#pragma once

#include <ostream>
#include <memory>
#include <vector>
#include <iostream>

class NotAFunctionType : std::exception {
    public:
        const std::string type_name;

        NotAFunctionType(const std::string& _type_name)
            : type_name(_type_name) {};

        const char* what() const noexcept override {
            return (type_name + " is not a function type").c_str();
        }
};


struct TypeInfo{
    unsigned int size_bytes;
    bool in_fp_reg;
    bool is_unsigned;
    bool is_function;
};


class Type {
    private:
        virtual void to_stream(std::ostream&) const =0;
    public:

        friend std::ostream& operator<<(std::ostream&, const Type&);
        virtual ~Type() {};
        virtual std::unique_ptr<Type> clone() const =0;

        virtual TypeInfo get_type_info() const = 0;
        virtual bool arithmetic_compatible(const Type&) const = 0;

        virtual std::vector<std::shared_ptr<Type>> get_arg_types() const {
            throw NotAFunctionType(typeid(*this).name());
        };
};

enum class BuiltinTypeName {
    CHAR, DOUBLE, FLOAT, LONG_DOUBLE, SIGNED_CHAR, SIGNED_INT, SIGNED_LONG_INT,
    SIGNED_SHORT_INT, UNSIGNED_CHAR, UNSIGNED_INT, UNSIGNED_LONG_INT,
    UNSIGNED_SHORT_INT, VOID
};
std::ostream& operator<<(std::ostream&, const BuiltinTypeName&);

class BuiltinType : public Type {
    private:
        virtual void to_stream(std::ostream&) const override;
     public:
        const BuiltinTypeName type;


        BuiltinType(BuiltinTypeName _type);
        virtual std::unique_ptr<Type> clone() const override;

        virtual TypeInfo get_type_info() const override;
        virtual bool arithmetic_compatible(const Type&) const override;
};

class PointerType : public Type {
    private:
        virtual void to_stream(std::ostream&) const override;
    public:
        const std::unique_ptr<Type> points_to;

        PointerType(std::unique_ptr<Type> _points_to);
        virtual std::unique_ptr<Type> clone() const override;

        virtual TypeInfo get_type_info() const override;
        virtual bool arithmetic_compatible(const Type&) const override;
};

class ArrayType : public Type {
    private:
        virtual void to_stream(std::ostream&) const override;
    public:
        const std::unique_ptr<Type> element_type;

        /**
        * -1 Indicated a missing length
        */
        const int length;

        ArrayType (std::unique_ptr<Type> element_type);
        ArrayType (std::unique_ptr<Type> element_type, int length);
        virtual std::unique_ptr<Type> clone() const override;

        virtual TypeInfo get_type_info() const override;
        virtual bool arithmetic_compatible(const Type&) const override;
};

class FunctionType : public Type {
    private:
        virtual void to_stream(std::ostream&) const override;
    public:

        const std::shared_ptr<Type> returns;
        const std::vector<std::shared_ptr<Type>> args;

        FunctionType(std::shared_ptr<Type>,
                     std::vector<std::shared_ptr<Type>>) noexcept;

        virtual std::unique_ptr<Type> clone() const override;

        virtual TypeInfo get_type_info() const override;
        virtual bool arithmetic_compatible(const Type&) const override;

        virtual std::vector<std::shared_ptr<Type>> get_arg_types() const override {
            return args;
        };
};
