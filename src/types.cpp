#include "types.hpp"

using namespace std;

BuiltinType::BuiltinType(BuiltinTypeName _type) : type(_type){};

PointerType::PointerType(unique_ptr<Type> _points_to)
    : points_to(move(_points_to)){};

ArrayType::ArrayType(unique_ptr<Type> _element_type)
    : element_type(move(_element_type)), length(-1) {}

ArrayType::ArrayType(unique_ptr<Type> _element_type, int _length)
    : element_type(move(_element_type)), length(_length) {}

FunctionType::FunctionType(shared_ptr<Type> _returns,
                           vector<shared_ptr<Type>> _args) noexcept
    : returns(move(_returns)), args(move(_args)) {};

unique_ptr<Type> BuiltinType::clone() const {
    return make_unique<BuiltinType>(type);
};

unique_ptr<Type> PointerType::clone() const {
    return make_unique<PointerType>(points_to->clone());
};

unique_ptr<Type> ArrayType::clone() const {
    return make_unique<ArrayType>(element_type->clone(), length);
};

unique_ptr<Type> FunctionType::clone() const {
    vector<shared_ptr<Type>> cloned_args;

    for (auto arg_it = args.begin(); arg_it != args.end(); ++arg_it) {
        cloned_args.push_back((*arg_it)->clone());
    }

    return make_unique<FunctionType>(returns->clone(), move(cloned_args));
}

/*** Printers ***/

ostream& operator<<(ostream& out, const Type& type) {
    type.to_stream(out);
    return out;
}

std::ostream& operator<<(std::ostream& out, const BuiltinTypeName& type_name) {
    switch (type_name) {
        case BuiltinTypeName::CHAR:
            out << "char";
            break;
        case BuiltinTypeName::DOUBLE:
            out << "double";
            break;
        case BuiltinTypeName::FLOAT:
            out << "float";
            break;
        case BuiltinTypeName::LONG_DOUBLE:
            out << "long double";
            break;
        case BuiltinTypeName::SIGNED_CHAR:
            out << "signed char";
            break;
        case BuiltinTypeName::SIGNED_INT:
            out << "signed int";
            break;
        case BuiltinTypeName::SIGNED_LONG_INT:
            out << "signed long int";
            break;
        case BuiltinTypeName::SIGNED_SHORT_INT:
            out << "signed short int";
            break;
        case BuiltinTypeName::UNSIGNED_CHAR:
            out << "unsigned char";
            break;
        case BuiltinTypeName::UNSIGNED_INT:
            out << "unsigned int";
            break;
        case BuiltinTypeName::UNSIGNED_LONG_INT:
            out << "unsigned long int";
            break;
        case BuiltinTypeName::UNSIGNED_SHORT_INT:
            out << "unsigned short int";
            break;
        case BuiltinTypeName::VOID:
            out << "void";
            break;
    }
    return out;
}

void BuiltinType::to_stream(std::ostream& out) const {
    out << type;
}

void PointerType::to_stream(std::ostream& out) const {
    out << "*" << *points_to;
}

void ArrayType::to_stream(std::ostream& out) const {
    out << *element_type << "[" << length << "]";
}

void FunctionType::to_stream(std::ostream& out) const {
    out << *returns << "(" << flush;
    for (auto arg_it = args.begin(); arg_it != args.end(); ++arg_it) {
        out << **arg_it << ", " << flush;
    }
    out << ")" << flush;
}

TypeInfo BuiltinType::get_type_info() const {
    unsigned int size_bytes;
    bool in_fp_reg;
    bool is_unsigned;

    //assign size_bytes
    switch (type) {
        case BuiltinTypeName::CHAR:
        case BuiltinTypeName::SIGNED_CHAR:
        case BuiltinTypeName::UNSIGNED_CHAR:
            size_bytes = 1;
            break;
        case BuiltinTypeName::UNSIGNED_SHORT_INT:
        case BuiltinTypeName::SIGNED_SHORT_INT:
            size_bytes = 2;
            break;
        case BuiltinTypeName::SIGNED_INT:
        case BuiltinTypeName::SIGNED_LONG_INT:
        case BuiltinTypeName::UNSIGNED_INT:
        case BuiltinTypeName::UNSIGNED_LONG_INT:
        case BuiltinTypeName::FLOAT:
            size_bytes = 4;
            break;

        case BuiltinTypeName::DOUBLE:
        case BuiltinTypeName::LONG_DOUBLE:
            size_bytes = 8;
            break;

        case BuiltinTypeName::VOID:
            throw runtime_error("tried to get size of VOID type");
            break;
    }

    //assign in_fp_reg
    switch (type) {
        case BuiltinTypeName::VOID:
            throw runtime_error("tried to get register file for VOID type");
            break;
        case BuiltinTypeName::DOUBLE:
        case BuiltinTypeName::LONG_DOUBLE:
        case BuiltinTypeName::FLOAT:
            in_fp_reg = true;
            break;
        default:
            in_fp_reg = false;
            break;
    }
    //assign is_unsigned
    switch (type) {
        case BuiltinTypeName::UNSIGNED_INT:
        case BuiltinTypeName::UNSIGNED_CHAR:
        case BuiltinTypeName::UNSIGNED_LONG_INT:
        case BuiltinTypeName::UNSIGNED_SHORT_INT:
            is_unsigned = true;
            break;
        default:
            is_unsigned = false;
            break;
    }

    return {size_bytes, in_fp_reg, is_unsigned};
}

TypeInfo PointerType::get_type_info() const {
    return {.size_bytes = 4,
            .in_fp_reg = false,
            .is_unsigned = true,
            .is_function = true};
}

TypeInfo ArrayType::get_type_info() const {
    unsigned int size_bytes;
    if (length == -1){
        size_bytes = 4;
    } else {
        size_bytes =  element_type->get_type_info().size_bytes * length;
    }

    return {.size_bytes = 4,
            .in_fp_reg = false,
            .is_unsigned = true,
            .is_function = false};
}

TypeInfo FunctionType::get_type_info() const {
    return {.size_bytes = 0,
            .in_fp_reg = false,
            .is_unsigned = false,
            .is_function = true};
}

bool ArrayType::arithmetic_compatible(const Type& other) const {
    return (other.get_type_info().size_bytes<=4) && (!other.get_type_info().in_fp_reg);
}

bool PointerType::arithmetic_compatible(const Type& other)const{
 return (other.get_type_info().size_bytes<=4) && (!other.get_type_info().in_fp_reg);
}
bool FunctionType::arithmetic_compatible(const Type& other)const{
    return false;
}
bool BuiltinType::arithmetic_compatible(const Type& other)const{
    return (get_type_info().in_fp_reg == other.get_type_info().in_fp_reg) &&
            (get_type_info().is_unsigned == other.get_type_info().is_unsigned);
}


