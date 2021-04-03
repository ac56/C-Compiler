// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.tab.hpp"


// Unqualified %code blocks.
#line 8 "src/parser.yy" // lalr1.cc:435

    using namespace std;
    extern yy::parser::symbol_type yylex();


#line 51 "src/parser.tab.cpp" // lalr1.cc:435


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 127 "src/parser.tab.cpp" // lalr1.cc:510

  /// Build a parser object.
  parser::parser (std::unique_ptr<TranslationUnit>& parse_result_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      parse_result (parse_result_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.type_get ())
    {
      case 108: // assignment_operator
        value.YY_MOVE_OR_COPY< AssignmentType > (YY_MOVE (that.value));
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        value.YY_MOVE_OR_COPY< DeclarationSpecifiers > (YY_MOVE (that.value));
        break;

      case 109: // unary_operator
        value.YY_MOVE_OR_COPY< UnaryOperatorType > (YY_MOVE (that.value));
        break;

      case 5: // FLOAT_CONSTANT
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 124: // compound_statement
        value.YY_MOVE_OR_COPY< std::unique_ptr<Block> > (YY_MOVE (that.value));
        break;

      case 119: // parameter_declaration
        value.YY_MOVE_OR_COPY< std::unique_ptr<Declaration> > (YY_MOVE (that.value));
        break;

      case 114: // declarator
      case 115: // direct_declarator
        value.YY_MOVE_OR_COPY< std::unique_ptr<Declarator> > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< std::unique_ptr<Expression> > (YY_MOVE (that.value));
        break;

      case 88: // function_definition
        value.YY_MOVE_OR_COPY< std::unique_ptr<FunctionDefinition> > (YY_MOVE (that.value));
        break;

      case 113: // init_declarator
        value.YY_MOVE_OR_COPY< std::unique_ptr<InitDeclarator> > (YY_MOVE (that.value));
        break;

      case 120: // initializer
        value.YY_MOVE_OR_COPY< std::unique_ptr<Initializer> > (YY_MOVE (that.value));
        break;

      case 123: // statement
        value.YY_MOVE_OR_COPY< std::unique_ptr<Statement> > (YY_MOVE (that.value));
        break;

      case 86: // translation_unit
        value.YY_MOVE_OR_COPY< std::unique_ptr<TranslationUnit> > (YY_MOVE (that.value));
        break;

      case 7: // TYPE_NAME
        value.YY_MOVE_OR_COPY< std::unique_ptr<Type> > (YY_MOVE (that.value));
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<Declaration>> > (YY_MOVE (that.value));
        break;

      case 94: // argument_expression_list
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<Expression>> > (YY_MOVE (that.value));
        break;

      case 87: // external_declaration_list
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<External>> > (YY_MOVE (that.value));
        break;

      case 112: // init_declarator_list
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<InitDeclarator>> > (YY_MOVE (that.value));
        break;

      case 126: // statement_list
        value.YY_MOVE_OR_COPY< std::vector<std::unique_ptr<Statement>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.type_get ())
    {
      case 108: // assignment_operator
        value.move< AssignmentType > (YY_MOVE (that.value));
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        value.move< DeclarationSpecifiers > (YY_MOVE (that.value));
        break;

      case 109: // unary_operator
        value.move< UnaryOperatorType > (YY_MOVE (that.value));
        break;

      case 5: // FLOAT_CONSTANT
        value.move< double > (YY_MOVE (that.value));
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        value.move< int > (YY_MOVE (that.value));
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 124: // compound_statement
        value.move< std::unique_ptr<Block> > (YY_MOVE (that.value));
        break;

      case 119: // parameter_declaration
        value.move< std::unique_ptr<Declaration> > (YY_MOVE (that.value));
        break;

      case 114: // declarator
      case 115: // direct_declarator
        value.move< std::unique_ptr<Declarator> > (YY_MOVE (that.value));
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
        value.move< std::unique_ptr<Expression> > (YY_MOVE (that.value));
        break;

      case 88: // function_definition
        value.move< std::unique_ptr<FunctionDefinition> > (YY_MOVE (that.value));
        break;

      case 113: // init_declarator
        value.move< std::unique_ptr<InitDeclarator> > (YY_MOVE (that.value));
        break;

      case 120: // initializer
        value.move< std::unique_ptr<Initializer> > (YY_MOVE (that.value));
        break;

      case 123: // statement
        value.move< std::unique_ptr<Statement> > (YY_MOVE (that.value));
        break;

      case 86: // translation_unit
        value.move< std::unique_ptr<TranslationUnit> > (YY_MOVE (that.value));
        break;

      case 7: // TYPE_NAME
        value.move< std::unique_ptr<Type> > (YY_MOVE (that.value));
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        value.move< std::vector<std::unique_ptr<Declaration>> > (YY_MOVE (that.value));
        break;

      case 94: // argument_expression_list
        value.move< std::vector<std::unique_ptr<Expression>> > (YY_MOVE (that.value));
        break;

      case 87: // external_declaration_list
        value.move< std::vector<std::unique_ptr<External>> > (YY_MOVE (that.value));
        break;

      case 112: // init_declarator_list
        value.move< std::vector<std::unique_ptr<InitDeclarator>> > (YY_MOVE (that.value));
        break;

      case 126: // statement_list
        value.move< std::vector<std::unique_ptr<Statement>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 108: // assignment_operator
        value.move< AssignmentType > (that.value);
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        value.move< DeclarationSpecifiers > (that.value);
        break;

      case 109: // unary_operator
        value.move< UnaryOperatorType > (that.value);
        break;

      case 5: // FLOAT_CONSTANT
        value.move< double > (that.value);
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        value.move< int > (that.value);
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        value.move< std::string > (that.value);
        break;

      case 124: // compound_statement
        value.move< std::unique_ptr<Block> > (that.value);
        break;

      case 119: // parameter_declaration
        value.move< std::unique_ptr<Declaration> > (that.value);
        break;

      case 114: // declarator
      case 115: // direct_declarator
        value.move< std::unique_ptr<Declarator> > (that.value);
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
        value.move< std::unique_ptr<Expression> > (that.value);
        break;

      case 88: // function_definition
        value.move< std::unique_ptr<FunctionDefinition> > (that.value);
        break;

      case 113: // init_declarator
        value.move< std::unique_ptr<InitDeclarator> > (that.value);
        break;

      case 120: // initializer
        value.move< std::unique_ptr<Initializer> > (that.value);
        break;

      case 123: // statement
        value.move< std::unique_ptr<Statement> > (that.value);
        break;

      case 86: // translation_unit
        value.move< std::unique_ptr<TranslationUnit> > (that.value);
        break;

      case 7: // TYPE_NAME
        value.move< std::unique_ptr<Type> > (that.value);
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        value.move< std::vector<std::unique_ptr<Declaration>> > (that.value);
        break;

      case 94: // argument_expression_list
        value.move< std::vector<std::unique_ptr<Expression>> > (that.value);
        break;

      case 87: // external_declaration_list
        value.move< std::vector<std::unique_ptr<External>> > (that.value);
        break;

      case 112: // init_declarator_list
        value.move< std::vector<std::unique_ptr<InitDeclarator>> > (that.value);
        break;

      case 126: // statement_list
        value.move< std::vector<std::unique_ptr<Statement>> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 108: // assignment_operator
        yylhs.value.emplace< AssignmentType > ();
        break;

      case 111: // declaration_specifiers
      case 121: // storage_class_specifier
      case 122: // type_specifier
        yylhs.value.emplace< DeclarationSpecifiers > ();
        break;

      case 109: // unary_operator
        yylhs.value.emplace< UnaryOperatorType > ();
        break;

      case 5: // FLOAT_CONSTANT
        yylhs.value.emplace< double > ();
        break;

      case 4: // INT_CONSTANT
      case 116: // pointer
        yylhs.value.emplace< int > ();
        break;

      case 3: // IDENTIFIER
      case 6: // STRING_LITERAL
        yylhs.value.emplace< std::string > ();
        break;

      case 124: // compound_statement
        yylhs.value.emplace< std::unique_ptr<Block> > ();
        break;

      case 119: // parameter_declaration
        yylhs.value.emplace< std::unique_ptr<Declaration> > ();
        break;

      case 114: // declarator
      case 115: // direct_declarator
        yylhs.value.emplace< std::unique_ptr<Declarator> > ();
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
        yylhs.value.emplace< std::unique_ptr<Expression> > ();
        break;

      case 88: // function_definition
        yylhs.value.emplace< std::unique_ptr<FunctionDefinition> > ();
        break;

      case 113: // init_declarator
        yylhs.value.emplace< std::unique_ptr<InitDeclarator> > ();
        break;

      case 120: // initializer
        yylhs.value.emplace< std::unique_ptr<Initializer> > ();
        break;

      case 123: // statement
        yylhs.value.emplace< std::unique_ptr<Statement> > ();
        break;

      case 86: // translation_unit
        yylhs.value.emplace< std::unique_ptr<TranslationUnit> > ();
        break;

      case 7: // TYPE_NAME
        yylhs.value.emplace< std::unique_ptr<Type> > ();
        break;

      case 110: // declaration
      case 117: // parameter_type_list
      case 118: // parameter_list
      case 125: // declaration_list
        yylhs.value.emplace< std::vector<std::unique_ptr<Declaration>> > ();
        break;

      case 94: // argument_expression_list
        yylhs.value.emplace< std::vector<std::unique_ptr<Expression>> > ();
        break;

      case 87: // external_declaration_list
        yylhs.value.emplace< std::vector<std::unique_ptr<External>> > ();
        break;

      case 112: // init_declarator_list
        yylhs.value.emplace< std::vector<std::unique_ptr<InitDeclarator>> > ();
        break;

      case 126: // statement_list
        yylhs.value.emplace< std::vector<std::unique_ptr<Statement>> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 142 "src/parser.yy" // lalr1.cc:919
    { parse_result = make_unique<TranslationUnit>(move(yystack_[0].value.as < std::vector<std::unique_ptr<External>> > ())); }
#line 925 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 3:
#line 146 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<External>> > () = move(yystack_[1].value.as < std::vector<std::unique_ptr<External>> > ()); yylhs.value.as < std::vector<std::unique_ptr<External>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<FunctionDefinition> > ())); }
#line 931 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 4:
#line 148 "src/parser.yy" // lalr1.cc:919
    {
            yylhs.value.as < std::vector<std::unique_ptr<External>> > () = move(yystack_[1].value.as < std::vector<std::unique_ptr<External>> > ());
            auto declarations = move(yystack_[0].value.as < std::vector<std::unique_ptr<Declaration>> > ());
            for_each(make_move_iterator(declarations.begin()), make_move_iterator(declarations.end()), [&](auto decl) {
                yylhs.value.as < std::vector<std::unique_ptr<External>> > ().push_back(make_unique<ExternalDeclaration>(move(decl)));
            });
        }
#line 943 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 5:
#line 156 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<External>> > () = vector<unique_ptr<External>>(); }
#line 949 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 6:
#line 160 "src/parser.yy" // lalr1.cc:919
    {
        auto declaration = yystack_[1].value.as < std::unique_ptr<Declarator> > ()->to_declaration(type_from_declaration_specifier(move(yystack_[2].value.as < DeclarationSpecifiers > ())));
        auto& arguments = yystack_[1].value.as < std::unique_ptr<Declarator> > ()->get_arguments();
        vector<string> argument_names;

        for (auto it = arguments.begin(); it != arguments.end(); ++it) {
            argument_names.push_back((*it)->get_name());
        }

        yylhs.value.as < std::unique_ptr<FunctionDefinition> > () = make_unique<FunctionDefinition>(move(declaration), move(argument_names), move(yystack_[0].value.as < std::unique_ptr<Block> > ()));
    }
#line 965 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 7:
#line 175 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 971 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 8:
#line 179 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<Identifier>(move(yystack_[0].value.as < std::string > ())); }
#line 977 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 9:
#line 181 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<IntConstant>(move(yystack_[0].value.as < int > ())); }
#line 983 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 10:
#line 183 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<FloatConstant>(move(yystack_[0].value.as < double > ())); }
#line 989 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 11:
#line 185 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<StringConstant>(move(yystack_[0].value.as < std::string > ())); }
#line 995 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 12:
#line 187 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[1].value.as < std::unique_ptr<Expression> > ()); }
#line 1001 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 13:
#line 190 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1007 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 14:
#line 192 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<ArraySubscript>(move(yystack_[3].value.as < std::unique_ptr<Expression> > ()), move(yystack_[1].value.as < std::unique_ptr<Expression> > ())); }
#line 1013 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 15:
#line 194 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<FunctionCall>(move(yystack_[3].value.as < std::unique_ptr<Expression> > ()), move(yystack_[1].value.as < std::vector<std::unique_ptr<Expression>> > ())); }
#line 1019 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 16:
#line 196 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<FunctionCall>(move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), vector<unique_ptr<Expression>>()); }
#line 1025 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 17:
#line 198 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<DotOperator>(move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::string > ())); }
#line 1031 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 18:
#line 200 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<ArrowOperator>(move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::string > ())); }
#line 1037 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 19:
#line 202 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<UnaryOperator>(UnaryOperatorType::POST_INCREMENT, move(yystack_[1].value.as < std::unique_ptr<Expression> > ())); }
#line 1043 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 20:
#line 204 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<UnaryOperator>(UnaryOperatorType::POST_DECREMENT, move(yystack_[1].value.as < std::unique_ptr<Expression> > ())); }
#line 1049 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 21:
#line 207 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1055 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 22:
#line 209 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<UnaryOperator>(move(yystack_[1].value.as < UnaryOperatorType > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1061 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 23:
#line 211 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<UnaryOperator>(UnaryOperatorType::PRE_INCREMENT, move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1067 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 24:
#line 213 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<UnaryOperator>(UnaryOperatorType::PRE_DECREMENT, move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1073 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 25:
#line 215 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<UnaryOperator>(UnaryOperatorType::SIZEOF, move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1079 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 26:
#line 217 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<SizeOfType>(move(yystack_[1].value.as < std::unique_ptr<Type> > ())); }
#line 1085 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 27:
#line 220 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1091 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 28:
#line 222 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<Cast>(move(yystack_[2].value.as < std::unique_ptr<Type> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1097 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 29:
#line 226 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Expression>> > () = vector<unique_ptr<Expression>>(); yylhs.value.as < std::vector<std::unique_ptr<Expression>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1103 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 30:
#line 228 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Expression>> > () = move(yystack_[2].value.as < std::vector<std::unique_ptr<Expression>> > ()); yylhs.value.as < std::vector<std::unique_ptr<Expression>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1109 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 31:
#line 231 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1115 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 32:
#line 233 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::MUL, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1121 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 33:
#line 235 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::DIV, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1127 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 34:
#line 237 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::MOD, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1133 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 35:
#line 240 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1139 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 36:
#line 242 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::ADD, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1145 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 37:
#line 244 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::SUB, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1151 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 38:
#line 247 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1157 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 39:
#line 249 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::RSHIFT, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1163 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 40:
#line 251 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::LSHIFT, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1169 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 41:
#line 254 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1175 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 42:
#line 256 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::LT, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1181 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 43:
#line 258 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::GT, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1187 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 44:
#line 260 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::LTE, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1193 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 45:
#line 262 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::GTE, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1199 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 46:
#line 265 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1205 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 47:
#line 267 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::EQUALS, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1211 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 48:
#line 269 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::NOT_EQUALS, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1217 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 49:
#line 272 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1223 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 50:
#line 274 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::BITWISE_AND, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1229 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 51:
#line 277 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1235 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 52:
#line 279 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::BITWISE_XOR, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1241 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 53:
#line 282 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1247 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 54:
#line 284 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::BITWISE_OR, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1253 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 55:
#line 287 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1259 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 56:
#line 289 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::LOGICAL_AND, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1265 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 57:
#line 292 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1271 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 58:
#line 294 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<BinaryOperator>(BinaryOperatorType::LOGICAL_OR, move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1277 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 59:
#line 297 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1283 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 60:
#line 299 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<TernaryIf>(move(yystack_[4].value.as < std::unique_ptr<Expression> > ()), move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1289 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 61:
#line 302 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1295 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 62:
#line 304 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = make_unique<Assignment>(move(yystack_[1].value.as < AssignmentType > ()), move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1301 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 63:
#line 309 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1307 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 64:
#line 312 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::PLAIN; }
#line 1313 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 65:
#line 313 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::RSHIFT; }
#line 1319 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 66:
#line 314 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::LSHIFT; }
#line 1325 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 67:
#line 315 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::ADD; }
#line 1331 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 68:
#line 316 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::SUB; }
#line 1337 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 69:
#line 317 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::MUL; }
#line 1343 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 70:
#line 318 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::DIV; }
#line 1349 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 71:
#line 319 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::MOD; }
#line 1355 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 72:
#line 320 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::AND; }
#line 1361 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 73:
#line 321 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::XOR; }
#line 1367 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 74:
#line 322 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < AssignmentType > () = AssignmentType::OR; }
#line 1373 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 75:
#line 325 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < UnaryOperatorType > () = UnaryOperatorType::ADDRESS_OF; }
#line 1379 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 76:
#line 326 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < UnaryOperatorType > () = UnaryOperatorType::DEREFERENCE; }
#line 1385 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 77:
#line 327 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < UnaryOperatorType > () = UnaryOperatorType::PLUS; }
#line 1391 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 78:
#line 328 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < UnaryOperatorType > () = UnaryOperatorType::NEGATE; }
#line 1397 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 79:
#line 329 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < UnaryOperatorType > () = UnaryOperatorType::BITWISE_NOT; }
#line 1403 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 80:
#line 330 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < UnaryOperatorType > () = UnaryOperatorType::NOT; }
#line 1409 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 81:
#line 335 "src/parser.yy" // lalr1.cc:919
    {
        unique_ptr<Type> specified_type = type_from_declaration_specifier(move(yystack_[2].value.as < DeclarationSpecifiers > ()));
        auto declarators = move(yystack_[1].value.as < std::vector<std::unique_ptr<InitDeclarator>> > ());
        for (auto dec = declarators.begin(); dec != declarators.end(); ++dec) {
            yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > ().push_back((*dec)->to_declaration(specified_type->clone()));
        }
    }
#line 1421 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 82:
#line 343 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > () = vector<unique_ptr<Declaration>>(); }
#line 1427 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 83:
#line 348 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = yystack_[1].value.as < DeclarationSpecifiers > () | yystack_[0].value.as < DeclarationSpecifiers > (); }
#line 1433 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 84:
#line 350 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = yystack_[1].value.as < DeclarationSpecifiers > () | yystack_[0].value.as < DeclarationSpecifiers > (); }
#line 1439 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 85:
#line 351 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = yystack_[0].value.as < DeclarationSpecifiers > (); }
#line 1445 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 86:
#line 352 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = yystack_[0].value.as < DeclarationSpecifiers > (); }
#line 1451 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 87:
#line 356 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<InitDeclarator>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<InitDeclarator> > ())); }
#line 1457 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 88:
#line 358 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<InitDeclarator>> > () = move(yystack_[2].value.as < std::vector<std::unique_ptr<InitDeclarator>> > ()); yylhs.value.as < std::vector<std::unique_ptr<InitDeclarator>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<InitDeclarator> > ())); }
#line 1463 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 89:
#line 362 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<InitDeclarator> > () = make_unique<InitDeclarator>(move(yystack_[0].value.as < std::unique_ptr<Declarator> > ()), nullptr); }
#line 1469 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 90:
#line 364 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<InitDeclarator> > () = make_unique<InitDeclarator>(move(yystack_[2].value.as < std::unique_ptr<Declarator> > ()), move(yystack_[0].value.as < std::unique_ptr<Initializer> > ())); }
#line 1475 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 91:
#line 368 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = make_unique<PointerDeclarator>(move(yystack_[0].value.as < std::unique_ptr<Declarator> > ())); }
#line 1481 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 92:
#line 369 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = move(yystack_[0].value.as < std::unique_ptr<Declarator> > ()); }
#line 1487 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 93:
#line 373 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = make_unique<IdentifierDeclarator>(move(yystack_[0].value.as < std::string > ())); }
#line 1493 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 94:
#line 375 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = move(yystack_[1].value.as < std::unique_ptr<Declarator> > ()); }
#line 1499 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 95:
#line 377 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = make_unique<ArrayDeclarator>(move(yystack_[3].value.as < std::unique_ptr<Declarator> > ()), move(yystack_[1].value.as < std::unique_ptr<Expression> > ())); }
#line 1505 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 96:
#line 379 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = make_unique<ArrayDeclarator>(move(yystack_[2].value.as < std::unique_ptr<Declarator> > ()), nullptr); }
#line 1511 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 97:
#line 381 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = make_unique<FunctionDeclarator>(move(yystack_[3].value.as < std::unique_ptr<Declarator> > ()), move(yystack_[1].value.as < std::vector<std::unique_ptr<Declaration>> > ())); }
#line 1517 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 98:
#line 385 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declarator> > () = make_unique<FunctionDeclarator>(move(yystack_[2].value.as < std::unique_ptr<Declarator> > ()), vector<unique_ptr<Declaration>>()); }
#line 1523 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 99:
#line 392 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < int > () = 1; }
#line 1529 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 100:
#line 393 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < int > () = yystack_[0].value.as < int > () + 1; }
#line 1535 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 101:
#line 398 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > () = move(yystack_[0].value.as < std::vector<std::unique_ptr<Declaration>> > ()); }
#line 1541 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 102:
#line 403 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<Declaration> > ())); }
#line 1547 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 103:
#line 405 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > () = move(yystack_[2].value.as < std::vector<std::unique_ptr<Declaration>> > ()); yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<Declaration> > ())); }
#line 1553 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 104:
#line 409 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Declaration> > () = yystack_[0].value.as < std::unique_ptr<Declarator> > ()->to_declaration(type_from_declaration_specifier(move(yystack_[1].value.as < DeclarationSpecifiers > ()))); }
#line 1559 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 105:
#line 432 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Initializer> > () = make_unique<ExpressionInitializer>(move(yystack_[0].value.as < std::unique_ptr<Expression> > ())); }
#line 1565 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 106:
#line 441 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_TYPEDEF; }
#line 1571 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 107:
#line 442 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_EXTERN; }
#line 1577 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 108:
#line 443 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_STATIC; }
#line 1583 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 109:
#line 444 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_AUTO; }
#line 1589 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 110:
#line 445 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_REGISTER; }
#line 1595 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 111:
#line 456 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_VOID; }
#line 1601 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 112:
#line 457 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_CHAR; }
#line 1607 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 113:
#line 458 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_SHORT; }
#line 1613 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 114:
#line 459 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_INT; }
#line 1619 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 115:
#line 460 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_LONG; }
#line 1625 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 116:
#line 461 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_FLOAT ; }
#line 1631 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 117:
#line 462 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_DOUBLE; }
#line 1637 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 118:
#line 463 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_SIGNED; }
#line 1643 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 119:
#line 464 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < DeclarationSpecifiers > () = DECSPEC_UNSIGNED; }
#line 1649 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 120:
#line 520 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = move(yystack_[0].value.as < std::unique_ptr<Statement> > ()); }
#line 1655 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 121:
#line 522 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = move(yystack_[0].value.as < std::unique_ptr<Statement> > ()); }
#line 1661 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 122:
#line 524 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = move(yystack_[0].value.as < std::unique_ptr<Statement> > ()); }
#line 1667 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 123:
#line 527 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<ExpressionStmt>(move(yystack_[1].value.as < std::unique_ptr<Expression> > ())); }
#line 1673 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 124:
#line 529 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_noop(); }
#line 1679 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 125:
#line 531 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = move(yystack_[0].value.as < std::unique_ptr<Block> > ()); }
#line 1685 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 126:
#line 534 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<IfStmt>(move(yystack_[4].value.as < std::unique_ptr<Expression> > ()), move(yystack_[2].value.as < std::unique_ptr<Statement> > ()), move(yystack_[0].value.as < std::unique_ptr<Statement> > ())); }
#line 1691 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 127:
#line 536 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<IfStmt>(move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Statement> > ()), make_noop()); }
#line 1697 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 128:
#line 538 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<SwitchStmt>(move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Statement> > ())); }
#line 1703 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 129:
#line 541 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<WhileStmt>(move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Statement> > ())); }
#line 1709 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 130:
#line 543 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<DoStmt>(move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[5].value.as < std::unique_ptr<Statement> > ())); }
#line 1715 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 131:
#line 545 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<ForStmt>(move(yystack_[6].value.as < std::unique_ptr<Expression> > ()), move(yystack_[4].value.as < std::unique_ptr<Expression> > ()), move(yystack_[2].value.as < std::unique_ptr<Expression> > ()), move(yystack_[0].value.as < std::unique_ptr<Statement> > ())); }
#line 1721 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 132:
#line 549 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<Continue>(); }
#line 1727 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 133:
#line 551 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<Break>(); }
#line 1733 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 134:
#line 553 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<Return>(move(yystack_[1].value.as < std::unique_ptr<Expression> > ())); }
#line 1739 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 135:
#line 555 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Statement> > () = make_unique<Return>(); }
#line 1745 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 136:
#line 559 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Block> > () = make_unique<Block>(move(yystack_[2].value.as < std::vector<std::unique_ptr<Declaration>> > ()), move(yystack_[1].value.as < std::vector<std::unique_ptr<Statement>> > ())); }
#line 1751 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 137:
#line 561 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Block> > () = make_unique<Block>(move(yystack_[1].value.as < std::vector<std::unique_ptr<Declaration>> > ()), vector<unique_ptr<Statement>>()); }
#line 1757 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 138:
#line 563 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Block> > () = make_unique<Block>(vector<unique_ptr<Declaration>>(), move(yystack_[1].value.as < std::vector<std::unique_ptr<Statement>> > ())); }
#line 1763 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 139:
#line 565 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Block> > () = make_unique<Block>(
                vector<unique_ptr<Declaration>>(),
                vector<unique_ptr<Statement>>()); }
