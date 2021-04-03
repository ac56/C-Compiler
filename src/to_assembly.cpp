#include "AST.hpp"
#include "types.hpp"
#include "util.hpp"
#include <exception>

using namespace std;

string op(string opcode, string target, string arg1, string arg2) {
    return opcode + " " + target + ", " + arg1 + ", " + arg2 + "\n";
}

string op(string opcode, string target, string arg) {
    return opcode + " " + target + ", " + arg + "\n";
}

string op(string opcode, string target) {
    return opcode + " " + target + "\n";
}

string op(string opcode) {
    return opcode + "\n";
}

void move_location(const LocationInfo& from, const LocationInfo& to, ostream& out) {
    from.match(
        [&] (IntRegister from_reg) {
            to.match(
                [&] (IntRegister to_reg) {
                    out << op("move", to_string(to_reg), to_string(from_reg));
                },
                [&] (FpRegister to_freg) {
                    out << op("mtc0", to_string(from_reg), to_string(to_freg));
                },
                [&] (Offset to_offset) {
                    out << op("sw", to_string(from_reg), to_string(to_offset)+"($fp)");
                });
        },
        [&] (FpRegister from_freg) {
            to.match(
                [&] (IntRegister to_reg) {
                    out << op("mfc0", to_string(to_reg), to_string(from_freg));
                },
                [&] (FpRegister to_freg) {
                    out << op("move", to_string(to_freg), to_string(from_freg));
                },
                [&] (Offset to_offset) {
                    out << op("sw", to_string(from_freg), to_string(to_offset)+"($fp)");
                });
        },
        [&] (Offset from_offset) {
            to.match(
                [&] (IntRegister to_reg) {
                    out << op("lw", to_string(to_reg), to_string(from_offset)+"($fp)");
                },
                [&] (FpRegister to_freg) {
                    out << op("lwc1", to_string(to_freg), to_string(from_offset)+"($fp)");
                },
                [&] (Offset to_offset) {
                    move_location(from, IntRegister::t9, out);
                    move_location(IntRegister::t9, to, out);
                });
        });
}

void load_label(const Label& label, const IntRegister& reg, ostream& out) {
    out << op("lui", to_string(reg), "%hi("+label+")");
    out << op("lw", to_string(reg), "%lo("+label+")", "("+to_string(reg)+")");
}

void TranslationUnit::to_assembly(std::ostream& out) const {
    auto top_ctx = make_shared<Context>();

    for (const auto& ext_decl : declarations) {
        out << ".globl " << ext_decl->declaration->name << "\n";
    }

    out << "\n\n## Begin declarations " << "\n\n";

    for (const auto& decl : declarations) {
        Context this_ctx(top_ctx);
        decl->to_assembly(this_ctx, out);
    }
}

void FunctionDefinition::to_assembly(Context& ctx, std::ostream& out) const {
    // Add arguments to context
    int arg_position = 0; // Indicates (in words) the next available argument position
    int int_registers_taken = 0;
    bool first_argument_integral = false;
    for (int i = 0; i < argument_names.size() && i < argument_types.size(); ++i) {
        const string&           name = argument_names.at(i);
        const shared_ptr<Type>& type = argument_types.at(i);

        /****************************************************/
        /***** It might be better not to touch this... ******/
        /***** DO NOT REORDER *******************************/
        /****************************************************/

        const bool type_in_fp_reg = type->get_type_info().in_fp_reg;
        const unsigned int type_size_bytes = type->get_type_info().size_bytes;

        if (i == 0 && !type_in_fp_reg) first_argument_integral = true;

        // Add the argument
        switch (arg_position) {
            case 0:
                if (type_in_fp_reg && !first_argument_integral)
                    ctx.add_argument(name, type, FpRegister::f12);
                else if (type_in_fp_reg && first_argument_integral)
                    throw runtime_error("First function argument is integral, but it's also not");
                else
                    ctx.add_argument(name, type, IntRegister::a0);
                break;
            case 1:
                if (type_in_fp_reg && !first_argument_integral)
                    throw runtime_error("First argument was single-word, but now placing float at second place. Impossible");
                else if (type_in_fp_reg && type_size_bytes == 4) // float
                    ctx.add_argument(name, type, IntRegister::a1);
                else if (type_in_fp_reg && type_size_bytes != 4) // double
                    ctx.add_argument(name, type, IntRegister::a2);
                else
                    ctx.add_argument(name, type, IntRegister::a0);
                break;
            case 2:
                if (type_in_fp_reg)
                    ctx.add_argument(name, type, FpRegister::f14);
                else
                    ctx.add_argument(name, type, IntRegister::a2);
                break;
            case 3:
                if (type_in_fp_reg && !first_argument_integral) {
                    ++arg_position; // Go to stack
                    /* fallthrough */
                } else if (type_in_fp_reg) {
                    ++arg_position; // Go to stack
                    /* fallthrough */
                } else {
                    ctx.add_argument(name, type, IntRegister::a0);
                    break;
                }
            default:
                ctx.add_argument(name, type, LocationInfo(arg_position*4)); // arg_position is in words
                break;
            }

        arg_position += word_align(type_size_bytes) / 4;
    }


    stringstream t_out;
    // Saved integer register (s0-s8)
    for (int i = 0; i <= 8; ++i) {
        Offset offset = ctx.allocate_stack(
            "saved_reg_"+to_string(i),
            make_shared<BuiltinType>(BuiltinTypeName::UNSIGNED_INT));

        t_out << op("sw", "$s"+to_string(i), to_string(offset)+"($fp)");
    }

    // Saved fp registers (f20-f30)
    for (int i = 20; i <= 30; ++i) {
        Offset offset = ctx.allocate_stack(
            "saved_fp_reg_"+to_string(i),
            make_shared<BuiltinType>(BuiltinTypeName::UNSIGNED_INT));

        t_out << op("swc1", "$"+to_string(i), to_string(offset)+"($fp)");
    }

    // Generate code to t_out
    body->to_assembly(ctx, t_out, "", "");

    /***** Actual code *****/
    // Label
    out << "\n\n";
    out << "#######-- " << declaration->name << " --#######\n";
    out << declaration->name << ":\n";

    // Allocate stack frame
    signed int stack_size = ctx.get_max_stack_size(); // signed cause we are going to negate it
    out << op("addiu", "$sp", "$sp", to_string(-stack_size));
    out << op("sw", "$fp", to_string(stack_size-4)+"($sp)");
    out << op("move", "$fp", "$sp");

    // Code
    out << t_out.rdbuf();
    out << "#######^^ " << declaration->name << " ^^#######\n";
    /***** Actual code *****/
}

