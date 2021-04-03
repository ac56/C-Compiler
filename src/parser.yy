%code requires {
    #include "AST.hpp"
    #include "parser_helpers.hpp"
    #include <memory>
    #include <algorithm>
}

%code {
    using namespace std;
    extern yy::parser::symbol_type yylex();

}

%language "c++"
%require "3.0.4"

%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define parse.trace

%parse-param { std::unique_ptr<TranslationUnit>& parse_result }

%token
    /* literals */
    IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL TYPE_NAME

    /* reserved words */
    SIZEOF TYPEDEF EXTERN STATIC AUTO REGISTER CONST VOLATILE VOID CHAR SHORT
    INT LONG FLOAT DOUBLE SIGNED UNSIGNED STRUCT UNION ENUM CASE DEFAULT IF
    SWITCH ELSE DO FOR WHILE CONTINUE BREAK RETURN

    /* Assignment operators */
    RIGHT_ASSIGN ">>="
    LEFT_ASSIGN "<<="
    ADD_ASSIGN "+="
    SUB_ASSIGN "-="
    MUL_ASSIGN "*="
    DIV_ASSIGN "/="
    MOD_ASSIGN "%="
    AND_ASSIGN "&="
    XOR_ASSIGN "^="
    OR_ASSIGN "|="

    /* Delimiters */
    LPAREN "("
    RPAREN ")"
    LBRACE "{"
    RBRACE "}"
    LBRACKET "["
    RBRACKET "]"

    /* Symbols */
    DOT "."
    QMARK "?"
    ELLIPSIS "..."
    EQ_OP "=="
    NE_OP "!="
    OR_OP "||"
    AND_OP "&&"
    SEMICOLON ";"
    COMMA ","
    COLON ":"
    EQUALS "="
    STAR "*"
    GE_OP ">="
    RIGHT_OP ">>"
    ARROW "->"
    INC_OP "++"
    DEC_OP "--"
    LE_OP "<="
    LEFT_OP "<<"
    PLUS "+"
    DIV_OP "/"
    AMPERSAND "&"
    BANG "!"
    TILDE "~"
    MINUS "-"
    MOD "%"
    LT_OP "<"
    GT_OP ">"
    XOR_OP "^"
    BITOR_OP "|"

%token END 0

%precedence RPAREN
%precedence ELSE

%type <AssignmentType> assignment_operator
%type <UnaryOperatorType> unary_operator

%type <std::string> IDENTIFIER
%type <std::string> STRING_LITERAL
%type <int> INT_CONSTANT
%type <double> FLOAT_CONSTANT
%type <std::unique_ptr<Type>> TYPE_NAME

%type <std::unique_ptr<Expression>>
    expression primary_expression postfix_expression unary_expression
    cast_expression multiplicative_expression additive_expression
    shift_expression relational_expression equality_expression and_expression
    exclusive_or_expression inclusive_or_expression logical_and_expression
    logical_or_expression conditional_expression assignment_expression
    constant_expression

%type   <std::vector<std::unique_ptr<Expression>>> argument_expression_list

%type   <std::unique_ptr<Statement>> statement
%type   <std::unique_ptr<Expression>> for_expression
%type   <std::vector<std::unique_ptr<Statement>>> statement_list
%type   <std::unique_ptr<Block>> compound_statement

%type   <std::vector<std::unique_ptr<Declaration>>> declaration
%type   <std::vector<std::unique_ptr<Declaration>>> declaration_list

%type   <DeclarationSpecifiers> declaration_specifiers
%type   <DeclarationSpecifiers> type_specifier
%type   <DeclarationSpecifiers> storage_class_specifier

%type   <std::unique_ptr<Declarator>> direct_declarator declarator
%type   <std::unique_ptr<Initializer>> initializer

%type   <std::unique_ptr<InitDeclarator>> init_declarator
%type   <std::vector<std::unique_ptr<InitDeclarator>>> init_declarator_list
%type   <int>           pointer

%type   <std::unique_ptr<TranslationUnit>>       translation_unit
%type   <std::vector<std::unique_ptr<External>>> external_declaration_list
%type   <std::unique_ptr<FunctionDefinition>>    function_definition

%type   <std::unique_ptr<Declaration>>           parameter_declaration
%type   <std::vector<std::unique_ptr<Declaration>>>           parameter_list
%type   <std::vector<std::unique_ptr<Declaration>>>           parameter_type_list

%start translation_unit

%%

translation_unit
    : external_declaration_list
        { parse_result = make_unique<TranslationUnit>(move($1)); }