#line 1771 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 140:
#line 571 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > () = move(yystack_[0].value.as < std::vector<std::unique_ptr<Declaration>> > ()); }
#line 1777 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 141:
#line 573 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > () = move(yystack_[1].value.as < std::vector<std::unique_ptr<Declaration>> > ()); auto new_decls = move(yystack_[0].value.as < std::vector<std::unique_ptr<Declaration>> > ()); yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > ().insert(yylhs.value.as < std::vector<std::unique_ptr<Declaration>> > ().end(), make_move_iterator(new_decls.begin()), make_move_iterator(new_decls.end())); }
#line 1783 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 142:
#line 577 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Statement>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<Statement> > ())); }
#line 1789 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 143:
#line 579 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::vector<std::unique_ptr<Statement>> > () = move(yystack_[1].value.as < std::vector<std::unique_ptr<Statement>> > ()); yylhs.value.as < std::vector<std::unique_ptr<Statement>> > ().push_back(move(yystack_[0].value.as < std::unique_ptr<Statement> > ())); }
#line 1795 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 144:
#line 582 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = nullptr; }
#line 1801 "src/parser.tab.cpp" // lalr1.cc:919
    break;

  case 145:
#line 583 "src/parser.yy" // lalr1.cc:919
    { yylhs.value.as < std::unique_ptr<Expression> > () = move(yystack_[0].value.as < std::unique_ptr<Expression> > ()); }
