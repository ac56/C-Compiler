#pragma once

#include <vector>
#include <memory>
#include "exceptions.hpp"
#include "types.hpp"
#include "context.hpp"


class AST {
    public:
        virtual void to_python(std::string indent, std::ostream&) const =0;
        virtual ~AST() {};
};

class Expression;
class Declaration;
class Statement;
class External;

class TranslationUnit : public AST {
    public:
        const std::vector<std::unique_ptr<External>> declarations;

        TranslationUnit(std::vector<std::unique_ptr<External>> declarations);
        virtual void to_python(std::string indent, std::ostream&) const override;
        void to_assembly(std::ostream&) const;
};

class External : public AST {
    public:
        const std::unique_ptr<Declaration> declaration;
        External(std::unique_ptr<Declaration>) noexcept;

        virtual void to_assembly(Context& ctx, std::ostream&) const =0;
};
class FunctionDefinition : public External {
    public:
        std::vector<std::string> argument_names;
        const std::vector<std::shared_ptr<Type>> argument_types;
        const std::unique_ptr<Statement> body;

        FunctionDefinition(std::unique_ptr<Declaration>,
                           std::vector<std::string>,
                           std::unique_ptr<Statement>);
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&) const override;
};

class ExternalDeclaration : public External {
     public:
        ExternalDeclaration(std::unique_ptr<Declaration>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override; //
        virtual void to_assembly(Context& ctx, std::ostream&) const override;
};

/***************************************************************/
class InitDeclaration;

class Initializer : public AST {
    public:
        /**
         * Generate code evaluating the initializer and putting the
         * result in the supplied LocationInfo
         */
        virtual void to_assembly(Context&, LocationInfo, std::ostream&) const =0;
};
class ExpressionInitializer : public Initializer {
    public:
        const std::unique_ptr<Expression> expr;

        ExpressionInitializer(std::unique_ptr<Expression> _expr);
        const Expression& get_expression() const { return *expr; };
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context&, LocationInfo, std::ostream&) const override;
};

class Declaration : public AST {
    public:
        std::shared_ptr<const Type> type;
        const std::string name;

        Declaration(std::unique_ptr<Type>, std::string) noexcept;
        std::unique_ptr<InitDeclaration> with_init(std::unique_ptr<const Initializer>);
        virtual ~Declaration() {};

        friend std::ostream& operator<<(std::ostream&, const Declaration&);
        inline const Type& get_type() { return *type; };
        inline const std::string& get_name() { return name; };
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context&, std::ostream&) const;
};

class InitDeclaration : public Declaration {
    public:
        const std::unique_ptr<const Initializer> initializer;

        InitDeclaration(std::unique_ptr<Type>, std::string, std::unique_ptr<const Initializer>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context&, std::ostream&) const override;
};


/***************************************************************/

class Statement : public AST {
    public:
        virtual ~Statement() {};
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const =0;
};

std::unique_ptr<Statement> make_noop();

class Block : public Statement {
    public:
        const std::vector<std::unique_ptr<Declaration>> declarations;
        const std::vector<std::unique_ptr<Statement>> body;

        Block(std::vector<std::unique_ptr<Declaration> >,
              std::vector<std::unique_ptr<Statement> >) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};


class ExpressionStmt : public Statement {
    std::unique_ptr<Expression> expr;

