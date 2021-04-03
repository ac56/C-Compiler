#include <string>
#include <algorithm>
#include <bitset>
#include <iostream>
#include "parser_helpers.hpp"

using namespace std;

DeclarationSpecifiers get_storage_class_specifier(DeclarationSpecifiers ds) {
    return static_cast<DeclarationSpecifiers>(ds & 0b11111000000000);
}

DeclarationSpecifiers get_type_specifier(DeclarationSpecifiers ds) {
    return static_cast<DeclarationSpecifiers>(ds & 0b00000111111111);
}

unique_ptr<Type> type_from_declaration_specifier(DeclarationSpecifiers spec) {
    switch (get_type_specifier(spec)) {
        case DECSPEC_VOID:
            return make_unique<BuiltinType>(BuiltinTypeName::VOID);
            break;
        case DECSPEC_INT:
        case DECSPEC_SIGNED:
        case DECSPEC_SIGNED | DECSPEC_INT:
            return make_unique<BuiltinType>(BuiltinTypeName::SIGNED_INT);
            break;
        case DECSPEC_UNSIGNED:
        case DECSPEC_UNSIGNED | DECSPEC_INT:
            return make_unique<BuiltinType>(BuiltinTypeName::UNSIGNED_INT);
            break;
        case DECSPEC_CHAR:
            return make_unique<BuiltinType>(BuiltinTypeName::CHAR);
            break;
        case DECSPEC_SIGNED | DECSPEC_CHAR:
            return make_unique<BuiltinType>(BuiltinTypeName::SIGNED_CHAR);
            break;
        case DECSPEC_SHORT:
        case DECSPEC_SHORT  | DECSPEC_INT:
        case DECSPEC_SIGNED | DECSPEC_SHORT:
        case DECSPEC_SIGNED | DECSPEC_SHORT | DECSPEC_INT:
            return make_unique<BuiltinType>(BuiltinTypeName::SIGNED_SHORT_INT);
            break;
        case DECSPEC_UNSIGNED | DECSPEC_SHORT:
        case DECSPEC_UNSIGNED | DECSPEC_SHORT | DECSPEC_INT:
            return make_unique<BuiltinType>(BuiltinTypeName::UNSIGNED_SHORT_INT);
            break;
        case DECSPEC_LONG:
        case DECSPEC_LONG  | DECSPEC_INT:
        case DECSPEC_SIGNED | DECSPEC_LONG:
        case DECSPEC_SIGNED | DECSPEC_LONG | DECSPEC_INT:
            return make_unique<BuiltinType>(BuiltinTypeName::SIGNED_LONG_INT);
            break;
        case DECSPEC_UNSIGNED | DECSPEC_LONG:
        case DECSPEC_UNSIGNED | DECSPEC_LONG | DECSPEC_INT:
            return make_unique<BuiltinType>(BuiltinTypeName::UNSIGNED_LONG_INT);
            break;
        case DECSPEC_FLOAT:
            return make_unique<BuiltinType>(BuiltinTypeName::FLOAT);
            break;
        case DECSPEC_DOUBLE:
            return make_unique<BuiltinType>(BuiltinTypeName::DOUBLE);
            break;
        case DECSPEC_LONG | DECSPEC_DOUBLE:
            return make_unique<BuiltinType>(BuiltinTypeName::LONG_DOUBLE);
            break;
        default:
            stringstream ss;
            ss << "Invalid DeclarationSpecifiers: " << spec;
            throw invalid_argument(ss.str());
            break;
    }
}

IdentifierDeclarator::IdentifierDeclarator(string _name) : name(_name) {};

FunctionDeclarator::FunctionDeclarator(unique_ptr<Declarator> _returns,
                                       vector<unique_ptr<Declaration>> _args)
    : returns(move(_returns)), args(move(_args)) {};

PointerDeclarator::PointerDeclarator(unique_ptr<Declarator> _points_to)
    : points_to(move(_points_to)) {};

ArrayDeclarator::ArrayDeclarator(unique_ptr<Declarator> _contains, unique_ptr<Expression> _size)
    : contains(move(_contains)), size(move(_size)) {};

InitDeclarator::InitDeclarator(unique_ptr<Declarator> _declarator,
                unique_ptr<Initializer> _initializer)
    : declarator(move(_declarator))
    , initializer(move(_initializer)) {};

unique_ptr<Declaration> IdentifierDeclarator::to_declaration(unique_ptr<Type> type) const {
    return make_unique<Declaration>(move(type), name);
}

unique_ptr<Declaration> PointerDeclarator::to_declaration(unique_ptr<Type> type) const {
    return points_to->to_declaration(make_unique<PointerType>(move(type)));
}

unique_ptr<Declaration> ArrayDeclarator::to_declaration(unique_ptr<Type> type) const {
    return contains->to_declaration(make_unique<ArrayType>(move(type)));
}

unique_ptr<Declaration> InitDeclarator::to_declaration(unique_ptr<Type> type) {
    if (initializer) {
        return declarator->to_declaration(move(type))->with_init(move(initializer));
    } else {
        return declarator->to_declaration(move(type));
    }
}

std::unique_ptr<Declaration> FunctionDeclarator::to_declaration(std::unique_ptr<Type> return_base) const {
    vector<shared_ptr<Type>> arg_types;
    for (auto arg_it = args.begin(); arg_it != args.end(); ++arg_it) {
        arg_types.push_back((*arg_it)->get_type().clone());
    }

    unique_ptr<Type> function_type = make_unique<FunctionType>(move(return_base), move(arg_types));
    return returns->to_declaration(move(function_type));
}

const vector<unique_ptr<Declaration>>& IdentifierDeclarator::get_arguments() const {
    throw runtime_error("Declarator for " + name + " has no arguments");
}
const vector<unique_ptr<Declaration>>& PointerDeclarator::get_arguments() const {
    return points_to->get_arguments();
}
const vector<unique_ptr<Declaration>>& ArrayDeclarator::get_arguments() const {
    return contains->get_arguments();
}
const vector<unique_ptr<Declaration>>& FunctionDeclarator::get_arguments() const {
    return args;
}
