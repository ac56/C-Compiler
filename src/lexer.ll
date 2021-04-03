%{

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "parser.tab.hpp"

#define YY_DECL yy::parser::symbol_type yylex()
#undef YY_NULL
#define YY_NULL yy::parser::make_END()

%}

%option noyywrap nounput noinput batch

D           [0-9]
L           [a-zA-Z_]
H           [a-fA-F0-9]
E           [Ee][+-]?{D}+
FS          (f|F|l|L)
IS          (u|U|l|L)*


/* to return the line number and errored character in case of error */
extern int yylineno, yychar;

%%

"auto"           return yy::parser::make_AUTO();

"break"         return yy::parser::make_BREAK();
"case"          return yy::parser::make_CASE();
"char"          return yy::parser::make_CHAR();
"const"         return yy::parser::make_CONST();
"continue"      return yy::parser::make_CONTINUE();
"default"       return yy::parser::make_DEFAULT();
"do"            return yy::parser::make_DO();
"double"        return yy::parser::make_DOUBLE();
"else"          return yy::parser::make_ELSE();
"enum"          return yy::parser::make_ENUM();
"extern"        return yy::parser::make_EXTERN();
"float"         return yy::parser::make_FLOAT();
"for"           return yy::parser::make_FOR();
"if"            return yy::parser::make_IF();
"int"           return yy::parser::make_INT();
"long"          return yy::parser::make_LONG();
"register"      return yy::parser::make_REGISTER();
"return"        return yy::parser::make_RETURN();
"short"         return yy::parser::make_SHORT();
"signed"        return yy::parser::make_SIGNED();
"sizeof"        return yy::parser::make_SIZEOF();
"static"        return yy::parser::make_STATIC();
"struct"        return yy::parser::make_STRUCT();
"switch"        return yy::parser::make_SWITCH();
"typedef"       return yy::parser::make_TYPEDEF();
"union"         return yy::parser::make_UNION();
"unsigned"      return yy::parser::make_UNSIGNED();
"void"          return yy::parser::make_VOID();
"volatile"      return yy::parser::make_VOLATILE();
"while"         return yy::parser::make_WHILE();

{L}({L}|{D})* return yy::parser::make_IDENTIFIER(yytext);

0[xX]{H}+{IS}?          return yy::parser::make_INT_CONSTANT(std::stod(yytext));
0{D}+{IS}?              return yy::parser::make_INT_CONSTANT(std::stod(yytext));
{D}+{IS}?               return yy::parser::make_INT_CONSTANT(std::stod(yytext));
L?'(\\.|[^\\'])+'       return yy::parser::make_INT_CONSTANT(std::stod(yytext));
{D}+{E}{FS}?            return yy::parser::make_INT_CONSTANT(std::stod(yytext));
{D}*"."{D}+({E})?{FS}?  return yy::parser::make_INT_CONSTANT(std::stod(yytext));
{D}+"."{D}*({E})?{FS}?  return yy::parser::make_INT_CONSTANT(std::stod(yytext));

["][^\n\"]*["]          {
    std::string yystring(yytext);
    return yy::parser::make_STRING_LITERAL(yystring.substr(1, yystring.length() - 2));
}

L?\"(\\.|[^\\"])*\"     return yy::parser::make_STRING_LITERAL("string_goes_here");

"..."           return yy::parser::make_ELLIPSIS();
">>="           return yy::parser::make_RIGHT_ASSIGN();
"<<="           return yy::parser::make_LEFT_ASSIGN();
"+="            return yy::parser::make_ADD_ASSIGN();
"-="            return yy::parser::make_SUB_ASSIGN();
"*="            return yy::parser::make_MUL_ASSIGN();
"/="            return yy::parser::make_DIV_ASSIGN();
"%="            return yy::parser::make_MOD_ASSIGN();
"&="            return yy::parser::make_AND_ASSIGN();
"^="            return yy::parser::make_XOR_ASSIGN();
"|="            return yy::parser::make_OR_ASSIGN();
">>"            return yy::parser::make_RIGHT_OP();
"<<"            return yy::parser::make_LEFT_OP();
"++"            return yy::parser::make_INC_OP();
"--"            return yy::parser::make_DEC_OP();
"->"            return yy::parser::make_ARROW();
"&&"            return yy::parser::make_AND_OP();
"||"            return yy::parser::make_OR_OP();
"<="            return yy::parser::make_LE_OP();
">="            return yy::parser::make_GE_OP();
"=="            return yy::parser::make_EQ_OP();
"!="            return yy::parser::make_NE_OP();
";"             return yy::parser::make_SEMICOLON();
"{"             return yy::parser::make_LBRACE();
"}"             return yy::parser::make_RBRACE();
","             return yy::parser::make_COMMA();
":"             return yy::parser::make_COLON();
"="             return yy::parser::make_EQUALS();
"("             return yy::parser::make_LPAREN();
")"             return yy::parser::make_RPAREN();
"["             return yy::parser::make_LBRACKET();
"]"             return yy::parser::make_RBRACKET();
"."             return yy::parser::make_DOT();
"&"             return yy::parser::make_AMPERSAND();
"!"             return yy::parser::make_BANG();
"~"             return yy::parser::make_TILDE();
"-"             return yy::parser::make_MINUS();
"+"             return yy::parser::make_PLUS();
"*"             return yy::parser::make_STAR();
"/"             return yy::parser::make_DIV_OP();
"%"             return yy::parser::make_MOD();
"<"             return yy::parser::make_LT_OP();
">"             return yy::parser::make_GT_OP();
"^"             return yy::parser::make_XOR_OP();
"|"             return yy::parser::make_BITOR_OP();
"?"             return yy::parser::make_QMARK();

[ \t\v\n\f\r]       { /*ignore*/ }

. {
    fprintf (stderr, "Error: %s\n", yytext);
    exit(1);
}

%%

namespace yy {
  void parser::error (const std::string& msg) {
    std::cerr << msg << '\n';
  }
}