void Return::to_assembly(Context &ctx, std::ostream & out, const std::string& end_label, const std::string& begin_label) const {
    auto rv_storage = value->to_assembly(ctx, out, "*rv*");
    move_location(rv_storage.location, IntRegister::v0, out);

    unsigned int stack_size = ctx.get_max_stack_size();

    out << "# Return\n";
    out << op("move",  "$sp", "$fp");
    out << op("lw",    "$fp", to_string(stack_size-4)+"($sp)");
    out << op("addiu", "$sp", "$sp", to_string(stack_size));
    out << op("j",     "$31");
    out << op("nop");
}

StorageInfo Identifier::to_assembly(Context &ctx, std::ostream &, std::string result_name) const {
    return ctx.lookup_variable(name);
}

StorageInfo BinaryOperator::to_assembly(Context &ctx, std::ostream& out, std::string result_name) const {
    StorageInfo left_storage = left->to_assembly(ctx, out, result_name+"_l");
    LocationInfo persistent_left_location = ctx.allocate_persistent(result_name+"_l", left_storage.type);
    move_location(left_storage.location, persistent_left_location, out);

    StorageInfo right_storage = right->to_assembly(ctx, out, result_name+"_r");
    if(!left_storage.type->arithmetic_compatible(*right_storage.type)){
    	stringstream ss;
    	ss << "Incompatible types" << left_storage.type << " and " << right_storage.type;
    	throw runtime_error(ss.str());
    }

    move_location(persistent_left_location, IntRegister::t1, out); // t1 := left
    move_location(right_storage.location, IntRegister::t2, out); // t2 := right

    bool t1_unsigned = left_storage.type->get_type_info().is_unsigned;
    bool t2_unsigned = right_storage.type->get_type_info().is_unsigned;

    string true_label = ctx.new_label();
    string false_label = ctx.new_label();

    switch(operator_type){
        case BinaryOperatorType::ADD:
        	out << op("addu", "$t0", "$t1", "$t2");
        	break;
	    case BinaryOperatorType::SUB:
	    	out << op("subu", "$t0", "$t1", "$t2");
	    	break;
	    case BinaryOperatorType::MUL:
	    	out << op("mul", "$t0", "$t1", "$t2");
	    	break;
	    case BinaryOperatorType::DIV:
	    	out << op("div", "$t1", "$t2");
	    	out << op("teq", "$t2", "$0", "7");
	    	// out << op("mfhi", "$t0");
	    	out << op("mflo", "$t0");
	    	break;
	   	case BinaryOperatorType::MOD:
	    	out << op("div", "$t1", "$t2");
	    	out << op("mfhi", "$t0");
	    	break;
	    case BinaryOperatorType::LSHIFT:
	    	out << op("sll", "$t0", "$t1", "$t2");
	    	break;
	    case BinaryOperatorType::RSHIFT:
	    	if(t1_unsigned) {
	    		out << op("srl", "$t0", "$t1", "$t2");
	    	} else {
	    		out << op("sra", "$t0", "$t1", "$t2");
	    	}
	    	break;
	    case BinaryOperatorType::LT:
	    	if(t1_unsigned || t2_unsigned){
	    		out << op("sltu", "$t0", "$t1", "$t2");
	    	}
	    	else{
	    		out << op("slt", "$t0", "$t1", "$t2");
	    	}
	    	break;
	    case BinaryOperatorType::GT:
	    	if(t1_unsigned || t2_unsigned){
	    		out << op("sltu", "$t0", "$t2", "$t1");
	    	}
	    	else{
	    		out << op("slt", "$t0", "$t2", "$t1");
	    	}
	    	break;
	    case BinaryOperatorType::LTE:
	    	if(t1_unsigned || t2_unsigned){
	    		out << op("sltu", "$t0", "$t1", "$t2");
	    	}
	    	else{
	    		out << op("slt", "$t0", "$t1", "$t2");
	    	}
	    	out << op("bne", "$t1", "$t2", "20"); //jump 5 instructions
	    	out << "nop" << "\n";
	    	out << op("ori", "$t0", "$t0", "1");
	    	out << "b 12" << "\n";
	    	out << "nop" << "\n";
	    	out << op("or", "$t0", "$0", "$0");
	    	break;
	    case BinaryOperatorType::GTE:
	    	if(t1_unsigned || t2_unsigned){
	    		out << op("sltu", "$t0", "$t2", "$t1");
	    	}
	    	else{
	    		out << op("slt", "$t0", "$t2", "$t1");
	    	}
	    	out << op("bne", "$t1", "$t2", "20"); //jump 5 instructions
	    	out << "nop" << "\n";
	    	out << op("ori", "$t0", "$t0", "1");
	    	out << "b" << " " << "12" << "\n";
	    	out << "nop" << "\n";
	    	out << op("or", "$t0", "$0", "$0");
	    	break;
	    case BinaryOperatorType::EQUALS:
	    	out << op("bne", "$t1", "$t2", "20"); //jump 5 instructions
	    	out << "nop" << "\n";
	    	out << op("ori", "$t0", "$t0", "1");
	    	out << "b" << " " << "12" << "\n";
	    	out << "nop" << "\n";
	    	out << op("or", "$t0", "$0", "$0");
	    	break;
	    case BinaryOperatorType::NOT_EQUALS:
	    	out << op("beq", "$t1", "$t2", "20"); //jump 5 instructions
	    	out << "nop" << "\n";
	    	out << op("ori", "$t0", "$t0", "1");
	    	out << "b" << " " << "12" << "\n";
	    	out << "nop" << "\n";
	    	out << op("or", "$t0", "$0", "$0");
	    	break;
	    case BinaryOperatorType::BITWISE_AND:
	    	out << op("and", "$t0", "$t1", "$t2");
	    	break;
	    case BinaryOperatorType::BITWISE_OR:
	    	out << op("or", "$t0", "$t1", "$t2");
	    	break;
	    case BinaryOperatorType::BITWISE_XOR:
	    	out << op("xor", "$t0", "$t1", "$t2");
	    	break;
	    case BinaryOperatorType::LOGICAL_AND:
	    	out << op("beq", "$t1", "$0", false_label);
	    	out << "nop" << "\n";
	    	out << op("beq", "$t2", "$0", false_label);
	    	out << "nop" << "\n";
	    	out << op("li", "$t0", "1");
	    	out << "b" << " " << true_label << "\n";
	    	out << "nop" << "\n";
	    	out << false_label << ":\n";
	    	out << op("or", "$t0", "$0", "$0");
	    	out << true_label << ":\n";
	    	break;
	    case BinaryOperatorType::LOGICAL_OR:
			out << op("bne", "$t1", "$0", true_label);
	    	out << "nop" << "\n";
	    	out << op("bne", "$t2", "$0", true_label);
	    	out << "nop" << "\n";
	    	out << op("or", "$t0", "$0", "$0");
	    	out << "b" << " " << false_label << "\n";
	    	out << "nop" << "\n";
	    	out << true_label << ":\n";
	    	out << op("li", "$t0", "1");
	    	out << false_label << ":\n";
	    	break;
    }


    return {IntRegister::t0,  left_storage.type  };
}

