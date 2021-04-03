#include "AST.hpp"

#include <utility>
#include <vector>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <exception>

using namespace std;

const string python_main =
    "if __name__ == '__main__':\n"
    "    try:\n"
    "        import sys\n"
    "        sys.exit(main())\n"
    "    except NameError:\n"
    "        sys.exit(0)\n";

void TranslationUnit::to_python(string indent, ostream& out) const {
    for (auto decl = declarations.begin(); decl != declarations.end(); ++decl) {
        (*decl)->to_python(indent, out);;
        out << "\n";
    }
    out << "\n" << python_main;
}

void ExternalDeclaration::to_python(string indent, ostream& out) const {
    declaration->to_python(indent, out);
}

void FunctionDefinition::to_python(string indent, ostream& out) const {
	// out /*<< "def " << func_name->to_python(indent, out);*/ << "(" ;
	// for(int i=0; i< (arguments.size()-1); i++){
	// 	arguments.at(i)->to_python(indent, out);;
    //     out << ", ";
	// }
	// arguments.at(arguments.size()-1)->to_python(indent, out);;
    // out << " ):\n\t";
    // declaration->to_python(indent, out);;
    out << "def " << declaration->get_name() << "(";

    if (argument_names.size() > 1) {
        for (auto it = argument_names.begin(); it != --argument_names.end(); ++it) {
            out << *it << ", " << flush;
        }
    }
    if (argument_names.size() > 0)
        out << *(argument_names.end() - 1);

    out << "):\n";

    body->to_python(indent+"    ", out);
}

void Declaration::to_python(string indent, ostream& out) const {
    out << indent << name << " = 0\n";
}

void InitDeclaration::to_python(string indent, ostream& out) const {
    out << indent << name << " = ";
    initializer->to_python(indent, out);;
}

void ExpressionInitializer::to_python(string indent, ostream& out) const {
    expr->to_python(indent, out);
}

void Return::to_python(string indent, ostream& out) const {
	out << indent << "return " ;
    value->to_python(indent, out);;
    out << ";";
}


void ExpressionStmt::to_python(string indent, ostream& out) const {
    out << indent;
	expr->to_python(indent, out);
}

void Block::to_python(string indent, ostream& out) const {
    if (declarations.size() == 0 && body.size() == 0) {
        out << indent << "pass";
        return;
    }

	for(int i=0; i<declarations.size(); i++){
        declarations.at(i)->to_python(indent, out);
        out << "\n" ;
	}

	for(int i=0; i<body.size(); i++){
        body.at(i)->to_python(indent, out);
        out << "\n" ;
	}
}



void WhileStmt::to_python(string indent, ostream& out) const {
	out << indent << "while " ;
    cond->to_python(indent, out);;
    out << ":\n" ;
    body->to_python(indent+"    ", out);;

}



void IfStmt::to_python(string indent, ostream& out) const {
    out << indent << "if ";
    condition->to_python(indent, out);;
    out << ":\n" ;
    trueBranch->to_python(indent+"    ", out);;
    out << indent << "else:\n" ;
    falseBranch->to_python(indent+"    ", out);;
}

void TernaryIf::to_python(string indent, ostream& out) const {
    condition->to_python(indent, out);;
    out << " ? ";
    trueBranch->to_python(indent, out);;
    out << " : ";
    falseBranch->to_python(indent, out);;
    throw runtime_error("Not Implemented");
}


void Identifier::to_python(string indent, ostream& out) const {
    out << name;
}

void ArraySubscript::to_python(string indent, ostream& out) const {
    array->to_python(indent, out);;
    out << "[";
    index->to_python(indent, out);;
    out <<"]";
}

void FloatConstant::to_python(string indent, ostream& out) const { out << value; }
void IntConstant::to_python(string indent, ostream& out) const { out << value; }
void CharConstant::to_python(string indent, ostream& out) const { out << "'" << value << "'"; }

void Assignment::to_python(string indent, ostream& out) const {
    // throw runtime_error("Not Implemented");
    target->to_python(indent, out);;
    out << " " << assignmentType << " ";
    value->to_python(indent, out);;
}