#line 1807 "src/parser.tab.cpp" // lalr1.cc:919
    break;


#line 1811 "src/parser.tab.cpp" // lalr1.cc:919
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const short parser::yypact_ninf_ = -209;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -209,    16,   682,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
       2,   682,   682,  -209,     3,  -209,   -19,   -44,  -209,   -15,
      17,     4,  -209,  -209,    13,  -209,  -209,     3,   206,   569,
    -209,    22,   423,    17,  -209,  -209,    25,    18,  -209,  -209,
    -209,   601,   569,    23,    43,    74,   387,    77,    79,    67,
      72,   442,   475,  -209,  -209,  -209,   648,   648,  -209,  -209,
    -209,  -209,  -209,    80,  -209,    28,   618,  -209,    61,   -59,
     -14,    21,    15,    63,    60,    64,    83,    29,  -209,  -209,
     569,  -209,     2,  -209,  -209,   283,   127,  -209,  -209,  -209,
    -209,     3,    95,    84,  -209,  -209,  -209,  -209,    96,   387,
     522,  -209,    87,   387,   569,   569,   117,   569,   569,  -209,
    -209,  -209,    91,   104,   109,   569,  -209,  -209,  -209,   553,
     569,   163,   164,  -209,  -209,  -209,  -209,  -209,  -209,  -209,
    -209,  -209,  -209,  -209,  -209,  -209,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,  -209,  -209,  -209,   335,
    -209,  -209,  -209,  -209,   682,  -209,  -209,   118,   387,  -209,
     119,   120,   122,  -209,   110,   123,  -209,   569,  -209,  -209,
     -26,  -209,   121,  -209,  -209,  -209,  -209,  -209,  -209,    61,
      61,   -59,   -59,   -14,   -14,   -14,   -14,    21,    21,    15,
      63,    60,    64,   113,    83,  -209,  -209,  -209,  -209,   387,
     387,   569,   569,   387,  -209,  -209,   569,  -209,   569,   142,
    -209,   130,   124,  -209,  -209,  -209,   387,   133,   569,  -209,
    -209,   134,   387,  -209
  };

  const unsigned char
  parser::yydefact_[] =
  {
       5,     0,     2,     1,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,     3,     4,
       0,    86,    85,    93,     0,    82,    99,     0,    87,    89,
      92,     0,    83,    84,     0,   100,    81,     0,     0,     0,
       6,     0,     0,    91,    94,    88,    89,     8,     9,    10,
      11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   139,   124,    76,     0,     0,    77,    75,
      80,    79,    78,     0,    13,    21,    27,    31,    35,    38,
      41,    46,    49,    51,    53,    55,    57,    59,    61,     7,
       0,   140,     0,   142,   125,     0,     0,     8,   105,    90,
      98,     0,     0,   101,   102,    96,    27,    63,     0,     0,
       0,    25,     0,     0,     0,     0,     0,   144,     0,   132,
     133,   135,     0,     0,     0,     0,    23,    24,   123,     0,
       0,     0,     0,    19,    20,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,   137,   141,     0,
     138,   143,   104,    97,     0,    95,   120,     0,     0,   122,
       0,     0,     0,   145,     0,     0,   134,     0,    12,    16,
       0,    29,     0,    17,    18,    62,    32,    33,    34,    36,
      37,    39,    40,    45,    44,    42,    43,    47,    48,    50,
      52,    54,    56,     0,    58,   136,   103,    26,   121,     0,
       0,     0,   144,     0,    28,    15,     0,    14,     0,   127,
     128,     0,     0,   129,    30,    60,     0,     0,   144,   126,
     130,     0,     0,   131
  };

  const short
  parser::yypgoto_[] =
  {
    -209,  -209,  -209,  -209,   -39,  -209,  -209,   -41,   -87,  -209,
     -55,   -48,   -99,   -21,    32,    24,    34,    37,    55,  -209,
     -40,  -125,   150,  -209,  -209,   -30,     7,  -209,   171,    -7,
     190,   205,  -209,  -209,    58,  -209,  -209,  -209,   -29,   204,
    -209,   143,  -208
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     1,     2,    18,    73,    74,    75,    76,    77,   190,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,   108,   146,    90,    19,    92,    27,    28,    46,
      30,    31,   102,   103,   104,    99,    21,    22,    93,    94,
      95,    96,   184
  };

  const unsigned char
  parser::yytable_[] =
  {
      98,   106,   107,   166,   191,    23,    23,    23,    91,    20,
     111,   106,   107,    29,   232,   150,     3,    34,    36,    37,
     151,   195,   122,   124,   225,   126,   127,   116,    32,    33,
     241,     4,     5,     6,     7,     8,    38,   226,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    26,   101,   106,
      39,    24,    24,    24,   152,   203,   204,   205,   206,   153,
     196,   197,   198,    44,    25,   168,    41,   171,    26,    26,
      42,   124,   100,   158,   159,   180,   181,   129,   183,   185,
     176,   130,   109,   131,   179,   164,   124,   113,   154,   165,
      39,   192,   114,   155,   172,   199,   200,   132,   133,   134,
     224,   234,   156,   157,   201,   202,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   115,   106,   213,   117,   147,   118,   119,
      47,    48,    49,    50,   120,    51,   148,   207,   208,   160,
     171,   149,   128,   161,   163,   173,   106,   174,   162,   218,
     175,   178,   182,   186,   187,    52,    53,    54,    55,   188,
      56,    57,    58,    59,    60,    61,   193,   194,   217,   219,
     220,   221,   222,   223,   236,   227,    62,   228,    38,   170,
     237,   101,   231,   183,   242,   210,   238,   106,   235,    64,
     229,   230,   209,    65,   233,   240,   211,    66,    67,   183,
     212,    68,   112,    69,    70,    71,    72,   239,    45,    47,
      48,    49,    50,   243,    51,     4,     5,     6,     7,     8,
     214,    43,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    35,   216,    40,    52,    53,    54,    55,   169,    56,
      57,    58,    59,    60,    61,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,    38,    63,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,    65,     0,     0,     0,    66,    67,     0,     0,
      68,     0,    69,    70,    71,    72,    47,    48,    49,    50,
       0,    51,     4,     5,     6,     7,     8,     0,     0,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,    52,    53,    54,    55,     0,    56,    57,    58,    59,
      60,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    62,     0,    38,   167,     0,     0,    47,    48,
      49,    50,     0,    51,     0,    64,     0,     0,     0,    65,
       0,     0,     0,    66,    67,     0,     0,    68,     0,    69,
      70,    71,    72,    52,    53,    54,    55,     0,    56,    57,
      58,    59,    60,    61,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,    38,   215,     0,     0,
      47,    48,    49,    50,     0,    51,     0,    64,     0,     0,
       0,    65,     0,     0,     0,    66,    67,     0,     0,    68,
       0,    69,    70,    71,    72,    52,    53,    54,    55,     0,
      56,    57,    58,    59,    60,    61,    97,    48,    49,    50,
       0,    51,     0,     0,     0,     0,    62,     0,    38,     0,
       0,     0,     0,     0,     0,    97,    48,    49,    50,    64,
      51,     0,     0,    65,     0,     0,     0,    66,    67,     0,
       0,    68,     0,    69,    70,    71,    72,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,   105,    97,    48,
      49,    50,   123,    51,     0,     0,     0,     0,     0,    65,
       0,    62,     0,    66,    67,     0,     0,    68,     0,    69,
      70,    71,    72,     0,   121,     0,     0,     0,    65,     0,
       0,     0,    66,    67,     0,     0,    68,     0,    69,    70,
      71,    72,     0,     0,    62,    97,    48,    49,    50,   177,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,     0,     0,     0,    66,    67,     0,     0,    68,
       0,    69,    70,    71,    72,     0,    97,    48,    49,    50,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,    97,    48,    49,    50,     0,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,     0,
       0,     0,    66,    67,     0,     0,    68,     0,    69,    70,
      71,    72,    62,   189,    97,    48,    49,    50,     0,    51,
       0,     0,     0,     0,     0,     0,     0,     0,    62,    65,
       0,     0,     0,    66,    67,     0,     0,    68,     0,    69,
      70,    71,    72,     0,     0,    65,     0,     0,     0,    66,
      67,     0,     0,    68,     0,    69,    70,    71,    72,     0,
     110,    97,    48,    49,    50,     0,    51,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,    65,     0,     0,
       0,    66,    67,     0,     0,    68,     0,    69,    70,    71,
      72,     0,     0,   145,     0,     0,     0,     0,     0,     0,
       0,     4,     5,     6,     7,     8,     0,   125,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
       0,     0,     0,     0,    65,     0,     0,     0,    66,    67,
       0,     0,    68,     0,    69,    70,    71,    72
  };

  const short
  parser::yycheck_[] =
  {
      39,    42,    42,    90,   129,     3,     3,     3,    38,     2,
      51,    52,    52,    20,   222,    74,     0,    24,    62,    63,
      79,   146,    61,    62,    50,    66,    67,    56,    21,    22,
     238,     9,    10,    11,    12,    13,    51,    63,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    66,    41,    90,
      65,    49,    49,    49,    68,   154,   155,   156,   157,    73,
     147,   148,   149,    50,    62,    95,    49,    96,    66,    66,
      53,   110,    50,    58,    59,   114,   115,    49,   117,   118,
     109,    53,    64,    55,   113,    56,   125,    64,    67,    60,
      65,   130,    49,    72,   101,   150,   151,    69,    70,    71,
     187,   226,    81,    82,   152,   153,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,    49,   165,   164,    49,    66,    49,    62,
       3,     4,     5,     6,    62,     8,    75,   158,   159,    76,
     169,    80,    62,    83,    61,    50,   187,    63,    84,   178,
      54,    64,    35,    62,    50,    28,    29,    30,    31,    50,
      33,    34,    35,    36,    37,    38,     3,     3,    50,    50,
      50,    49,    62,    50,    32,    54,    49,    64,    51,    52,
      50,   174,   221,   222,    50,   161,    62,   228,   228,    62,
     219,   220,   160,    66,   223,    62,   162,    70,    71,   238,
     163,    74,    52,    76,    77,    78,    79,   236,    37,     3,
       4,     5,     6,   242,     8,     9,    10,    11,    12,    13,
     165,    31,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    26,   174,    29,    28,    29,    30,    31,    95,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    70,    71,    -1,    -1,
      74,    -1,    76,    77,    78,    79,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    29,    30,    31,    -1,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    51,    52,    -1,    -1,     3,     4,
       5,     6,    -1,     8,    -1,    62,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    70,    71,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    28,    29,    30,    31,    -1,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,
       3,     4,     5,     6,    -1,     8,    -1,    62,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    70,    71,    -1,    -1,    74,
      -1,    76,    77,    78,    79,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    37,    38,     3,     4,     5,     6,
      -1,     8,    -1,    -1,    -1,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    62,
       8,    -1,    -1,    66,    -1,    -1,    -1,    70,    71,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    54,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    49,    -1,    70,    71,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    -1,    62,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    70,    71,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    -1,    -1,    49,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    70,    71,    -1,    -1,    74,
      -1,    76,    77,    78,    79,    -1,     3,     4,     5,     6,
      -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,     3,     4,     5,     6,    -1,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    70,    71,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    49,    50,     3,     4,     5,     6,    -1,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    66,
      -1,    -1,    -1,    70,    71,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    -1,    -1,    66,    -1,    -1,    -1,    70,
      71,    -1,    -1,    74,    -1,    76,    77,    78,    79,    -1,
      49,     3,     4,     5,     6,    -1,     8,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    66,    -1,    -1,
      -1,    70,    71,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    -1,    49,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    70,    71,
      -1,    -1,    74,    -1,    76,    77,    78,    79
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    86,    87,     0,     9,    10,    11,    12,    13,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    88,   110,
     111,   121,   122,     3,    49,    62,    66,   112,   113,   114,
     115,   116,   111,   111,   114,   116,    62,    63,    51,    65,
     124,    49,    53,   115,    50,   113,   114,     3,     4,     5,
       6,     8,    28,    29,    30,    31,    33,    34,    35,    36,
      37,    38,    49,    52,    62,    66,    70,    71,    74,    76,
      77,    78,    79,    89,    90,    91,    92,    93,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     109,   110,   111,   123,   124,   125,   126,     3,    89,   120,
      50,   111,   117,   118,   119,    54,    92,   105,   107,    64,
      49,    92,   107,    64,    49,    49,   123,    49,    49,    62,
      62,    62,    89,     7,    89,    49,    92,    92,    62,    49,
      53,    55,    69,    70,    71,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    65,   108,    66,    75,    80,
      74,    79,    68,    73,    67,    72,    81,    82,    58,    59,
      76,    83,    84,    61,    56,    60,    93,    52,   110,   126,
      52,   123,   114,    50,    63,    54,   123,     7,    64,   123,
      89,    89,    35,    89,   127,    89,    62,    50,    50,    50,
      94,   106,    89,     3,     3,   106,    93,    93,    93,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    98,    99,
     100,   101,   102,    89,   103,    52,   119,    50,   123,    50,
      50,    49,    62,    50,    93,    50,    63,    54,    64,   123,
     123,    89,   127,   123,   106,   105,    32,    50,    62,   123,
      62,   127,    50,   123
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    85,    86,    87,    87,    87,    88,    89,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    92,    92,    92,    92,    92,    92,    93,    93,    94,
      94,    95,    95,    95,    95,    96,    96,    96,    97,    97,
      97,    98,    98,    98,    98,    98,    99,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   111,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   116,
     116,   117,   118,   118,   119,   120,   121,   121,   121,   121,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   124,
     125,   125,   126,   126,   127,   127
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     2,     0,     3,     1,     1,     1,
       1,     1,     3,     1,     4,     4,     3,     3,     3,     2,
       2,     1,     2,     2,     2,     2,     4,     1,     4,     1,
       3,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     2,     1,     1,     1,     3,     1,
       3,     2,     1,     1,     3,     4,     3,     4,     3,     1,
       2,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     1,     1,     7,     5,     5,     5,
       7,     9,     2,     2,     3,     2,     4,     3,     3,     2,
       1,     2,     1,     2,     0,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "END", "error", "$undefined", "IDENTIFIER", "INT_CONSTANT",
  "FLOAT_CONSTANT", "STRING_LITERAL", "TYPE_NAME", "SIZEOF", "TYPEDEF",
  "EXTERN", "STATIC", "AUTO", "REGISTER", "CONST", "VOLATILE", "VOID",
  "CHAR", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE", "SIGNED", "UNSIGNED",
  "STRUCT", "UNION", "ENUM", "CASE", "DEFAULT", "IF", "SWITCH", "ELSE",
  "DO", "FOR", "WHILE", "CONTINUE", "BREAK", "RETURN", "\">>=\"",
  "\"<<=\"", "\"+=\"", "\"-=\"", "\"*=\"", "\"/=\"", "\"%=\"", "\"&=\"",
  "\"^=\"", "\"|=\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"",
  "\".\"", "\"?\"", "\"...\"", "\"==\"", "\"!=\"", "\"||\"", "\"&&\"",
  "\";\"", "\",\"", "\":\"", "\"=\"", "\"*\"", "\">=\"", "\">>\"",
  "\"->\"", "\"++\"", "\"--\"", "\"<=\"", "\"<<\"", "\"+\"", "\"/\"",
  "\"&\"", "\"!\"", "\"~\"", "\"-\"", "\"%\"", "\"<\"", "\">\"", "\"^\"",
  "\"|\"", "$accept", "translation_unit", "external_declaration_list",
  "function_definition", "expression", "primary_expression",
  "postfix_expression", "unary_expression", "cast_expression",
  "argument_expression_list", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "constant_expression", "assignment_operator",
  "unary_operator", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "declarator",
  "direct_declarator", "pointer", "parameter_type_list", "parameter_list",
  "parameter_declaration", "initializer", "storage_class_specifier",
  "type_specifier", "statement", "compound_statement", "declaration_list",
  "statement_list", "for_expression", YY_NULLPTR
  };


  const unsigned short
  parser::yyrline_[] =
  {
       0,   141,   141,   145,   147,   155,   159,   175,   178,   180,
     182,   184,   186,   190,   191,   193,   195,   197,   199,   201,
     203,   207,   208,   210,   212,   214,   216,   220,   221,   225,
     227,   231,   232,   234,   236,   240,   241,   243,   247,   248,
     250,   254,   255,   257,   259,   261,   265,   266,   268,   272,
     273,   277,   278,   282,   283,   287,   288,   292,   293,   297,
     298,   302,   303,   309,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   325,   326,   327,   328,   329,
     330,   334,   342,   347,   349,   351,   352,   355,   357,   361,
     363,   367,   369,   372,   374,   376,   378,   380,   384,   392,
     393,   398,   402,   404,   408,   431,   441,   442,   443,   444,
     445,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     519,   521,   523,   526,   528,   531,   533,   535,   537,   540,
     542,   544,   548,   550,   552,   554,   558,   560,   562,   564,
     570,   572,   576,   578,   582,   583
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 2386 "src/parser.tab.cpp" // lalr1.cc:1242
#line 585 "src/parser.yy" // lalr1.cc:1243