void Block::to_assembly(Context& ctx, ostream& out, const std::string& end_label , const std::string& begin_label) const {
    for (const auto& decl : declarations) {
        decl->to_assembly(ctx, out);
    }
    for (const auto& stmt : body) {
        stmt->to_assembly(ctx, out, end_label, begin_label);
    }
}

void IfStmt::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const {
    string else_label = ctx.new_label();
    string if_end_label = ctx.new_label();

    move_location(condition->to_assembly(ctx, out, "cond").location,
                  IntRegister::t0, out);
    out << op("beq", "$t0", "$0", else_label);
    out << "nop" << "\n";

    trueBranch->to_assembly(ctx, out, end_label, begin_label);
    out << "b" << " " << if_end_label << "\n";
    out << "nop" << "\n";

    out << else_label << ":\n";
    falseBranch->to_assembly(ctx, out, end_label, begin_label);

    out << if_end_label << ":\n";
}

void WhileStmt::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const {
    string true_label = ctx.new_label();
    string cond_label = ctx.new_label();
    string while_end = ctx.new_label();

    out << "b" << " " << cond_label << "\n";
    out << "nop" << "\n";

    out << true_label << ":\n";
    body->to_assembly(ctx, out, while_end, cond_label);

    out << cond_label << ":" << "\n";
    move_location(cond->to_assembly(ctx, out, "cond").location,
                  IntRegister::t0,
                  out);

    out << op("li", "$t1", "1");
    out << op("beq", "$t0", "$1", true_label);
    out << "nop" << "\n";
    out << while_end << ":" << "\n";

}