external_declaration_list
    : external_declaration_list function_definition
        { $$ = move($1); $$.push_back(move($2)); }
    | external_declaration_list declaration
        {
            $$ = move($1);
            auto declarations = move($2);
            for_each(make_move_iterator(declarations.begin()), make_move_iterator(declarations.end()), [&](auto decl) {
                $$.push_back(make_unique<ExternalDeclaration>(move(decl)));
            });
        }
    | %empty
        { $$ = vector<unique_ptr<External>>(); }

function_definition
    : declaration_specifiers declarator compound_statement
    {
        auto declaration = $2->to_declaration(type_from_declaration_specifier(move($1)));
        auto& arguments = $2->get_arguments();
        vector<string> argument_names;

        for (auto it = arguments.begin(); it != arguments.end(); ++it) {
            argument_names.push_back((*it)->get_name());
        }

        $$ = make_unique<FunctionDefinition>(move(declaration), move(argument_names), move($3));
    }
    // | declarator compound_statement

 /******** EXPRESSIONS ********/

expression : assignment_expression { $$ = move($1); }

primary_expression
    : IDENTIFIER
        { $$ = make_unique<Identifier>(move($1)); }
    | INT_CONSTANT
        { $$ = make_unique<IntConstant>(move($1)); }
    | FLOAT_CONSTANT
        { $$ = make_unique<FloatConstant>(move($1)); }
    | STRING_LITERAL
        { $$ = make_unique<StringConstant>(move($1)); }
    | LPAREN expression RPAREN
        { $$ = move($2); }

postfix_expression
    : primary_expression { $$ = move($1); }
    | postfix_expression LBRACKET expression RBRACKET
        { $$ = make_unique<ArraySubscript>(move($1), move($3)); }
    | postfix_expression LPAREN argument_expression_list RPAREN
        { $$ = make_unique<FunctionCall>(move($1), move($3)); }
    | postfix_expression LPAREN RPAREN
        { $$ = make_unique<FunctionCall>(move($1), vector<unique_ptr<Expression>>()); }
    | postfix_expression DOT IDENTIFIER
        { $$ = make_unique<DotOperator>(move($1), move($3)); }
    | postfix_expression ARROW IDENTIFIER
        { $$ = make_unique<ArrowOperator>(move($1), move($3)); }
    | postfix_expression INC_OP
        { $$ = make_unique<UnaryOperator>(UnaryOperatorType::POST_INCREMENT, move($1)); }
    | postfix_expression DEC_OP
        { $$ = make_unique<UnaryOperator>(UnaryOperatorType::POST_DECREMENT, move($1)); }

unary_expression
    : postfix_expression { $$ = move($1); }
    | unary_operator cast_expression
        { $$ = make_unique<UnaryOperator>(move($1), move($2)); }
    | INC_OP unary_expression
        { $$ = make_unique<UnaryOperator>(UnaryOperatorType::PRE_INCREMENT, move($2)); }
    | DEC_OP unary_expression
        { $$ = make_unique<UnaryOperator>(UnaryOperatorType::PRE_DECREMENT, move($2)); }
    | SIZEOF unary_expression
        { $$ = make_unique<UnaryOperator>(UnaryOperatorType::SIZEOF, move($2)); }
    | SIZEOF LPAREN TYPE_NAME RPAREN
        { $$ = make_unique<SizeOfType>(move($3)); }

cast_expression
    : unary_expression { $$ = move($1); }
    | LPAREN TYPE_NAME RPAREN cast_expression
        { $$ = make_unique<Cast>(move($2), move($4)); }

argument_expression_list
    : assignment_expression
        { $$ = vector<unique_ptr<Expression>>(); $$.push_back(move($1)); }
    | argument_expression_list COMMA assignment_expression
        { $$ = move($1); $$.push_back(move($3)); }

multiplicative_expression
    : cast_expression { $$ = move($1); }
    | multiplicative_expression STAR cast_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::MUL, move($1), move($3)); }
    | multiplicative_expression DIV_OP cast_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::DIV, move($1), move($3)); }
    | multiplicative_expression MOD cast_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::MOD, move($1), move($3)); }

additive_expression
    : multiplicative_expression { $$ = move($1); }
    | additive_expression PLUS multiplicative_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::ADD, move($1), move($3)); }
    | additive_expression MINUS multiplicative_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::SUB, move($1), move($3)); }

shift_expression
    : additive_expression { $$ = move($1); }
    | shift_expression RIGHT_OP additive_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::RSHIFT, move($1), move($3)); }
    | shift_expression LEFT_OP additive_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::LSHIFT, move($1), move($3)); }