void UnaryOperator::to_python(string indent, ostream& out) const {
    switch (operator_type) {
        case UnaryOperatorType::POST_INCREMENT:
            throw NotPythonTranslateable("Post PRE_INCREMENT operator");
            break;
        case UnaryOperatorType::POST_DECREMENT:
            throw NotPythonTranslateable("Post decrement operator");
            break;
        case UnaryOperatorType::PRE_INCREMENT:
            throw NotPythonTranslateable("Pre increment operator");
            break;
        case UnaryOperatorType::PRE_DECREMENT:
            throw NotPythonTranslateable("Pre decrement operator");
            break;
        case UnaryOperatorType::PLUS:
        	// throw runtime_error("Not Implemented");
            out << " +";
            operand->to_python(indent, out);;
            break;
        case UnaryOperatorType::NEGATE:
        	// throw runtime_error("Not Implemented");
            out << " -";
            operand->to_python(indent, out);;
            break;
        case UnaryOperatorType::NOT:
        	// throw runtime_error("Not Implemented");
            out << " not ";
            operand->to_python(indent, out);;
            break;
        case UnaryOperatorType::BITWISE_NOT:
        	// throw runtime_error("Not Implemented");
            out << " ~";
            operand->to_python(indent, out);;
            break;
        case UnaryOperatorType::LOGICAL_NOT:
        	// throw runtime_error("Not Implemented");
            out << " not ";
            operand->to_python(indent, out);;
            break;
        case UnaryOperatorType::DEREFERENCE:
        	// throw runtime_error("Not Implemented");
            throw NotPythonTranslateable("Dereference operator");
            break;
        case UnaryOperatorType::ADDRESS_OF:
        	// throw runtime_error("Not Implemented");
            throw NotPythonTranslateable("Dereference operator");
            break;
        case UnaryOperatorType::SIZEOF:
        	// throw runtime_error("Not Implemented");
            out << "sys.getsizeof(";
            operand->to_python(indent, out);;
            out << ")";
            break;
    }
}

void StringConstant::to_python(string indent, ostream& out) const {
    out << "\"" << value << "\"";
}

void FunctionCall::to_python(string indent, ostream& out) const {
    //throw runtime_error("Not Implemented");
    callee->to_python(indent, out);;
    out << "(";

    for (int i = 0; i < arguments.size()-1; i++) {
        arguments.at(i)->to_python(indent, out);;
        out << ",";
    }

    arguments.at(arguments.size() - 1)->to_python(indent, out);;
    out << ")";
}

void BinaryOperator::to_python(string indent, ostream& out) const {
	//throw runtime_error("Not Implemented");
    out << "(";
	switch(operator_type)
	{
		case BinaryOperatorType::LOGICAL_AND:
			left->to_python(indent, out);;
    		out << " " << "and" << " ";
    		right->to_python(indent, out);;
            break;
    	case BinaryOperatorType::LOGICAL_OR:
    		left->to_python(indent, out);;
    		out << " " << "or" << " ";
    		right->to_python(indent, out);;
            break;
    	default:
    		left->to_python(indent, out);;
    		out << " " << operator_type << " ";
    		right->to_python(indent, out);;
            break;
	}
    out << ")";
}

/**********************************/
/****** Not implemented ***********/
/**********************************/

void Cast::to_python(string indent, ostream&) const {
    throw NotPythonTranslateable("Casts");
}

void SwitchStmt::to_python(string indent, ostream&) const {
    throw NotPythonTranslateable("switch statements");
}

void ForStmt::to_python(string indent, ostream&) const {
    throw NotPythonTranslateable("for loops");
}

void DoStmt::to_python(string indent, ostream&) const {
    throw NotPythonTranslateable("do-while loops");
}

void Continue::to_python(string indent, ostream&) const {
    throw NotPythonTranslateable("continue");
}

void Break::to_python(string indent, ostream&) const {
    throw NotPythonTranslateable("break");
}

void ArrowOperator::to_python(string indent, ostream& out) const {
    throw NotPythonTranslateable("Arrow operator");
}

void DotOperator::to_python(string indent, ostream& out) const {
    throw NotPythonTranslateable("Dot operator");
}


void SizeOfType::to_python(string indent, ostream& out) const {
    throw NotPythonTranslateable("sizeof operator");
}