void DoStmt::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const {
    string true_label = ctx.new_label();
    string do_end = ctx.new_label();
    string do_cond = ctx.new_label();

    out << true_label << ":" << "\n";
    body->to_assembly(ctx, out, do_end, do_cond);

    out << do_cond << ":\n";
    move_location(cond->to_assembly(ctx, out, "cond").location,
                  IntRegister::t0,
                  out);
    out << op("beq", "$t0", "$1", true_label);
    out << "nop" << "\n";
    out << do_end << ":\n";
}

void ForStmt::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const {
    string true_label = ctx.new_label();
    string for_end = ctx.new_label();
    string for_cond = ctx.new_label();

    move_location(init->to_assembly(ctx, out, "cond").location,
                  IntRegister::t0,
                out);
    out << true_label << ":" << "\n";
    body->to_assembly(ctx, out, for_end, for_cond);

    out << for_cond << ":\n";
    after->to_assembly(ctx, out, "cond");
    move_location(cond->to_assembly(ctx, out, "cond").location,
                  IntRegister::t0,
                  out);
    out << op("beq", "$t0", "$1", true_label);
    out << "nop" << "\n";
    out << for_end << ":\n";
}

void ExpressionStmt::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const {
    expr->to_assembly(ctx, out, "to be removed");
}


void Break::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const {
    out << "b" << " " << end_label << "\n";
    out << "nop" << "\n";
}
void Continue::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const {
    out << "b" << " " << begin_label << "\n";
    out << "nop" << "\n";
}

StorageInfo IntConstant::to_assembly(Context& ctx, ostream& out, string name) const {
    out << op("li", "$t0", to_string(value)) << "\n";
    return { IntRegister::t0, make_shared<BuiltinType>(BuiltinTypeName::SIGNED_INT) };
}

void Declaration::to_assembly(Context& ctx, ostream& out) const {
    ctx.allocate_persistent(name, type);
}

void InitDeclaration::to_assembly(Context& ctx, ostream& out) const {
    LocationInfo location = ctx.allocate_persistent(name, type);
    initializer->to_assembly(ctx, location, out);
}

void ExpressionInitializer::to_assembly(Context& ctx, LocationInfo location, std::ostream& out) const {
    StorageInfo temp = expr->to_assembly(ctx, out, "_");
    move_location(temp.location, location, out);
}

void ExternalDeclaration::to_assembly(Context&, ostream&) const { throw runtime_error("Not yet implemented: ExternalDeclaration"); }
void SwitchStmt::to_assembly(Context& ctx, ostream& out, const std::string& end_label, const std::string& begin_label) const { throw runtime_error("Not yet implemented: SwitchStmt"); }
StorageInfo TernaryIf::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: TernaryIf"); }
StorageInfo ArraySubscript::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: ArraySubscript"); }
StorageInfo FloatConstant::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: FloatConstant"); }
StorageInfo CharConstant::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: CharConstant"); }
StorageInfo Assignment::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: Assignment"); }
StorageInfo UnaryOperator::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: UnaryOperator"); }
StorageInfo StringConstant::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: StringConstant"); }
StorageInfo FunctionCall::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: FunctionCall"); }
StorageInfo Cast::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: Cast"); }
StorageInfo ArrowOperator::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: ArrowOperator"); }
StorageInfo DotOperator::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: DotOperator"); }
StorageInfo SizeOfType::to_assembly(Context&, ostream&, string) const { throw runtime_error("Not yet implemented: SizeOfType"); }
