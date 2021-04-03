#pragma once

#include <string>
#include "AST.hpp"


class Declarator {
    public:
        virtual std::string get_name() const =0;
        virtual std::unique_ptr<Declaration> to_declaration(std::unique_ptr<Type>) const =0;
        virtual const std::vector<std::unique_ptr<Declaration>>& get_arguments() const =0;
        virtual ~Declarator() {};
};

struct IdentifierDeclarator : public Declarator {
    public:
        std::string name;

        IdentifierDeclarator(std::string);
        virtual std::string get_name() const override { return name; };
        virtual std::unique_ptr<Declaration> to_declaration(std::unique_ptr<Type>) const override;
        virtual const std::vector<std::unique_ptr<Declaration>>& get_arguments() const override;
};

struct FunctionDeclarator : public Declarator {
    private:
        std::unique_ptr<Declarator> returns;
        std::vector<std::unique_ptr<Declaration>> args;

    public:
        FunctionDeclarator(std::unique_ptr<Declarator>, std::vector<std::unique_ptr<Declaration>>);

        virtual std::string get_name() const override { return returns->get_name(); };
        virtual std::unique_ptr<Declaration> to_declaration(std::unique_ptr<Type>) const override;
        virtual const std::vector<std::unique_ptr<Declaration>>& get_arguments() const override;
};

struct ArrayDeclarator : public Declarator {
    public:
        std::unique_ptr<Declarator> contains;
        std::unique_ptr<Expression> size;

        ArrayDeclarator(std::unique_ptr<Declarator>, std::unique_ptr<Expression>);

        virtual std::string get_name() const override { return contains->get_name(); };
        virtual std::unique_ptr<Declaration> to_declaration(std::unique_ptr<Type>) const override;
        virtual const std::vector<std::unique_ptr<Declaration>>& get_arguments() const override;
};

struct PointerDeclarator : public Declarator {
    public:
        const std::unique_ptr<const Declarator> points_to;

        PointerDeclarator(std::unique_ptr<Declarator>);

        virtual std::string get_name() const override { return points_to->get_name(); };
        virtual std::unique_ptr<Declaration> to_declaration(std::unique_ptr<Type>) const override;
        virtual const std::vector<std::unique_ptr<Declaration>>& get_arguments() const override;
};

struct InitDeclarator {
    public:
        std::unique_ptr<const Declarator> declarator;
        /**
        * If null there is no initializer
        */
        std::unique_ptr<const Initializer> initializer;

        InitDeclarator(std::unique_ptr<Declarator> _declarator,
                       std::unique_ptr<Initializer> _initializer);

        std::unique_ptr<Declaration> to_declaration(std::unique_ptr<Type>);
        const std::vector<const Declaration>& get_arguments() const;
};

using DeclarationSpecifiers = uint16_t;
static const DeclarationSpecifiers DECSPEC_VOID     = 0b00000000000001;
static const DeclarationSpecifiers DECSPEC_SIGNED   = 0b00000000000010;
static const DeclarationSpecifiers DECSPEC_UNSIGNED = 0b00000000000100;
static const DeclarationSpecifiers DECSPEC_CHAR     = 0b00000000001000;
static const DeclarationSpecifiers DECSPEC_DOUBLE   = 0b00000000010000;
static const DeclarationSpecifiers DECSPEC_FLOAT    = 0b00000000100000;
static const DeclarationSpecifiers DECSPEC_LONG     = 0b00000001000000;
static const DeclarationSpecifiers DECSPEC_INT      = 0b00000010000000;
static const DeclarationSpecifiers DECSPEC_SHORT    = 0b00000100000000;
static const DeclarationSpecifiers DECSPEC_TYPEDEF  = 0b00001000000000;
static const DeclarationSpecifiers DECSPEC_EXTERN   = 0b00010000000000;
static const DeclarationSpecifiers DECSPEC_STATIC   = 0b00100000000000;
static const DeclarationSpecifiers DECSPEC_AUTO     = 0b01000000000000;
static const DeclarationSpecifiers DECSPEC_REGISTER = 0b10000000000000;

DeclarationSpecifiers get_storage_class_specifier(DeclarationSpecifiers);
DeclarationSpecifiers get_type_specifier(DeclarationSpecifiers);

std::unique_ptr<Type> type_from_declaration_specifier(DeclarationSpecifiers);
