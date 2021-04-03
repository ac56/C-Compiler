#include "AST.hpp"

#include <utility>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <exception>

using namespace std;

/**********************************/
/****** Constructors **************/
/**********************************/

TranslationUnit::TranslationUnit(vector<unique_ptr<External>> _declarations)
    : declarations(move(_declarations)) {}

External::External(unique_ptr<Declaration> _declaration) noexcept
    : declaration(move(_declaration)) {};

FunctionDefinition::FunctionDefinition(unique_ptr<Declaration> _declaration,
                                       vector<string> argument_names,
                                       unique_ptr<Statement> _body)
    : External(move(_declaration)), argument_names(argument_names), body(move(_body))
    , argument_types(declaration->type->get_arg_types()) {};

ExternalDeclaration::ExternalDeclaration(unique_ptr<Declaration> _declaration) noexcept
    : External(move(_declaration)) {};

unique_ptr<Statement> make_noop() {
    return make_unique<Block>(       //
        vector<unique_ptr<Declaration> >(),
        vector<unique_ptr<Statement> >());
}

Declaration::Declaration(unique_ptr<Type> _type, string _name) noexcept
    :  type(move(_type)), name(_name) {};

unique_ptr<InitDeclaration> Declaration::with_init(unique_ptr<const Initializer> _initializer) {
    return make_unique<InitDeclaration>(type->clone(), name, move(_initializer));
}

InitDeclaration::InitDeclaration(std::unique_ptr<Type> _type,
                                 std::string _name,
                                 std::unique_ptr<const Initializer> _initializer) noexcept
    : Declaration(move(_type), _name), initializer(move(_initializer)) {};

ExpressionInitializer::ExpressionInitializer(unique_ptr<Expression> _expr)
    : expr(move(_expr)) {};

ExpressionStmt::ExpressionStmt(unique_ptr<Expression> _expr)
    : expr(move(_expr)){};

IfStmt::IfStmt(unique_ptr<Expression> _condition,
               unique_ptr<Statement> _trueBranch,
               unique_ptr<Statement> _falseBranch)
    : condition(move(_condition)), trueBranch(move(_trueBranch)),
      falseBranch(move(_falseBranch)){};

WhileStmt::WhileStmt(unique_ptr<Expression> _cond, unique_ptr<Statement> _body)
    : cond(move(_cond)), body(move(_body)){};

DoStmt::DoStmt(unique_ptr<Expression> _cond, unique_ptr<Statement> _body)
    : cond(move(_cond)), body(move(_body)){};

SwitchStmt::SwitchStmt(unique_ptr<Expression> _expr, unique_ptr<Statement> _body)
    : expr(move(_expr)), body(move(_body)){};

ForStmt::ForStmt(unique_ptr<Expression> _init, unique_ptr<Expression> _cond,
                 unique_ptr<Expression> _after, unique_ptr<Statement> _body)
    : init(move(_init)), cond(move(_cond)), after(move(_after)),
      body(move(_body)){};

Block::Block(vector<unique_ptr<Declaration> > _declarations,
             vector<unique_ptr<Statement> > _body) noexcept
    : declarations(move(_declarations)), body(move(_body)){};

Return::Return(unique_ptr<Expression> _value) noexcept : value(move(_value)){};
Return::Return() noexcept : value(nullptr){};
Identifier::Identifier(string _name) noexcept : name(_name){};
IntConstant::IntConstant(long int _value) noexcept : value(_value){};
FloatConstant::FloatConstant(double _value) noexcept : value(_value){};
StringConstant::StringConstant(string _value) noexcept : value(_value){};
SizeOfType::SizeOfType(unique_ptr<Type> _type) noexcept : type(move(_type)){};

ArraySubscript::ArraySubscript(unique_ptr<Expression> _array,
                               unique_ptr<Expression> _index) noexcept
    : array(move(_array)), index(move(_index)){};

FunctionCall::FunctionCall(unique_ptr<Expression> _callee,
                           vector<unique_ptr<Expression>> _args) noexcept
    : callee(move(_callee)), arguments(move(_args)){};