    public:
        ExpressionStmt(std::unique_ptr<Expression> expr);
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class IfStmt : public Statement {
    public:
        const std::unique_ptr<Expression> condition;
        const std::unique_ptr<Statement> trueBranch;
        const std::unique_ptr<Statement> falseBranch;


        IfStmt(std::unique_ptr<Expression> cond,
            std::unique_ptr<Statement> trueBranch,
            std::unique_ptr<Statement> falseBranch);
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class WhileStmt : public Statement {
    public:
        const std::unique_ptr<Expression> cond;
        const std::unique_ptr<Statement> body;


        WhileStmt(std::unique_ptr<Expression> cond, std::unique_ptr<Statement> body);
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class DoStmt : public Statement {
    public:
        const std::unique_ptr<Expression> cond;
        const std::unique_ptr<Statement> body;


        DoStmt(std::unique_ptr<Expression> cond, std::unique_ptr<Statement> body);
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class ForStmt : public Statement {
    public:
        const std::unique_ptr<Expression> init;
        const std::unique_ptr<Expression> cond;
        const std::unique_ptr<Expression> after;
        const std::unique_ptr<Statement> body;


        ForStmt(std::unique_ptr<Expression> init,
                std::unique_ptr<Expression> cond,
                std::unique_ptr<Expression> after,
                std::unique_ptr<Statement> body);
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class SwitchStmt : public Statement {
    public:
        const std::unique_ptr<Expression> expr;
        const std::unique_ptr<Statement> body;


        SwitchStmt(std::unique_ptr<Expression> expr, std::unique_ptr<Statement> body);
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class Break : public Statement {
    public:
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class Continue : public Statement {
    public:
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

class Return : public Statement {
    public:
        const std::unique_ptr<Expression> value;

        Return(std::unique_ptr<Expression> value) noexcept;
        Return() noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual void to_assembly(Context& ctx, std::ostream&, const std::string& end_label, const std::string& begin_label) const override;
};

/***************************************************************/

class Expression : public AST {
    public:
        virtual ~Expression() {};

        virtual void to_python(std::string indent, std::ostream&) const override =0;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const =0;
};

// lvalues
class Identifier : public Expression {
    public:
        const std::string name;

        Identifier(std::string) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;
};

class ArraySubscript : public Expression {
    public:
        const std::unique_ptr<Expression> array;
        const std::unique_ptr<Expression> index;


        ArraySubscript(
            std::unique_ptr<Expression>,
            std::unique_ptr<Expression>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class FloatConstant : public Expression {
    double value;

    public:
        FloatConstant(double) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class IntConstant : public Expression {
    long int value;

    public:
        IntConstant(long int) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class StringConstant : public Expression {
    public:
        const std::string value;


        StringConstant(std::string) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class CharConstant : public Expression {
    public:
        const char value;


        CharConstant(char) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class SizeOfType : public Expression {
    public:
        const std::unique_ptr<Type> type;


        SizeOfType(std::unique_ptr<Type>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

enum class AssignmentType {
    PLAIN, MUL, DIV, MOD, ADD, SUB, LSHIFT, RSHIFT, AND, XOR, OR
};
std::ostream& operator<<(std::ostream&, const AssignmentType&);

// a = 5;
class Assignment : public Expression {
    public:
        const AssignmentType assignmentType;
        const std::unique_ptr<Expression> target;
        const std::unique_ptr<Expression> value;



        Assignment(
            AssignmentType,
            std::unique_ptr<Expression>,
            std::unique_ptr<Expression>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class Cast : public Expression {
    public:
        const std::unique_ptr<Type> type;
        const std::unique_ptr<Expression> expression;


        Cast(std::unique_ptr<Type>, std::unique_ptr<Expression>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

enum class BinaryOperatorType {
    MUL, DIV, MOD, ADD, SUB, LSHIFT, RSHIFT, LT, GT, LTE, GTE, EQUALS,
    NOT_EQUALS, BITWISE_AND, BITWISE_OR, BITWISE_XOR, LOGICAL_AND, LOGICAL_OR,
};
std::ostream& operator<<(std::ostream&, const BinaryOperatorType&);
void to_python(std::ostream&, const BinaryOperatorType&);

class BinaryOperator : public Expression {
    BinaryOperatorType operator_type;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    public:
        BinaryOperator(
            BinaryOperatorType,
            std::unique_ptr<Expression>,
            std::unique_ptr<Expression>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

enum class UnaryOperatorType {
    POST_INCREMENT, POST_DECREMENT, PRE_INCREMENT, PRE_DECREMENT, PLUS, NEGATE,
    NOT, BITWISE_NOT, LOGICAL_NOT, DEREFERENCE, ADDRESS_OF, SIZEOF
};

class UnaryOperator      : public Expression {
    public:
        const UnaryOperatorType operator_type;
        const std::unique_ptr<Expression> operand;


        UnaryOperator(UnaryOperatorType, std::unique_ptr<Expression>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class ArrowOperator : public Expression {
    public:
        const std::unique_ptr<Expression> left;
        const std::string right;


        ArrowOperator(std::unique_ptr<Expression>, std::string) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

class DotOperator : public Expression {
    public:
        const std::unique_ptr<Expression> left;
        const std::string right;


        DotOperator(std::unique_ptr<Expression>, std::string) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

// a ? 1 : 5
class TernaryIf : public Expression {
    public:
       const std::unique_ptr<Expression> condition;
        const std::unique_ptr<Expression> trueBranch;
        const std::unique_ptr<Expression> falseBranch;


        TernaryIf(
            std::unique_ptr<Expression>,
            std::unique_ptr<Expression>,
            std::unique_ptr<Expression>) noexcept;
        virtual void to_python(std::string indent, std::ostream&) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};

// a()
class FunctionCall : public Expression {
    public:
        const std::unique_ptr<Expression> callee;
        const std::vector<std::unique_ptr<Expression> > arguments;


        FunctionCall(
            std::unique_ptr<Expression>,
            std::vector<std::unique_ptr<Expression> >) noexcept;
        virtual void to_python(std::string indent, std::ostream& out) const override;
        virtual StorageInfo to_assembly(Context& ctx, std::ostream&, std::string name) const override;

};
