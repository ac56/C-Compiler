// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file src/parser.tab.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 1 "src/parser.yy" // lalr1.cc:401

    #include "AST.hpp"
    #include "parser_helpers.hpp"
    #include <memory>
    #include <algorithm>

#line 55 "src/parser.tab.hpp" // lalr1.cc:401

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif

#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace yy {
#line 171 "src/parser.tab.hpp" // lalr1.cc:401



  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YYASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // assignment_operator
      char dummy1[sizeof (AssignmentType)];

      // declaration_specifiers
      // storage_class_specifier
      // type_specifier
      char dummy2[sizeof (DeclarationSpecifiers)];

      // unary_operator
      char dummy3[sizeof (UnaryOperatorType)];

      // FLOAT_CONSTANT
      char dummy4[sizeof (double)];

      // INT_CONSTANT
      // pointer
      char dummy5[sizeof (int)];

      // IDENTIFIER
      // STRING_LITERAL
      char dummy6[sizeof (std::string)];

      // compound_statement
      char dummy7[sizeof (std::unique_ptr<Block>)];

      // parameter_declaration
      char dummy8[sizeof (std::unique_ptr<Declaration>)];

      // declarator
      // direct_declarator
      char dummy9[sizeof (std::unique_ptr<Declarator>)];

      // expression
      // primary_expression
      // postfix_expression
      // unary_expression
      // cast_expression
      // multiplicative_expression
      // additive_expression
      // shift_expression
      // relational_expression
      // equality_expression
      // and_expression
      // exclusive_or_expression
      // inclusive_or_expression
      // logical_and_expression
      // logical_or_expression
      // conditional_expression
      // assignment_expression
      // constant_expression
      // for_expression
      char dummy10[sizeof (std::unique_ptr<Expression>)];

      // function_definition
      char dummy11[sizeof (std::unique_ptr<FunctionDefinition>)];

      // init_declarator
      char dummy12[sizeof (std::unique_ptr<InitDeclarator>)];

      // initializer
      char dummy13[sizeof (std::unique_ptr<Initializer>)];

      // statement
      char dummy14[sizeof (std::unique_ptr<Statement>)];

      // translation_unit
      char dummy15[sizeof (std::unique_ptr<TranslationUnit>)];

      // TYPE_NAME
      char dummy16[sizeof (std::unique_ptr<Type>)];

      // declaration
      // parameter_type_list
      // parameter_list
      // declaration_list
      char dummy17[sizeof (std::vector<std::unique_ptr<Declaration>>)];

      // argument_expression_list
      char dummy18[sizeof (std::vector<std::unique_ptr<Expression>>)];

      // external_declaration_list
      char dummy19[sizeof (std::vector<std::unique_ptr<External>>)];

      // init_declarator_list
      char dummy20[sizeof (std::vector<std::unique_ptr<InitDeclarator>>)];

      // statement_list
      char dummy21[sizeof (std::vector<std::unique_ptr<Statement>>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        IDENTIFIER = 258,
        INT_CONSTANT = 259,
        FLOAT_CONSTANT = 260,
        STRING_LITERAL = 261,
        TYPE_NAME = 262,
        SIZEOF = 263,
        TYPEDEF = 264,
        EXTERN = 265,
        STATIC = 266,
        AUTO = 267,
        REGISTER = 268,
        CONST = 269,
        VOLATILE = 270,
        VOID = 271,
        CHAR = 272,
        SHORT = 273,
        INT = 274,
        LONG = 275,
        FLOAT = 276,
        DOUBLE = 277,
        SIGNED = 278,
        UNSIGNED = 279,
        STRUCT = 280,
        UNION = 281,
        ENUM = 282,
        CASE = 283,
        DEFAULT = 284,
        IF = 285,
        SWITCH = 286,
        ELSE = 287,
        DO = 288,
        FOR = 289,
        WHILE = 290,
        CONTINUE = 291,
        BREAK = 292,
        RETURN = 293,
        RIGHT_ASSIGN = 294,
        LEFT_ASSIGN = 295,
        ADD_ASSIGN = 296,
        SUB_ASSIGN = 297,
        MUL_ASSIGN = 298,
        DIV_ASSIGN = 299,
        MOD_ASSIGN = 300,
        AND_ASSIGN = 301,
        XOR_ASSIGN = 302,
        OR_ASSIGN = 303,
        LPAREN = 304,
        RPAREN = 305,
        LBRACE = 306,
        RBRACE = 307,
        LBRACKET = 308,
        RBRACKET = 309,
        DOT = 310,
        QMARK = 311,
        ELLIPSIS = 312,
        EQ_OP = 313,
        NE_OP = 314,
        OR_OP = 315,
        AND_OP = 316,
        SEMICOLON = 317,
        COMMA = 318,
        COLON = 319,
        EQUALS = 320,
        STAR = 321,
        GE_OP = 322,
        RIGHT_OP = 323,
        ARROW = 324,
        INC_OP = 325,
        DEC_OP = 326,
        LE_OP = 327,
        LEFT_OP = 328,
        PLUS = 329,
        DIV_OP = 330,
        AMPERSAND = 331,
        BANG = 332,
        TILDE = 333,
        MINUS = 334,
        MOD = 335,
        LT_OP = 336,
        GT_OP = 337,
        XOR_OP = 338,
        BITOR_OP = 339
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, AssignmentType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const AssignmentType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DeclarationSpecifiers&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DeclarationSpecifiers& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UnaryOperatorType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UnaryOperatorType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<Block>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<Block>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<Declaration>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<Declaration>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<Declarator>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<Declarator>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<Expression>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<Expression>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<FunctionDefinition>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<FunctionDefinition>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<InitDeclarator>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<InitDeclarator>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<Initializer>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<Initializer>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<Statement>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<Statement>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<TranslationUnit>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<TranslationUnit>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::unique_ptr<Type>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::unique_ptr<Type>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::unique_ptr<Declaration>>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::unique_ptr<Declaration>>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::unique_ptr<Expression>>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::unique_ptr<Expression>>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::unique_ptr<External>>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::unique_ptr<External>>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::unique_ptr<InitDeclarator>>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::unique_ptr<InitDeclarator>>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::unique_ptr<Statement>>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::unique_ptr<Statement>>& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_number_type yytype = this->type_get ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yytype)
        {
       default:
          break;
        }

        // Type destructor.
switch (yytype)
    {
      case 108: // assignment_operator
        value.template destroy< AssignmentType > ();
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        value.template destroy< DeclarationSpecifiers > ();
        break;

      case 109: // unary_operator
        value.template destroy< UnaryOperatorType > ();
        break;

      case 5: // FLOAT_CONSTANT
        value.template destroy< double > ();
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        value.template destroy< int > ();
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        value.template destroy< std::string > ();
        break;

      case 124: // compound_statement
        value.template destroy< std::unique_ptr<Block> > ();
        break;

      case 119: // parameter_declaration
        value.template destroy< std::unique_ptr<Declaration> > ();
        break;

      case 114: // declarator
      case 115: // direct_declarator
        value.template destroy< std::unique_ptr<Declarator> > ();
        break;

      case 89: // expression
      case 90: // primary_expression
      case 91: // postfix_expression
      case 92: // unary_expression
      case 93: // cast_expression
      case 95: // multiplicative_expression
      case 96: // additive_expression
      case 97: // shift_expression
      case 98: // relational_expression
      case 99: // equality_expression
      case 100: // and_expression
      case 101: // exclusive_or_expression
      case 102: // inclusive_or_expression
      case 103: // logical_and_expression
      case 104: // logical_or_expression
      case 105: // conditional_expression
      case 106: // assignment_expression
      case 107: // constant_expression
      case 127: // for_expression
        value.template destroy< std::unique_ptr<Expression> > ();
        break;

      case 88: // function_definition
        value.template destroy< std::unique_ptr<FunctionDefinition> > ();
        break;

      case 113: // init_declarator
        value.template destroy< std::unique_ptr<InitDeclarator> > ();
        break;

      case 120: // initializer
        value.template destroy< std::unique_ptr<Initializer> > ();
        break;

      case 123: // statement
        value.template destroy< std::unique_ptr<Statement> > ();
        break;

      case 86: // translation_unit
        value.template destroy< std::unique_ptr<TranslationUnit> > ();
        break;

      case 7: // TYPE_NAME
        value.template destroy< std::unique_ptr<Type> > ();
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        value.template destroy< std::vector<std::unique_ptr<Declaration>> > ();
        break;

      case 94: // argument_expression_list
        value.template destroy< std::vector<std::unique_ptr<Expression>> > ();
        break;

      case 87: // external_declaration_list
        value.template destroy< std::vector<std::unique_ptr<External>> > ();
        break;

      case 112: // init_declarator_list
        value.template destroy< std::vector<std::unique_ptr<InitDeclarator>> > ();
        break;

      case 126: // statement_list
        value.template destroy< std::vector<std::unique_ptr<Statement>> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The token.
      token_type token () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YYASSERT (tok == token::END || tok == token::SIZEOF || tok == token::TYPEDEF || tok == token::EXTERN || tok == token::STATIC || tok == token::AUTO || tok == token::REGISTER || tok == token::CONST || tok == token::VOLATILE || tok == token::VOID || tok == token::CHAR || tok == token::SHORT || tok == token::INT || tok == token::LONG || tok == token::FLOAT || tok == token::DOUBLE || tok == token::SIGNED || tok == token::UNSIGNED || tok == token::STRUCT || tok == token::UNION || tok == token::ENUM || tok == token::CASE || tok == token::DEFAULT || tok == token::IF || tok == token::SWITCH || tok == token::ELSE || tok == token::DO || tok == token::FOR || tok == token::WHILE || tok == token::CONTINUE || tok == token::BREAK || tok == token::RETURN || tok == token::RIGHT_ASSIGN || tok == token::LEFT_ASSIGN || tok == token::ADD_ASSIGN || tok == token::SUB_ASSIGN || tok == token::MUL_ASSIGN || tok == token::DIV_ASSIGN || tok == token::MOD_ASSIGN || tok == token::AND_ASSIGN || tok == token::XOR_ASSIGN || tok == token::OR_ASSIGN || tok == token::LPAREN || tok == token::RPAREN || tok == token::LBRACE || tok == token::RBRACE || tok == token::LBRACKET || tok == token::RBRACKET || tok == token::DOT || tok == token::QMARK || tok == token::ELLIPSIS || tok == token::EQ_OP || tok == token::NE_OP || tok == token::OR_OP || tok == token::AND_OP || tok == token::SEMICOLON || tok == token::COMMA || tok == token::COLON || tok == token::EQUALS || tok == token::STAR || tok == token::GE_OP || tok == token::RIGHT_OP || tok == token::ARROW || tok == token::INC_OP || tok == token::DEC_OP || tok == token::LE_OP || tok == token::LEFT_OP || tok == token::PLUS || tok == token::DIV_OP || tok == token::AMPERSAND || tok == token::BANG || tok == token::TILDE || tok == token::MINUS || tok == token::MOD || tok == token::LT_OP || tok == token::GT_OP || tok == token::XOR_OP || tok == token::BITOR_OP);
      }
#else
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YYASSERT (tok == token::END || tok == token::SIZEOF || tok == token::TYPEDEF || tok == token::EXTERN || tok == token::STATIC || tok == token::AUTO || tok == token::REGISTER || tok == token::CONST || tok == token::VOLATILE || tok == token::VOID || tok == token::CHAR || tok == token::SHORT || tok == token::INT || tok == token::LONG || tok == token::FLOAT || tok == token::DOUBLE || tok == token::SIGNED || tok == token::UNSIGNED || tok == token::STRUCT || tok == token::UNION || tok == token::ENUM || tok == token::CASE || tok == token::DEFAULT || tok == token::IF || tok == token::SWITCH || tok == token::ELSE || tok == token::DO || tok == token::FOR || tok == token::WHILE || tok == token::CONTINUE || tok == token::BREAK || tok == token::RETURN || tok == token::RIGHT_ASSIGN || tok == token::LEFT_ASSIGN || tok == token::ADD_ASSIGN || tok == token::SUB_ASSIGN || tok == token::MUL_ASSIGN || tok == token::DIV_ASSIGN || tok == token::MOD_ASSIGN || tok == token::AND_ASSIGN || tok == token::XOR_ASSIGN || tok == token::OR_ASSIGN || tok == token::LPAREN || tok == token::RPAREN || tok == token::LBRACE || tok == token::RBRACE || tok == token::LBRACKET || tok == token::RBRACKET || tok == token::DOT || tok == token::QMARK || tok == token::ELLIPSIS || tok == token::EQ_OP || tok == token::NE_OP || tok == token::OR_OP || tok == token::AND_OP || tok == token::SEMICOLON || tok == token::COMMA || tok == token::COLON || tok == token::EQUALS || tok == token::STAR || tok == token::GE_OP || tok == token::RIGHT_OP || tok == token::ARROW || tok == token::INC_OP || tok == token::DEC_OP || tok == token::LE_OP || tok == token::LEFT_OP || tok == token::PLUS || tok == token::DIV_OP || tok == token::AMPERSAND || tok == token::BANG || tok == token::TILDE || tok == token::MINUS || tok == token::MOD || tok == token::LT_OP || tok == token::GT_OP || tok == token::XOR_OP || tok == token::BITOR_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v)
        : super_type(token_type (tok), std::move (v))
      {
        YYASSERT (tok == token::FLOAT_CONSTANT);
      }
#else
      symbol_type (int tok, const double& v)
        : super_type(token_type (tok), v)
      {
        YYASSERT (tok == token::FLOAT_CONSTANT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v)
        : super_type(token_type (tok), std::move (v))
      {
        YYASSERT (tok == token::INT_CONSTANT);
      }
#else
      symbol_type (int tok, const int& v)
        : super_type(token_type (tok), v)
      {
        YYASSERT (tok == token::INT_CONSTANT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type(token_type (tok), std::move (v))
      {
        YYASSERT (tok == token::IDENTIFIER || tok == token::STRING_LITERAL);
      }
#else
      symbol_type (int tok, const std::string& v)
        : super_type(token_type (tok), v)
      {
        YYASSERT (tok == token::IDENTIFIER || tok == token::STRING_LITERAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::unique_ptr<Type> v)
        : super_type(token_type (tok), std::move (v))
      {
        YYASSERT (tok == token::TYPE_NAME);
      }
#else
      symbol_type (int tok, const std::unique_ptr<Type>& v)
        : super_type(token_type (tok), v)
      {
        YYASSERT (tok == token::TYPE_NAME);
      }
#endif
    };

    /// Build a parser object.
    parser (std::unique_ptr<TranslationUnit>& parse_result_yyarg);
    virtual ~parser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END ()
      {
        return symbol_type (token::END);
      }
#else
      static
      symbol_type
      make_END ()
      {
        return symbol_type (token::END);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v)
      {
        return symbol_type (token::IDENTIFIER, std::move (v));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v)
      {
        return symbol_type (token::IDENTIFIER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT_CONSTANT (int v)
      {
        return symbol_type (token::INT_CONSTANT, std::move (v));
      }
#else
      static
      symbol_type
      make_INT_CONSTANT (const int& v)
      {
        return symbol_type (token::INT_CONSTANT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT_CONSTANT (double v)
      {
        return symbol_type (token::FLOAT_CONSTANT, std::move (v));
      }
#else
      static
      symbol_type
      make_FLOAT_CONSTANT (const double& v)
      {
        return symbol_type (token::FLOAT_CONSTANT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_LITERAL (std::string v)
      {
        return symbol_type (token::STRING_LITERAL, std::move (v));
      }
#else
      static
      symbol_type
      make_STRING_LITERAL (const std::string& v)
      {
        return symbol_type (token::STRING_LITERAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE_NAME (std::unique_ptr<Type> v)
      {
        return symbol_type (token::TYPE_NAME, std::move (v));
      }
#else
      static
      symbol_type
      make_TYPE_NAME (const std::unique_ptr<Type>& v)
      {
        return symbol_type (token::TYPE_NAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIZEOF ()
      {
        return symbol_type (token::SIZEOF);
      }
#else
      static
      symbol_type
      make_SIZEOF ()
      {
        return symbol_type (token::SIZEOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPEDEF ()
      {
        return symbol_type (token::TYPEDEF);
      }
#else
      static
      symbol_type
      make_TYPEDEF ()
      {
        return symbol_type (token::TYPEDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXTERN ()
      {
        return symbol_type (token::EXTERN);
      }
#else
      static
      symbol_type
      make_EXTERN ()
      {
        return symbol_type (token::EXTERN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STATIC ()
      {
        return symbol_type (token::STATIC);
      }
#else
      static
      symbol_type
      make_STATIC ()
      {
        return symbol_type (token::STATIC);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AUTO ()
      {
        return symbol_type (token::AUTO);
      }
#else
      static
      symbol_type
      make_AUTO ()
      {
        return symbol_type (token::AUTO);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REGISTER ()
      {
        return symbol_type (token::REGISTER);
      }
#else
      static
      symbol_type
      make_REGISTER ()
      {
        return symbol_type (token::REGISTER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONST ()
      {
        return symbol_type (token::CONST);
      }
#else
      static
      symbol_type
      make_CONST ()
      {
        return symbol_type (token::CONST);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOLATILE ()
      {
        return symbol_type (token::VOLATILE);
      }
#else
      static
      symbol_type
      make_VOLATILE ()
      {
        return symbol_type (token::VOLATILE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOID ()
      {
        return symbol_type (token::VOID);
      }
#else
      static
      symbol_type
      make_VOID ()
      {
        return symbol_type (token::VOID);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR ()
      {
        return symbol_type (token::CHAR);
      }
#else
      static
      symbol_type
      make_CHAR ()
      {
        return symbol_type (token::CHAR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SHORT ()
      {
        return symbol_type (token::SHORT);
      }
#else
      static
      symbol_type
      make_SHORT ()
      {
        return symbol_type (token::SHORT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT ()
      {
        return symbol_type (token::INT);
      }
#else
      static
      symbol_type
      make_INT ()
      {
        return symbol_type (token::INT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LONG ()
      {
        return symbol_type (token::LONG);
      }
#else
      static
      symbol_type
      make_LONG ()
      {
        return symbol_type (token::LONG);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT ()
      {
        return symbol_type (token::FLOAT);
      }
#else
      static
      symbol_type
      make_FLOAT ()
      {
        return symbol_type (token::FLOAT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLE ()
      {
        return symbol_type (token::DOUBLE);
      }
#else
      static
      symbol_type
      make_DOUBLE ()
      {
        return symbol_type (token::DOUBLE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIGNED ()
      {
        return symbol_type (token::SIGNED);
      }
#else
      static
      symbol_type
      make_SIGNED ()
      {
        return symbol_type (token::SIGNED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNSIGNED ()
      {
        return symbol_type (token::UNSIGNED);
      }
#else
      static
      symbol_type
      make_UNSIGNED ()
      {
        return symbol_type (token::UNSIGNED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRUCT ()
      {
        return symbol_type (token::STRUCT);
      }
#else
      static
      symbol_type
      make_STRUCT ()
      {
        return symbol_type (token::STRUCT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNION ()
      {
        return symbol_type (token::UNION);
      }
#else
      static
      symbol_type
      make_UNION ()
      {
        return symbol_type (token::UNION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENUM ()
      {
        return symbol_type (token::ENUM);
      }
#else
      static
      symbol_type
      make_ENUM ()
      {
        return symbol_type (token::ENUM);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE ()
      {
        return symbol_type (token::CASE);
      }
#else
      static
      symbol_type
      make_CASE ()
      {
        return symbol_type (token::CASE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT ()
      {
        return symbol_type (token::DEFAULT);
      }
#else
      static
      symbol_type
      make_DEFAULT ()
      {
        return symbol_type (token::DEFAULT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::IF);
      }
#else
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::IF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SWITCH ()
      {
        return symbol_type (token::SWITCH);
      }
#else
      static
      symbol_type
      make_SWITCH ()
      {
        return symbol_type (token::SWITCH);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#else
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO ()
      {
        return symbol_type (token::DO);
      }
#else
      static
      symbol_type
      make_DO ()
      {
        return symbol_type (token::DO);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#else
      static
      symbol_type
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::WHILE);
      }
#else
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::WHILE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONTINUE ()
      {
        return symbol_type (token::CONTINUE);
      }
#else
      static
      symbol_type
      make_CONTINUE ()
      {
        return symbol_type (token::CONTINUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BREAK ()
      {
        return symbol_type (token::BREAK);
      }
#else
      static
      symbol_type
      make_BREAK ()
      {
        return symbol_type (token::BREAK);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN ()
      {
        return symbol_type (token::RETURN);
      }
#else
      static
      symbol_type
      make_RETURN ()
      {
        return symbol_type (token::RETURN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RIGHT_ASSIGN ()
      {
        return symbol_type (token::RIGHT_ASSIGN);
      }
#else
      static
      symbol_type
      make_RIGHT_ASSIGN ()
      {
        return symbol_type (token::RIGHT_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEFT_ASSIGN ()
      {
        return symbol_type (token::LEFT_ASSIGN);
      }
#else
      static
      symbol_type
      make_LEFT_ASSIGN ()
      {
        return symbol_type (token::LEFT_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD_ASSIGN ()
      {
        return symbol_type (token::ADD_ASSIGN);
      }
#else
      static
      symbol_type
      make_ADD_ASSIGN ()
      {
        return symbol_type (token::ADD_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB_ASSIGN ()
      {
        return symbol_type (token::SUB_ASSIGN);
      }
#else
      static
      symbol_type
      make_SUB_ASSIGN ()
      {
        return symbol_type (token::SUB_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL_ASSIGN ()
      {
        return symbol_type (token::MUL_ASSIGN);
      }
#else
      static
      symbol_type
      make_MUL_ASSIGN ()
      {
        return symbol_type (token::MUL_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV_ASSIGN ()
      {
        return symbol_type (token::DIV_ASSIGN);
      }
#else
      static
      symbol_type
      make_DIV_ASSIGN ()
      {
        return symbol_type (token::DIV_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD_ASSIGN ()
      {
        return symbol_type (token::MOD_ASSIGN);
      }
#else
      static
      symbol_type
      make_MOD_ASSIGN ()
      {
        return symbol_type (token::MOD_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND_ASSIGN ()
      {
        return symbol_type (token::AND_ASSIGN);
      }
#else
      static
      symbol_type
      make_AND_ASSIGN ()
      {
        return symbol_type (token::AND_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR_ASSIGN ()
      {
        return symbol_type (token::XOR_ASSIGN);
      }
#else
      static
      symbol_type
      make_XOR_ASSIGN ()
      {
        return symbol_type (token::XOR_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR_ASSIGN ()
      {
        return symbol_type (token::OR_ASSIGN);
      }
#else
      static
      symbol_type
      make_OR_ASSIGN ()
      {
        return symbol_type (token::OR_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN ()
      {
        return symbol_type (token::LPAREN);
      }
#else
      static
      symbol_type
      make_LPAREN ()
      {
        return symbol_type (token::LPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN ()
      {
        return symbol_type (token::RPAREN);
      }
#else
      static
      symbol_type
      make_RPAREN ()
      {
        return symbol_type (token::RPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACE ()
      {
        return symbol_type (token::LBRACE);
      }
#else
      static
      symbol_type
      make_LBRACE ()
      {
        return symbol_type (token::LBRACE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACE ()
      {
        return symbol_type (token::RBRACE);
      }
#else
      static
      symbol_type
      make_RBRACE ()
      {
        return symbol_type (token::RBRACE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LBRACKET ()
      {
        return symbol_type (token::LBRACKET);
      }
#else
      static
      symbol_type
      make_LBRACKET ()
      {
        return symbol_type (token::LBRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RBRACKET ()
      {
        return symbol_type (token::RBRACKET);
      }
#else
      static
      symbol_type
      make_RBRACKET ()
      {
        return symbol_type (token::RBRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT ()
      {
        return symbol_type (token::DOT);
      }
#else
      static
      symbol_type
      make_DOT ()
      {
        return symbol_type (token::DOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_QMARK ()
      {
        return symbol_type (token::QMARK);
      }
#else
      static
      symbol_type
      make_QMARK ()
      {
        return symbol_type (token::QMARK);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELLIPSIS ()
      {
        return symbol_type (token::ELLIPSIS);
      }
#else
      static
      symbol_type
      make_ELLIPSIS ()
      {
        return symbol_type (token::ELLIPSIS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ_OP ()
      {
        return symbol_type (token::EQ_OP);
      }
#else
      static
      symbol_type
      make_EQ_OP ()
      {
        return symbol_type (token::EQ_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NE_OP ()
      {
        return symbol_type (token::NE_OP);
      }
#else
      static
      symbol_type
      make_NE_OP ()
      {
        return symbol_type (token::NE_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR_OP ()
      {
        return symbol_type (token::OR_OP);
      }
#else
      static
      symbol_type
      make_OR_OP ()
      {
        return symbol_type (token::OR_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND_OP ()
      {
        return symbol_type (token::AND_OP);
      }
#else
      static
      symbol_type
      make_AND_OP ()
      {
        return symbol_type (token::AND_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::SEMICOLON);
      }
#else
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::SEMICOLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#else
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON ()
      {
        return symbol_type (token::COLON);
      }
#else
      static
      symbol_type
      make_COLON ()
      {
        return symbol_type (token::COLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUALS ()
      {
        return symbol_type (token::EQUALS);
      }
#else
      static
      symbol_type
      make_EQUALS ()
      {
        return symbol_type (token::EQUALS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR ()
      {
        return symbol_type (token::STAR);
      }
#else
      static
      symbol_type
      make_STAR ()
      {
        return symbol_type (token::STAR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE_OP ()
      {
        return symbol_type (token::GE_OP);
      }
#else
      static
      symbol_type
      make_GE_OP ()
      {
        return symbol_type (token::GE_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RIGHT_OP ()
      {
        return symbol_type (token::RIGHT_OP);
      }
#else
      static
      symbol_type
      make_RIGHT_OP ()
      {
        return symbol_type (token::RIGHT_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW ()
      {
        return symbol_type (token::ARROW);
      }
#else
      static
      symbol_type
      make_ARROW ()
      {
        return symbol_type (token::ARROW);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INC_OP ()
      {
        return symbol_type (token::INC_OP);
      }
#else
      static
      symbol_type
      make_INC_OP ()
      {
        return symbol_type (token::INC_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEC_OP ()
      {
        return symbol_type (token::DEC_OP);
      }
#else
      static
      symbol_type
      make_DEC_OP ()
      {
        return symbol_type (token::DEC_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE_OP ()
      {
        return symbol_type (token::LE_OP);
      }
#else
      static
      symbol_type
      make_LE_OP ()
      {
        return symbol_type (token::LE_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEFT_OP ()
      {
        return symbol_type (token::LEFT_OP);
      }
#else
      static
      symbol_type
      make_LEFT_OP ()
      {
        return symbol_type (token::LEFT_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS ()
      {
        return symbol_type (token::PLUS);
      }
#else
      static
      symbol_type
      make_PLUS ()
      {
        return symbol_type (token::PLUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV_OP ()
      {
        return symbol_type (token::DIV_OP);
      }
#else
      static
      symbol_type
      make_DIV_OP ()
      {
        return symbol_type (token::DIV_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AMPERSAND ()
      {
        return symbol_type (token::AMPERSAND);
      }
#else
      static
      symbol_type
      make_AMPERSAND ()
      {
        return symbol_type (token::AMPERSAND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BANG ()
      {
        return symbol_type (token::BANG);
      }
#else
      static
      symbol_type
      make_BANG ()
      {
        return symbol_type (token::BANG);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TILDE ()
      {
        return symbol_type (token::TILDE);
      }
#else
      static
      symbol_type
      make_TILDE ()
      {
        return symbol_type (token::TILDE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS ()
      {
        return symbol_type (token::MINUS);
      }
#else
      static
      symbol_type
      make_MINUS ()
      {
        return symbol_type (token::MINUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD ()
      {
        return symbol_type (token::MOD);
      }
#else
      static
      symbol_type
      make_MOD ()
      {
        return symbol_type (token::MOD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT_OP ()
      {
        return symbol_type (token::LT_OP);
      }
#else
      static
      symbol_type
      make_LT_OP ()
      {
        return symbol_type (token::LT_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GT_OP ()
      {
        return symbol_type (token::GT_OP);
      }
#else
      static
      symbol_type
      make_GT_OP ()
      {
        return symbol_type (token::GT_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR_OP ()
      {
        return symbol_type (token::XOR_OP);
      }
#else
      static
      symbol_type
      make_XOR_OP ()
      {
        return symbol_type (token::XOR_OP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BITOR_OP ()
      {
        return symbol_type (token::BITOR_OP);
      }
#else
      static
      symbol_type
      make_BITOR_OP ()
      {
        return symbol_type (token::BITOR_OP);
      }
#endif


  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (size_type i)
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (int i)
      {
        return operator[] (size_type (i));
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (size_type i) const
      {
        return seq_[size () - 1 - i];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (int i) const
      {
        return operator[] (size_type (i));
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (int n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      size_type
      size () const YY_NOEXCEPT
      {
        return seq_.size ();
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, int range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (int i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        int range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 727,     ///< Last index in yytable_.
      yynnts_ = 43,  ///< Number of nonterminal symbols.
      yyfinal_ = 3, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 85  ///< Number of tokens.
    };


    // User arguments.
    std::unique_ptr<TranslationUnit>& parse_result;
  };

  inline
  parser::token_number_type
  parser::yytranslate_ (token_type t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
    };
    const unsigned user_token_number_max_ = 339;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
  {
    switch (this->type_get ())
    {
      case 108: // assignment_operator
        value.move< AssignmentType > (std::move (that.value));
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        value.move< DeclarationSpecifiers > (std::move (that.value));
        break;

      case 109: // unary_operator
        value.move< UnaryOperatorType > (std::move (that.value));
        break;

      case 5: // FLOAT_CONSTANT
        value.move< double > (std::move (that.value));
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        value.move< int > (std::move (that.value));
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        value.move< std::string > (std::move (that.value));
        break;

      case 124: // compound_statement
        value.move< std::unique_ptr<Block> > (std::move (that.value));
        break;

      case 119: // parameter_declaration
        value.move< std::unique_ptr<Declaration> > (std::move (that.value));
        break;

      case 114: // declarator
      case 115: // direct_declarator
        value.move< std::unique_ptr<Declarator> > (std::move (that.value));
        break;

      case 89: // expression
      case 90: // primary_expression
      case 91: // postfix_expression
      case 92: // unary_expression
      case 93: // cast_expression
      case 95: // multiplicative_expression
      case 96: // additive_expression
      case 97: // shift_expression
      case 98: // relational_expression
      case 99: // equality_expression
      case 100: // and_expression
      case 101: // exclusive_or_expression
      case 102: // inclusive_or_expression
      case 103: // logical_and_expression
      case 104: // logical_or_expression
      case 105: // conditional_expression
      case 106: // assignment_expression
      case 107: // constant_expression
      case 127: // for_expression
        value.move< std::unique_ptr<Expression> > (std::move (that.value));
        break;

      case 88: // function_definition
        value.move< std::unique_ptr<FunctionDefinition> > (std::move (that.value));
        break;

      case 113: // init_declarator
        value.move< std::unique_ptr<InitDeclarator> > (std::move (that.value));
        break;

      case 120: // initializer
        value.move< std::unique_ptr<Initializer> > (std::move (that.value));
        break;

      case 123: // statement
        value.move< std::unique_ptr<Statement> > (std::move (that.value));
        break;

      case 86: // translation_unit
        value.move< std::unique_ptr<TranslationUnit> > (std::move (that.value));
        break;

      case 7: // TYPE_NAME
        value.move< std::unique_ptr<Type> > (std::move (that.value));
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        value.move< std::vector<std::unique_ptr<Declaration>> > (std::move (that.value));
        break;

      case 94: // argument_expression_list
        value.move< std::vector<std::unique_ptr<Expression>> > (std::move (that.value));
        break;

      case 87: // external_declaration_list
        value.move< std::vector<std::unique_ptr<External>> > (std::move (that.value));
        break;

      case 112: // init_declarator_list
        value.move< std::vector<std::unique_ptr<InitDeclarator>> > (std::move (that.value));
        break;

      case 126: // statement_list
        value.move< std::vector<std::unique_ptr<Statement>> > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->type_get ())
    {
      case 108: // assignment_operator
        value.copy< AssignmentType > (YY_MOVE (that.value));
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        value.copy< DeclarationSpecifiers > (YY_MOVE (that.value));
        break;

      case 109: // unary_operator
        value.copy< UnaryOperatorType > (YY_MOVE (that.value));
        break;

      case 5: // FLOAT_CONSTANT
        value.copy< double > (YY_MOVE (that.value));
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        value.copy< int > (YY_MOVE (that.value));
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case 124: // compound_statement
        value.copy< std::unique_ptr<Block> > (YY_MOVE (that.value));
        break;

      case 119: // parameter_declaration
        value.copy< std::unique_ptr<Declaration> > (YY_MOVE (that.value));
        break;

      case 114: // declarator
      case 115: // direct_declarator
        value.copy< std::unique_ptr<Declarator> > (YY_MOVE (that.value));
        break;

      case 89: // expression
      case 90: // primary_expression
      case 91: // postfix_expression
      case 92: // unary_expression
      case 93: // cast_expression
      case 95: // multiplicative_expression
      case 96: // additive_expression
      case 97: // shift_expression
      case 98: // relational_expression
      case 99: // equality_expression
      case 100: // and_expression
      case 101: // exclusive_or_expression
      case 102: // inclusive_or_expression
      case 103: // logical_and_expression
      case 104: // logical_or_expression
      case 105: // conditional_expression
      case 106: // assignment_expression
      case 107: // constant_expression
      case 127: // for_expression
        value.copy< std::unique_ptr<Expression> > (YY_MOVE (that.value));
        break;

      case 88: // function_definition
        value.copy< std::unique_ptr<FunctionDefinition> > (YY_MOVE (that.value));
        break;

      case 113: // init_declarator
        value.copy< std::unique_ptr<InitDeclarator> > (YY_MOVE (that.value));
        break;

      case 120: // initializer
        value.copy< std::unique_ptr<Initializer> > (YY_MOVE (that.value));
        break;

      case 123: // statement
        value.copy< std::unique_ptr<Statement> > (YY_MOVE (that.value));
        break;

      case 86: // translation_unit
        value.copy< std::unique_ptr<TranslationUnit> > (YY_MOVE (that.value));
        break;

      case 7: // TYPE_NAME
        value.copy< std::unique_ptr<Type> > (YY_MOVE (that.value));
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        value.copy< std::vector<std::unique_ptr<Declaration>> > (YY_MOVE (that.value));
        break;

      case 94: // argument_expression_list
        value.copy< std::vector<std::unique_ptr<Expression>> > (YY_MOVE (that.value));
        break;

      case 87: // external_declaration_list
        value.copy< std::vector<std::unique_ptr<External>> > (YY_MOVE (that.value));
        break;

      case 112: // init_declarator_list
        value.copy< std::vector<std::unique_ptr<InitDeclarator>> > (YY_MOVE (that.value));
        break;

      case 126: // statement_list
        value.copy< std::vector<std::unique_ptr<Statement>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 108: // assignment_operator
        value.move< AssignmentType > (YY_MOVE (s.value));
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        value.move< DeclarationSpecifiers > (YY_MOVE (s.value));
        break;

      case 109: // unary_operator
        value.move< UnaryOperatorType > (YY_MOVE (s.value));
        break;

      case 5: // FLOAT_CONSTANT
        value.move< double > (YY_MOVE (s.value));
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        value.move< int > (YY_MOVE (s.value));
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case 124: // compound_statement
        value.move< std::unique_ptr<Block> > (YY_MOVE (s.value));
        break;

      case 119: // parameter_declaration
        value.move< std::unique_ptr<Declaration> > (YY_MOVE (s.value));
        break;

      case 114: // declarator
      case 115: // direct_declarator
        value.move< std::unique_ptr<Declarator> > (YY_MOVE (s.value));
        break;

      case 89: // expression
      case 90: // primary_expression
      case 91: // postfix_expression
      case 92: // unary_expression
      case 93: // cast_expression
      case 95: // multiplicative_expression
      case 96: // additive_expression
      case 97: // shift_expression
      case 98: // relational_expression
      case 99: // equality_expression
      case 100: // and_expression
      case 101: // exclusive_or_expression
      case 102: // inclusive_or_expression
      case 103: // logical_and_expression
      case 104: // logical_or_expression
      case 105: // conditional_expression
      case 106: // assignment_expression
      case 107: // constant_expression
      case 127: // for_expression
        value.move< std::unique_ptr<Expression> > (YY_MOVE (s.value));
        break;

      case 88: // function_definition
        value.move< std::unique_ptr<FunctionDefinition> > (YY_MOVE (s.value));
        break;

      case 113: // init_declarator
        value.move< std::unique_ptr<InitDeclarator> > (YY_MOVE (s.value));
        break;

      case 120: // initializer
        value.move< std::unique_ptr<Initializer> > (YY_MOVE (s.value));
        break;

      case 123: // statement
        value.move< std::unique_ptr<Statement> > (YY_MOVE (s.value));
        break;

      case 86: // translation_unit
        value.move< std::unique_ptr<TranslationUnit> > (YY_MOVE (s.value));
        break;

      case 7: // TYPE_NAME
        value.move< std::unique_ptr<Type> > (YY_MOVE (s.value));
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        value.move< std::vector<std::unique_ptr<Declaration>> > (YY_MOVE (s.value));
        break;

      case 94: // argument_expression_list
        value.move< std::vector<std::unique_ptr<Expression>> > (YY_MOVE (s.value));
        break;

      case 87: // external_declaration_list
        value.move< std::vector<std::unique_ptr<External>> > (YY_MOVE (s.value));
        break;

      case 112: // init_declarator_list
        value.move< std::vector<std::unique_ptr<InitDeclarator>> > (YY_MOVE (s.value));
        break;

      case 126: // statement_list
        value.move< std::vector<std::unique_ptr<Statement>> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

  inline
  parser::token_type
  parser::by_type::token () const YY_NOEXCEPT
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339
    };
    return token_type (yytoken_number_[type]);
  }


} // yy
#line 3243 "src/parser.tab.hpp" // lalr1.cc:401




#endif // !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