relational_expression
    : shift_expression { $$ = move($1); }
    | relational_expression LT_OP shift_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::LT, move($1), move($3)); }
    | relational_expression GT_OP shift_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::GT, move($1), move($3)); }
    | relational_expression LE_OP shift_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::LTE, move($1), move($3)); }
    | relational_expression GE_OP shift_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::GTE, move($1), move($3)); }

equality_expression
    : relational_expression { $$ = move($1); }
    | equality_expression EQ_OP relational_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::EQUALS, move($1), move($3)); }
    | equality_expression NE_OP relational_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::NOT_EQUALS, move($1), move($3)); }

and_expression
    : equality_expression { $$ = move($1); }
    | and_expression AMPERSAND equality_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::BITWISE_AND, move($1), move($3)); }

exclusive_or_expression
    : and_expression { $$ = move($1); }
    | exclusive_or_expression XOR_OP and_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::BITWISE_XOR, move($1), move($3)); }

inclusive_or_expression
    : exclusive_or_expression { $$ = move($1); }
    | inclusive_or_expression BITOR_OP exclusive_or_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::BITWISE_OR, move($1), move($3)); }

logical_and_expression
    : inclusive_or_expression { $$ = move($1); }
    | logical_and_expression AND_OP inclusive_or_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::LOGICAL_AND, move($1), move($3)); }

logical_or_expression
    : logical_and_expression { $$ = move($1); }
    | logical_or_expression OR_OP logical_and_expression
        { $$ = make_unique<BinaryOperator>(BinaryOperatorType::LOGICAL_OR, move($1), move($3)); }

conditional_expression
    : logical_or_expression { $$ = move($1); }
    | logical_or_expression QMARK expression COLON conditional_expression
        { $$ = make_unique<TernaryIf>(move($1), move($3), move($5)); }

assignment_expression
    : conditional_expression { $$ = move($1); }
    | unary_expression assignment_operator assignment_expression
        { $$ = make_unique<Assignment>(move($2), move($1), move($3)); }

 // Not doing the comma operator

constant_expression:
    conditional_expression { $$ = move($1); }

assignment_operator
    : EQUALS       { $$ = AssignmentType::PLAIN; }
    | RIGHT_ASSIGN { $$ = AssignmentType::RSHIFT; }
    | LEFT_ASSIGN  { $$ = AssignmentType::LSHIFT; }
    | ADD_ASSIGN   { $$ = AssignmentType::ADD; }
    | SUB_ASSIGN   { $$ = AssignmentType::SUB; }
    | MUL_ASSIGN   { $$ = AssignmentType::MUL; }
    | DIV_ASSIGN   { $$ = AssignmentType::DIV; }
    | MOD_ASSIGN   { $$ = AssignmentType::MOD; }
    | AND_ASSIGN   { $$ = AssignmentType::AND; }
    | XOR_ASSIGN   { $$ = AssignmentType::XOR; }
    | OR_ASSIGN    { $$ = AssignmentType::OR; }

unary_operator
    : AMPERSAND { $$ = UnaryOperatorType::ADDRESS_OF; }
    | STAR      { $$ = UnaryOperatorType::DEREFERENCE; }
    | PLUS      { $$ = UnaryOperatorType::PLUS; }
    | MINUS     { $$ = UnaryOperatorType::NEGATE; }
    | TILDE     { $$ = UnaryOperatorType::BITWISE_NOT; }
    | BANG      { $$ = UnaryOperatorType::NOT; }

/******** DECLARATIONS ********/
declaration
    : declaration_specifiers init_declarator_list SEMICOLON
    {
        unique_ptr<Type> specified_type = type_from_declaration_specifier(move($1));
        auto declarators = move($2);
        for (auto dec = declarators.begin(); dec != declarators.end(); ++dec) {
            $$.push_back((*dec)->to_declaration(specified_type->clone()));
        }
    }
    | declaration_specifiers SEMICOLON
        { $$ = vector<unique_ptr<Declaration>>(); }


declaration_specifiers
    : storage_class_specifier declaration_specifiers
        { $$ = $1 | $2; }
    | type_specifier declaration_specifiers
        { $$ = $1 | $2; }
    | type_specifier
    | storage_class_specifier

init_declarator_list
    : init_declarator
        { $$.push_back(move($1)); }
    | init_declarator_list COMMA init_declarator
        { $$ = move($1); $$.push_back(move($3)); }