DotOperator::DotOperator(unique_ptr<Expression> _left, string _right) noexcept
    : left(move(_left)), right(_right){};

ArrowOperator::ArrowOperator(unique_ptr<Expression> _left,
                             string _right) noexcept
    : left(move(_left)), right(_right){};

BinaryOperator::BinaryOperator(BinaryOperatorType _type,
                               unique_ptr<Expression> _left,
                               unique_ptr<Expression> _right) noexcept
    : operator_type(_type), left(move(_left)), right(move(_right)){};

UnaryOperator::UnaryOperator(UnaryOperatorType _type,
                             unique_ptr<Expression> _expr) noexcept
    : operator_type(_type), operand(move(_expr)){};

Cast::Cast(unique_ptr<Type> _type, unique_ptr<Expression> _expr) noexcept
    : type(move(_type)), expression(move(_expr)){};

TernaryIf::TernaryIf(std::unique_ptr<Expression> _condition,
                     std::unique_ptr<Expression> _trueBranch,
                     std::unique_ptr<Expression> _falseBranch) noexcept
    : condition(move(_condition)), trueBranch(move(_trueBranch)),
      falseBranch(move(_falseBranch)){};

Assignment::Assignment(AssignmentType _assignmentType, std::unique_ptr<Expression> _target,
                       std::unique_ptr<Expression> _value) noexcept
    : assignmentType(_assignmentType), target(move(_target)), value(move(_value)){};

/****************************************/
/****** Printers ************************/
/****************************************/

std::ostream& operator<<(std::ostream& out, const Declaration& decl) {
    return out << *decl.type << " " << decl.name;
}

ostream& operator<<(ostream& out , const AssignmentType& val) {
    switch(val) {
        case AssignmentType::PLAIN:
            out << "=";
            break;
        case AssignmentType::MUL:
            out << "*=";
            break;
        case AssignmentType::DIV:
            out << "/=";
            break;
        case AssignmentType::MOD:
            out << "%=";
            break;
        case AssignmentType::ADD:
            out << "+=";
            break;
        case AssignmentType::SUB:
            out << "-=";
            break;
        case AssignmentType::LSHIFT:
            out << "<<=";
            break;
        case AssignmentType::RSHIFT:
            out << ">>=";
            break;
        case AssignmentType::AND:
            out << "&=";
            break;
        case AssignmentType::XOR:
            out << "^=";
            break;
        case AssignmentType::OR:
            out << "|=";
            break;
    }
    return out;
}

ostream& operator<<(ostream& out, const BinaryOperatorType& op) {
    switch(op) {
        case BinaryOperatorType::MUL:
            out << "*";
            break;
        case BinaryOperatorType::DIV:
            out << "/";
            break;
        case BinaryOperatorType::MOD:
            out << "%";
            break;
        case BinaryOperatorType::ADD:
            out << "+";
            break;
        case BinaryOperatorType::SUB:
            out << "-";
            break;
        case BinaryOperatorType::LSHIFT:
            out << "<<";
            break;
        case BinaryOperatorType::RSHIFT:
            out << ">>";
            break;
        case BinaryOperatorType::LT:
            out << "<";
            break;
        case BinaryOperatorType::GT:
            out << ">";
            break;
        case BinaryOperatorType::LTE:
            out << "<=";
            break;
        case BinaryOperatorType::GTE:
            out << ">=";
            break;
        case BinaryOperatorType::EQUALS:
            out << "==";
            break;
        case BinaryOperatorType::NOT_EQUALS:
            out << "!=";
            break;
        case BinaryOperatorType::BITWISE_AND:
            out << "&";
            break;
        case BinaryOperatorType::BITWISE_OR:
            out << "|";
            break;
        case BinaryOperatorType::BITWISE_XOR:
            out << "^";
            break;
        case BinaryOperatorType::LOGICAL_AND:
            out << "&&";
            break;
        case BinaryOperatorType::LOGICAL_OR:
            out << "||";
            break;
    }
    return out;
}