init_declarator
    : declarator
        { $$ = make_unique<InitDeclarator>(move($1), nullptr); }
    | declarator EQUALS initializer
        { $$ = make_unique<InitDeclarator>(move($1), move($3)); }

declarator
    : pointer direct_declarator
        { $$ = make_unique<PointerDeclarator>(move($2)); }
    | direct_declarator { $$ = move($1); }

direct_declarator
    : IDENTIFIER
        { $$ = make_unique<IdentifierDeclarator>(move($1)); }
    | LPAREN declarator RPAREN
        { $$ = move($2); }
    | direct_declarator LBRACKET constant_expression RBRACKET
        { $$ = make_unique<ArrayDeclarator>(move($1), move($3)); }
    | direct_declarator LBRACKET RBRACKET
        { $$ = make_unique<ArrayDeclarator>(move($1), nullptr); }
    | direct_declarator LPAREN parameter_type_list RPAREN
        { $$ = make_unique<FunctionDeclarator>(move($1), move($3)); }
      /* Function declarator that doesn't specify parameter types ??? */
      /* | direct_declarator LPAREN identifier_list RPAREN */
    | direct_declarator LPAREN RPAREN
        { $$ = make_unique<FunctionDeclarator>(move($1), vector<unique_ptr<Declaration>>()); }

/* identifier_list */
/*     : IDENTIFIER */
/*     | identifier_list COMMA IDENTIFIER */

pointer
    : STAR         { $$ = 1; }
    | STAR pointer { $$ = $2 + 1; }
    /* | STAR type_qualifier_list pointer */
    /* | STAR type_qualifier_list */

parameter_type_list
    : parameter_list { $$ = move($1); }
    /* | parameter_list COMMA ELLIPSIS */

parameter_list
    : parameter_declaration
        { $$.push_back(move($1)); }
    | parameter_list COMMA parameter_declaration
        { $$ = move($1); $$.push_back(move($3)); }

parameter_declaration
    : declaration_specifiers declarator
        { $$ = $2->to_declaration(type_from_declaration_specifier(move($1))); }
    /* | declaration_specifiers */
    /*     { $$.push_back(move($1)); } */
    /* | declaration_specifiers abstract_declarator */

/* abstract_declarator */
/*     : pointer */
/*     | pointer direct_abstract_declarator */
/*     | direct_abstract_declarator */

/* direct_abstract_declarator */
/*     : LPAREN abstract_declarator RPAREN */
/*     | direct_abstract_declarator LBRACKET constant_expression RBRACKET */
/*     | direct_abstract_declarator LBRACKET RBRACKET */
/*     | LBRACKET constant_expression RBRACKET */
/*     | LBRACKET RBRACKET */
/*     | direct_abstract_declarator LPAREN parameter_type_list RPAREN */
/*     | direct_abstract_declarator LPAREN RPAREN */
/*     | LPAREN parameter_type_list  RPAREN */
/*     | LPAREN RPAREN */

initializer
    : expression
        { $$ = make_unique<ExpressionInitializer>(move($1)); }
    /* | LBRACE initializer_list RBRACE */
    /* | LBRACE initializer_list COMMA RBRACE */

/* initializer_list */
/*     : initializer */
/*     | initializer_list COMMA initializer */

storage_class_specifier
    : TYPEDEF { $$ = DECSPEC_TYPEDEF; }
    | EXTERN { $$ = DECSPEC_EXTERN; }
    | STATIC { $$ = DECSPEC_STATIC; }
    | AUTO { $$ = DECSPEC_AUTO; }
    | REGISTER { $$ = DECSPEC_REGISTER; }

/* Not examined */
/* type_qualifier_list */
/*     : type_qualifier */
/*     | type_qualifier_list type_qualifier */
/* type_qualifier */
/*     : CONST { $$ = TypeQualifier::CONST; } */
/*     | VOLATILE { $$ = TypeQualifier::VOLATILE; } */

type_specifier
    : VOID { $$ = DECSPEC_VOID; }
    | CHAR { $$ = DECSPEC_CHAR; }
    | SHORT { $$ = DECSPEC_SHORT; }
    | INT { $$ = DECSPEC_INT; }
    | LONG { $$ = DECSPEC_LONG; }
    | FLOAT { $$ = DECSPEC_FLOAT ; }
    | DOUBLE { $$ = DECSPEC_DOUBLE; }
    | SIGNED { $$ = DECSPEC_SIGNED; }
    | UNSIGNED { $$ = DECSPEC_UNSIGNED; }
    /* Later */
    /* | struct_or_union_specifier */
    /* | enum_specifier */
    /* | typedef_name */

/* struct_or_union_specifier */
/*     : struct_or_union IDENTIFIER LBRACE struct_declaration_list RBRACE */
/*     | struct_or_union LBRACE struct_declaration_list RBRACE */
/*     | struct_or_union IDENTIFIER */

/* struct_or_union: STRUCT | UNION */

/* struct_declaration_list */
/*     : struct_declaration */
/*     | struct_declaration_list struct_declaration */

/* struct_declaration: specifier_qualifier_list struct_declarator_list SEMICOLON */

/* specifier_qualifier_list */
/*     : type_specifier specifier_qualifier_list */
/*     | type_specifier */
/*     /\* | type_qualifier specifier_qualifier_list *\/ */
/*     /\* | type_qualifier *\/ */

/* struct_declarator_list */
/*     : struct_declarator */
/*     | struct_declarator_list COMMA struct_declarator */

/* struct_declarator */
/*     : declarator */
/*     | declarator COLON constant_expression */
/*     | COLON constant_expression */

/* enum_specifier */
/*     : ENUM IDENTIFIER LBRACE enumerator_list RBRACE */
/*     | ENUM LBRACE enumerator_list RBRACE */
/*     | ENUM IDENTIFIER */

/* enumerator_list */
/*     : enumerator */
/*     | enumerator_list COMMA enumerator */

/* enumerator */
/*     : enumeration_constant */
/*     | enumeration_constant EQUALS constant_expression */

/* enumeration_constant: IDENTIFIER */
/* typedef_name: %empty */

/******** STATEMENTS ********/

statement
    /* Labeled statement */
    /* TODO: Actually take statement labels into account */
    : IDENTIFIER COLON statement
        { $$ = move($3); }
    | CASE constant_expression COLON statement
        { $$ = move($4); }
    | DEFAULT COLON statement
        { $$ = move($3); }
      /* Expression Statement */
    | expression SEMICOLON
        { $$ = make_unique<ExpressionStmt>(move($1)); }
    | SEMICOLON
        { $$ = make_noop(); }
      /* Compound Statement */
    | compound_statement { $$ = move($1); }
      /* Selection Statement */
    | IF LPAREN expression RPAREN statement ELSE statement
        { $$ = make_unique<IfStmt>(move($3), move($5), move($7)); }
    | IF LPAREN expression RPAREN statement
        { $$ = make_unique<IfStmt>(move($3), move($5), make_noop()); }
    | SWITCH LPAREN expression RPAREN statement
        { $$ = make_unique<SwitchStmt>(move($3), move($5)); }
      /* iteration Statement */
    | WHILE LPAREN expression RPAREN statement
        { $$ = make_unique<WhileStmt>(move($3), move($5)); }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON
        { $$ = make_unique<DoStmt>(move($5), move($2)); }
    | FOR LPAREN for_expression SEMICOLON for_expression SEMICOLON for_expression RPAREN statement
        { $$ = make_unique<ForStmt>(move($3), move($5), move($7), move($9)); }
      /* Jump Statement */
      /* Except goto */
    | CONTINUE SEMICOLON
        { $$ = make_unique<Continue>(); }
    | BREAK SEMICOLON
        { $$ = make_unique<Break>(); }
    | RETURN expression SEMICOLON
        { $$ = make_unique<Return>(move($2)); }
    | RETURN SEMICOLON
        { $$ = make_unique<Return>(); }

compound_statement
    : LBRACE declaration_list statement_list RBRACE
        { $$ = make_unique<Block>(move($2), move($3)); }
    | LBRACE declaration_list RBRACE
        { $$ = make_unique<Block>(move($2), vector<unique_ptr<Statement>>()); }
    | LBRACE statement_list RBRACE
        { $$ = make_unique<Block>(vector<unique_ptr<Declaration>>(), move($2)); }
    | LBRACE RBRACE
        { $$ = make_unique<Block>(
                vector<unique_ptr<Declaration>>(),
                vector<unique_ptr<Statement>>()); }

declaration_list
    : declaration
        { $$ = move($1); }
    | declaration_list declaration
        { $$ = move($1); auto new_decls = move($2); $$.insert($$.end(), make_move_iterator(new_decls.begin()), make_move_iterator(new_decls.end())); }

statement_list
    : statement
        { $$.push_back(move($1)); }
    | statement_list statement
        { $$ = move($1); $$.push_back(move($2)); }

for_expression
    : %empty { $$ = nullptr; }
    | expression { $$ = move($1); }

%%
