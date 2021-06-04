/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         S2ESTYPE
/* Substitute the variable and function names.  */
#define yyparse         s2eparse
#define yylex           s2elex
#define yyerror         s2eerror
#define yydebug         s2edebug
#define yynerrs         s2enerrs
#define yylval          s2elval
#define yychar          s2echar

/* First part of user prologue.  */
#line 1 "sysY.y"

#include "parser.hpp"

static s_basenode *root;
extern "C"{
    int yylex();
}
extern YYSTYPE s2elval;
extern FILE* s2ein;
extern FILE* s2eout;
extern void scantree(s_basenode*);

#line 91 "sysY.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_S2E_SYSY_TAB_HPP_INCLUDED
# define YY_S2E_SYSY_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef S2EDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define S2EDEBUG 1
#  else
#   define S2EDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define S2EDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined S2EDEBUG */
#if S2EDEBUG
extern int s2edebug;
#endif

/* Token type.  */
#ifndef S2ETOKENTYPE
# define S2ETOKENTYPE
  enum s2etokentype
  {
    TYPE_INT = 258,
    TYPE_VOID = 259,
    TYPE_CONST = 260,
    MAIN = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    BREAK = 265,
    CONTINUE = 266,
    RETURN = 267,
    LOWER_THAN_ELSE = 268,
    ASSIGN = 269,
    ADD = 270,
    MINUS = 271,
    MUL = 272,
    DIV = 273,
    MOD = 274,
    NOT = 275,
    LESS = 276,
    MORE = 277,
    LEQ = 278,
    GEQ = 279,
    EQUAL = 280,
    AND = 281,
    OR = 282,
    NEQ = 283,
    LPR = 284,
    RPR = 285,
    LBRK = 286,
    RBRK = 287,
    LBRAC = 288,
    RBRAC = 289,
    COMMA = 290,
    SEMCOL = 291,
    INT_CONST = 292,
    ID = 293,
    ERROR = 294
  };
#endif

/* Value type.  */
#if ! defined S2ESTYPE && ! defined S2ESTYPE_IS_DECLARED
typedef int S2ESTYPE;
# define S2ESTYPE_IS_TRIVIAL 1
# define S2ESTYPE_IS_DECLARED 1
#endif


extern S2ESTYPE s2elval;

int s2eparse (void);

#endif /* !YY_S2E_SYSY_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined S2ESTYPE_IS_TRIVIAL && S2ESTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

#define YYUNDEFTOK  2
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39
};

#if S2EDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    21,    21,    22,    27,    32,    37,    44,    49,    56,
      61,    68,    76,    81,    89,    99,   103,   111,   116,   123,
     131,   136,   144,   152,   157,   165,   171,   181,   186,   192,
     201,   206,   215,   224,   236,   241,   249,   255,   266,   272,
     281,   286,   294,   299,   308,   315,   320,   324,   329,   340,
     349,   358,   363,   368,   373,   381,   388,   395,   402,   406,
     413,   420,   425,   432,   441,   446,   453,   461,   469,   474,
     479,   486,   491,   500,   505,   514,   519,   524,   531,   536,
     545,   550,   557,   562,   571,   576,   581,   586,   593,   598,
     607,   612,   619,   624,   633,   640,   645,   654,   661
};
#endif

#if S2EDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE_INT", "TYPE_VOID", "TYPE_CONST",
  "MAIN", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN",
  "LOWER_THAN_ELSE", "ASSIGN", "ADD", "MINUS", "MUL", "DIV", "MOD", "NOT",
  "LESS", "MORE", "LEQ", "GEQ", "EQUAL", "AND", "OR", "NEQ", "LPR", "RPR",
  "LBRK", "RBRK", "LBRAC", "RBRAC", "COMMA", "SEMCOL", "INT_CONST", "ID",
  "ERROR", "$accept", "Program", "CompUnit", "Decl", "BType", "ConstDecl",
  "ConstSeqDecl", "ConstDef", "MD_Array", "ConstInitVal",
  "ConstSeqInitVal", "VarDecl", "VarSeqDef", "VarDef", "InitVal",
  "InitSeqVal", "FuncDef", "FuncFParams", "FuncFParam", "Block",
  "BlockSeqItem", "BlockItem", "Stmt", "Exp", "Cond", "LVal", "LVal_Array",
  "PrimaryExp", "Number", "UnaryExp", "UnaryOp", "FuncRParams", "MulExp",
  "MulOp", "AddExp", "AddOp", "RelExp", "RelOp", "EqExp", "EqOp",
  "LAndExp", "LAndOp", "LOrExp", "LOrOp", "ConstExp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF (-129)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      96,  -129,  -129,    62,    15,    96,  -129,    -5,  -129,  -129,
    -129,     8,  -129,  -129,  -129,     6,    27,  -129,  -129,    55,
    -129,     7,    -3,    17,  -129,    -1,     8,  -129,    19,    35,
     -16,  -129,     5,    44,  -129,  -129,   178,  -129,    40,   115,
    -129,    35,    73,  -129,  -129,  -129,    44,    59,  -129,    49,
    -129,  -129,  -129,  -129,  -129,  -129,    44,    88,    79,    79,
      52,   175,  -129,  -129,    54,    83,    85,    80,    87,    11,
    -129,  -129,  -129,    17,  -129,   151,  -129,  -129,    92,   118,
    -129,  -129,    99,  -129,  -129,    68,   190,   102,  -129,  -129,
    -129,  -129,    44,  -129,  -129,    44,  -129,  -129,  -129,    74,
    -129,    44,    44,  -129,  -129,  -129,    98,  -129,  -129,  -129,
      44,  -129,  -129,     5,  -129,  -129,   -12,    44,  -129,    88,
    -129,   178,   105,   107,    79,    30,    33,   112,   113,   109,
    -129,   106,  -129,  -129,    44,   111,  -129,   163,  -129,  -129,
    -129,  -129,    44,  -129,  -129,    44,  -129,    44,  -129,    44,
     163,  -129,  -129,  -129,   133,    79,    30,    33,   112,  -129,
     163,  -129
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,     0,     0,     2,     3,     0,     7,     8,
       4,     0,     1,     5,     6,    15,     0,    23,    15,     0,
      12,     0,    25,     0,    22,     0,     0,    11,     0,     0,
       0,    34,     0,     0,    15,    24,     0,    13,    36,     0,
      32,     0,     0,    68,    69,    70,     0,     0,    63,    58,
      26,    27,    61,    64,    62,    73,     0,    78,    55,    98,
       0,     0,    14,    17,     0,     0,     0,     0,     0,     0,
      38,    46,    42,     0,    47,     0,    40,    43,     0,    61,
      33,    35,     0,    28,    30,     0,     0,    57,    67,    75,
      76,    77,     0,    80,    81,     0,    16,    19,    20,     0,
      15,     0,     0,    51,    52,    53,     0,    39,    41,    45,
       0,    60,    29,     0,    65,    71,     0,     0,    74,    79,
      18,     0,    37,     0,    82,    88,    92,    95,    56,     0,
      54,     0,    31,    66,     0,     0,    21,     0,    84,    86,
      85,    87,     0,    90,    91,     0,    94,     0,    97,     0,
       0,    44,    72,    59,    49,    83,    89,    93,    96,    50,
       0,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -129,  -129,  -129,    45,     2,  -129,  -129,   119,   -15,   -54,
    -129,  -129,  -129,   123,   -41,  -129,   142,  -129,   108,   -17,
    -129,    82,  -128,   -30,    57,   -39,  -129,  -129,  -129,   -48,
    -129,  -129,    69,  -129,   -32,  -129,    20,  -129,    21,  -129,
      28,  -129,  -129,  -129,   136
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    72,     7,     8,    19,    20,    22,    62,
      99,     9,    16,    17,    50,    85,    10,    30,    31,    74,
      75,    76,    77,    78,   123,    52,    87,    53,    54,    55,
      56,   116,    57,    92,    58,    95,   125,   142,   126,   145,
     127,   147,   128,   149,    63
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      79,    59,    51,    25,    59,    11,    84,    98,    88,   154,
      28,    32,    40,    36,    41,    12,    82,    51,   133,    42,
      43,    44,   159,   134,    80,    45,    43,    44,    33,    59,
      33,    45,   161,    15,    46,    21,    79,    29,    47,   106,
      46,    73,    48,    49,   118,     6,    18,   105,    48,    49,
      13,   138,   139,   140,   141,    34,   115,    38,   143,    43,
      44,   144,    23,    24,    45,     1,     2,   136,    39,   124,
     124,    64,   132,    46,    43,    44,    28,    73,    86,    45,
     131,    48,    49,    51,    96,   122,   100,   135,    46,    59,
      26,    27,    47,    83,    93,    94,    48,    49,    79,     1,
       2,     3,   112,   113,   152,    89,    90,    91,   120,   121,
     155,    79,   101,   124,   102,   124,   103,   124,     1,     2,
       3,    79,    65,   104,    66,    67,    68,    69,   109,   111,
      43,    44,   110,   117,   130,    45,    33,   137,   146,   150,
     148,   160,   151,   153,    46,    37,    35,    14,    39,    70,
      81,    71,    48,    49,     1,     2,     3,   108,    65,   129,
      66,    67,    68,    69,   119,   156,    43,    44,   157,    60,
      65,    45,    66,    67,    68,    69,     0,   158,    43,    44,
      46,     0,     0,    45,    39,   107,     0,    71,    48,    49,
      43,    44,    46,    43,    44,    45,    39,     0,    45,    71,
      48,    49,     0,     0,    46,    43,    44,    46,    61,    97,
      45,    61,    48,    49,     0,    48,    49,     0,     0,    46,
     114,     0,     0,     0,     0,     0,     0,    48,    49
};

static const yytype_int16 yycheck[] =
{
      39,    33,    32,    18,    36,     3,    47,    61,    56,   137,
       3,    14,    29,    14,    30,     0,    46,    47,    30,    35,
      15,    16,   150,    35,    41,    20,    15,    16,    31,    61,
      31,    20,   160,    38,    29,    29,    75,    30,    33,    69,
      29,    39,    37,    38,    92,     0,    38,    36,    37,    38,
       5,    21,    22,    23,    24,    38,    86,    38,    25,    15,
      16,    28,    35,    36,    20,     3,     4,   121,    33,   101,
     102,    31,   113,    29,    15,    16,     3,    75,    29,    20,
     110,    37,    38,   113,    32,   100,    32,   117,    29,   121,
      35,    36,    33,    34,    15,    16,    37,    38,   137,     3,
       4,     5,    34,    35,   134,    17,    18,    19,    34,    35,
     142,   150,    29,   145,    29,   147,    36,   149,     3,     4,
       5,   160,     7,    36,     9,    10,    11,    12,    36,    30,
      15,    16,    14,    31,    36,    20,    31,    30,    26,    30,
      27,     8,    36,    32,    29,    26,    23,     5,    33,    34,
      42,    36,    37,    38,     3,     4,     5,    75,     7,   102,
       9,    10,    11,    12,    95,   145,    15,    16,   147,    33,
       7,    20,     9,    10,    11,    12,    -1,   149,    15,    16,
      29,    -1,    -1,    20,    33,    34,    -1,    36,    37,    38,
      15,    16,    29,    15,    16,    20,    33,    -1,    20,    36,
      37,    38,    -1,    -1,    29,    15,    16,    29,    33,    34,
      20,    33,    37,    38,    -1,    37,    38,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    41,    42,    43,    44,    45,    51,
      56,    44,     0,    43,    56,    38,    52,    53,    38,    46,
      47,    29,    48,    35,    36,    48,    35,    36,     3,    30,
      57,    58,    14,    31,    38,    53,    14,    47,    38,    33,
      59,    30,    35,    15,    16,    20,    29,    33,    37,    38,
      54,    63,    65,    67,    68,    69,    70,    72,    74,    74,
      84,    33,    49,    84,    31,     7,     9,    10,    11,    12,
      34,    36,    43,    44,    59,    60,    61,    62,    63,    65,
      59,    58,    63,    34,    54,    55,    29,    66,    69,    17,
      18,    19,    73,    15,    16,    75,    32,    34,    49,    50,
      32,    29,    29,    36,    36,    36,    63,    34,    61,    36,
      14,    30,    34,    35,    30,    63,    71,    31,    69,    72,
      34,    35,    48,    64,    74,    76,    78,    80,    82,    64,
      36,    63,    54,    30,    35,    63,    49,    30,    21,    22,
      23,    24,    77,    25,    28,    79,    26,    81,    27,    83,
      30,    36,    63,    32,    62,    74,    76,    78,    80,    62,
       8,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    43,    43,    44,
      44,    45,    46,    46,    47,    48,    48,    49,    49,    49,
      50,    50,    51,    52,    52,    53,    53,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    63,    64,    65,    66,    66,
      67,    67,    67,    68,    69,    69,    69,    69,    70,    70,
      70,    71,    71,    72,    72,    73,    73,    73,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    77,    78,    78,
      79,    79,    80,    80,    81,    82,    82,    83,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     4,     1,     3,     4,     0,     4,     1,     3,     2,
       1,     3,     3,     1,     3,     2,     4,     1,     2,     3,
       1,     3,     5,     6,     1,     3,     2,     5,     2,     3,
       1,     2,     1,     1,     4,     2,     1,     1,     7,     5,
       5,     2,     2,     2,     3,     1,     1,     2,     0,     4,
       3,     1,     1,     1,     1,     3,     4,     2,     1,     1,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if S2EDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !S2EDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !S2EDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 21 "sysY.y"
                   {yyval=yyvsp[0]; root = yyvsp[0];}
#line 1493 "sysY.tab.cpp"
    break;

  case 3:
#line 22 "sysY.y"
              { 
                s_basenode* tmp = new s_basenode(_compunit);
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
            }
#line 1503 "sysY.tab.cpp"
    break;

  case 4:
#line 27 "sysY.y"
                 {
                s_basenode* tmp = new s_basenode(_compunit);
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
            }
#line 1513 "sysY.tab.cpp"
    break;

  case 5:
#line 32 "sysY.y"
                       {
                auto tmp = yyvsp[-1];
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
        }
#line 1523 "sysY.tab.cpp"
    break;

  case 6:
#line 37 "sysY.y"
                          {
                auto tmp = yyvsp[-1];
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
        }
#line 1533 "sysY.tab.cpp"
    break;

  case 7:
#line 44 "sysY.y"
               {
                s_basenode* tmp = new s_basenode(_decl);
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
        }
#line 1543 "sysY.tab.cpp"
    break;

  case 8:
#line 49 "sysY.y"
                 {
                s_basenode* tmp = new s_basenode(_decl);
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
        }
#line 1553 "sysY.tab.cpp"
    break;

  case 9:
#line 56 "sysY.y"
              {
            s_basenode* tmp = new s_basenode(_btype);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
      }
#line 1563 "sysY.tab.cpp"
    break;

  case 10:
#line 61 "sysY.y"
                 {
            s_basenode* tmp = new s_basenode(_btype);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
      }
#line 1573 "sysY.tab.cpp"
    break;

  case 11:
#line 68 "sysY.y"
                                               {
                s_basenode* tmp = new s_basenode(_constdecl);
                tmp->Son.push_back(yyvsp[-2]);
                tmp->Son.push_back(yyvsp[-1]);
                yyval=tmp;
        }
#line 1584 "sysY.tab.cpp"
    break;

  case 12:
#line 76 "sysY.y"
                      {
                s_basenode* tmp = new s_basenode(_defconstlist);
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
        }
#line 1594 "sysY.tab.cpp"
    break;

  case 13:
#line 81 "sysY.y"
                                     {
                s_basenode* tmp = new s_basenode(_defconstlist);
                tmp->Son.push_back(yyvsp[-2]);
                tmp->Son.push_back(yyvsp[0]);
                yyval = tmp;
        }
#line 1605 "sysY.tab.cpp"
    break;

  case 14:
#line 89 "sysY.y"
                                         {
              s_basenode* tmp = new s_basenode(_constdef);
              tmp->Son.push_back(yyvsp[-3]);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1618 "sysY.tab.cpp"
    break;

  case 15:
#line 99 "sysY.y"
          {
              s_basenode *tmp = new s_basenode(_mddim);
              yyval = tmp;
        }
#line 1627 "sysY.tab.cpp"
    break;

  case 16:
#line 103 "sysY.y"
                                     {
              s_basenode* tmp = new s_basenode(_mddim);
              tmp->Son.push_back(yyvsp[-3]);
              tmp->Son.push_back(yyvsp[-1]);
              yyval = tmp;
        }
#line 1638 "sysY.tab.cpp"
    break;

  case 17:
#line 111 "sysY.y"
                      {
              s_basenode* tmp = new s_basenode(_constinitval);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1648 "sysY.tab.cpp"
    break;

  case 18:
#line 116 "sysY.y"
                                     {
              s_basenode* tmp = new s_basenode(_constinitval);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1660 "sysY.tab.cpp"
    break;

  case 19:
#line 123 "sysY.y"
                     {
              s_basenode* tmp = new s_basenode(_constinitval);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1671 "sysY.tab.cpp"
    break;

  case 20:
#line 131 "sysY.y"
                             {
              s_basenode* tmp = new s_basenode(_constseqinitval);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1681 "sysY.tab.cpp"
    break;

  case 21:
#line 136 "sysY.y"
                                            {
              s_basenode* tmp = new s_basenode(_constseqinitval);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1692 "sysY.tab.cpp"
    break;

  case 22:
#line 144 "sysY.y"
                               {
              s_basenode* tmp = new s_basenode(_vardecl);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              yyval = tmp;
        }
#line 1703 "sysY.tab.cpp"
    break;

  case 23:
#line 152 "sysY.y"
                 {
              s_basenode*tmp = new s_basenode(_varseqdef);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1713 "sysY.tab.cpp"
    break;

  case 24:
#line 157 "sysY.y"
                                {
              s_basenode* tmp = new s_basenode(_varseqdef);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1724 "sysY.tab.cpp"
    break;

  case 25:
#line 165 "sysY.y"
                   {
              s_basenode* tmp = new s_basenode(_vardef);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1735 "sysY.tab.cpp"
    break;

  case 26:
#line 171 "sysY.y"
                                    {
              s_basenode* tmp = new s_basenode(_vardef);
              tmp->Son.push_back(yyvsp[-3]);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1748 "sysY.tab.cpp"
    break;

  case 27:
#line 181 "sysY.y"
            {
              s_basenode* tmp = new s_basenode(_initval);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1758 "sysY.tab.cpp"
    break;

  case 28:
#line 186 "sysY.y"
                     {
              s_basenode* tmp = new s_basenode(_initval);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1769 "sysY.tab.cpp"
    break;

  case 29:
#line 192 "sysY.y"
                                {
              s_basenode* tmp = new s_basenode(_initval);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1781 "sysY.tab.cpp"
    break;

  case 30:
#line 201 "sysY.y"
                   {
              s_basenode* tmp = new s_basenode(_initseqval);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1791 "sysY.tab.cpp"
    break;

  case 31:
#line 206 "sysY.y"
                                  {
              s_basenode* tmp = new s_basenode(_initseqval);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1803 "sysY.tab.cpp"
    break;

  case 32:
#line 215 "sysY.y"
                                {
              s_basenode* tmp = new s_basenode(_funcdef);
              tmp->Son.push_back(yyvsp[-4]);
              tmp->Son.push_back(yyvsp[-3]);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1817 "sysY.tab.cpp"
    break;

  case 33:
#line 224 "sysY.y"
                                            {
              s_basenode* tmp = new s_basenode(_funcdef);
              tmp->Son.push_back(yyvsp[-5]);
              tmp->Son.push_back(yyvsp[-4]);
              tmp->Son.push_back(yyvsp[-3]);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1832 "sysY.tab.cpp"
    break;

  case 34:
#line 236 "sysY.y"
                       {
              s_basenode* tmp = new s_basenode(_funcfparams);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1842 "sysY.tab.cpp"
    break;

  case 35:
#line 241 "sysY.y"
                                      {
              s_basenode* tmp = new s_basenode(_funcfparams);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1853 "sysY.tab.cpp"
    break;

  case 36:
#line 249 "sysY.y"
                       {
              s_basenode* tmp = new s_basenode(_funcfparam);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1864 "sysY.tab.cpp"
    break;

  case 37:
#line 255 "sysY.y"
                                        {
              s_basenode* tmp = new s_basenode(_funcfparam);
              tmp->Son.push_back(yyvsp[-4]);
              tmp->Son.push_back(yyvsp[-3]);
              tmp->Son.push_back(yyvsp[-2]);
              tmp->Son.push_back(yyvsp[-1]);
              tmp->Son.push_back(yyvsp[0]);
              yyval = tmp;
        }
#line 1878 "sysY.tab.cpp"
    break;

  case 38:
#line 266 "sysY.y"
                  {
            s_basenode* tmp = new s_basenode(_block);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1889 "sysY.tab.cpp"
    break;

  case 39:
#line 272 "sysY.y"
                                  {
            s_basenode* tmp = new s_basenode(_block);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1901 "sysY.tab.cpp"
    break;

  case 40:
#line 281 "sysY.y"
                       {
            s_basenode* tmp = new s_basenode(_blockseqitem);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1911 "sysY.tab.cpp"
    break;

  case 41:
#line 286 "sysY.y"
                                {
            s_basenode* tmp = new s_basenode(_blockseqitem);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1922 "sysY.tab.cpp"
    break;

  case 42:
#line 294 "sysY.y"
               {
            s_basenode* tmp = new s_basenode(_blockitem);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1932 "sysY.tab.cpp"
    break;

  case 43:
#line 299 "sysY.y"
              {
            s_basenode* tmp = new s_basenode(_blockitem);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1942 "sysY.tab.cpp"
    break;

  case 44:
#line 308 "sysY.y"
                            {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-3]);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            yyval = tmp;
        }
#line 1954 "sysY.tab.cpp"
    break;

  case 45:
#line 315 "sysY.y"
                    {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-1]);
            yyval = tmp; 
        }
#line 1964 "sysY.tab.cpp"
    break;

  case 46:
#line 320 "sysY.y"
                {
            s_basenode* tmp = new s_basenode(_stmt);
            yyval = tmp;
        }
#line 1973 "sysY.tab.cpp"
    break;

  case 47:
#line 324 "sysY.y"
               {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1983 "sysY.tab.cpp"
    break;

  case 48:
#line 329 "sysY.y"
                                        {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-6]);
            tmp->Son.push_back(yyvsp[-5]);
            tmp->Son.push_back(yyvsp[-4]);
            tmp->Son.push_back(yyvsp[-3]);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 1999 "sysY.tab.cpp"
    break;

  case 49:
#line 340 "sysY.y"
                                                    {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-4]);
            tmp->Son.push_back(yyvsp[-3]);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2013 "sysY.tab.cpp"
    break;

  case 50:
#line 349 "sysY.y"
                                 {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-4]);
            tmp->Son.push_back(yyvsp[-3]);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp; 
        }
#line 2027 "sysY.tab.cpp"
    break;

  case 51:
#line 358 "sysY.y"
                      {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-1]);
            yyval = tmp;
        }
#line 2037 "sysY.tab.cpp"
    break;

  case 52:
#line 363 "sysY.y"
                         {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-1]);
            yyval = tmp;
        }
#line 2047 "sysY.tab.cpp"
    break;

  case 53:
#line 368 "sysY.y"
                       {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-1]);
            yyval = tmp;
        }
#line 2057 "sysY.tab.cpp"
    break;

  case 54:
#line 373 "sysY.y"
                           {
            s_basenode* tmp = new s_basenode(_stmt);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            yyval = tmp;
        }
#line 2068 "sysY.tab.cpp"
    break;

  case 55:
#line 381 "sysY.y"
           {
            s_basenode* tmp = new s_basenode(_exp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2078 "sysY.tab.cpp"
    break;

  case 56:
#line 388 "sysY.y"
            {
            s_basenode* tmp = new s_basenode(_cond);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2088 "sysY.tab.cpp"
    break;

  case 57:
#line 395 "sysY.y"
                   {
            s_basenode* tmp = new s_basenode(_lval);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2099 "sysY.tab.cpp"
    break;

  case 58:
#line 402 "sysY.y"
            {
              s_basenode *tmp = new s_basenode(_lvaldim);
              yyval = tmp;
        }
#line 2108 "sysY.tab.cpp"
    break;

  case 59:
#line 406 "sysY.y"
                                  {
              s_basenode* tmp = new s_basenode(_lvaldim);
              tmp->Son.push_back(yyvsp[-3]);
              tmp->Son.push_back(yyvsp[-1]);
              yyval = tmp;
        }
#line 2119 "sysY.tab.cpp"
    break;

  case 60:
#line 413 "sysY.y"
                       {
            s_basenode* tmp = new s_basenode(_primaryexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2131 "sysY.tab.cpp"
    break;

  case 61:
#line 420 "sysY.y"
              {
            s_basenode* tmp = new s_basenode(_primaryexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2141 "sysY.tab.cpp"
    break;

  case 62:
#line 425 "sysY.y"
                {
            s_basenode* tmp = new s_basenode(_primaryexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2151 "sysY.tab.cpp"
    break;

  case 63:
#line 432 "sysY.y"
                 {
            s_basenode* tmp = new s_basenode(_number);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2161 "sysY.tab.cpp"
    break;

  case 64:
#line 441 "sysY.y"
                    {
            s_basenode* tmp = new s_basenode(_unaryexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2171 "sysY.tab.cpp"
    break;

  case 65:
#line 446 "sysY.y"
                    {
            s_basenode* tmp = new s_basenode(_unaryexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2183 "sysY.tab.cpp"
    break;

  case 66:
#line 453 "sysY.y"
                                {
            s_basenode* tmp = new s_basenode(_unaryexp);
            tmp->Son.push_back(yyvsp[-3]);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2196 "sysY.tab.cpp"
    break;

  case 67:
#line 461 "sysY.y"
                          {
            s_basenode* tmp = new s_basenode(_unaryexp);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2207 "sysY.tab.cpp"
    break;

  case 68:
#line 469 "sysY.y"
            {
            s_basenode* tmp = new s_basenode(_unaryop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2217 "sysY.tab.cpp"
    break;

  case 69:
#line 474 "sysY.y"
               {
            s_basenode* tmp = new s_basenode(_unaryop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2227 "sysY.tab.cpp"
    break;

  case 70:
#line 479 "sysY.y"
             {
            s_basenode* tmp = new s_basenode(_unaryop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2237 "sysY.tab.cpp"
    break;

  case 71:
#line 486 "sysY.y"
                {
            s_basenode* tmp = new s_basenode(_funcrparams);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2247 "sysY.tab.cpp"
    break;

  case 72:
#line 491 "sysY.y"
                               {
            s_basenode* tmp = new s_basenode(_funcrparams);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2259 "sysY.tab.cpp"
    break;

  case 73:
#line 500 "sysY.y"
                {
            s_basenode* tmp = new s_basenode(_mulexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2269 "sysY.tab.cpp"
    break;

  case 74:
#line 505 "sysY.y"
                               {
            s_basenode* tmp = new s_basenode(_mulexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2281 "sysY.tab.cpp"
    break;

  case 75:
#line 514 "sysY.y"
          {
            s_basenode* tmp = new s_basenode(_mulop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2291 "sysY.tab.cpp"
    break;

  case 76:
#line 519 "sysY.y"
             {
            s_basenode* tmp = new s_basenode(_mulop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp; 
        }
#line 2301 "sysY.tab.cpp"
    break;

  case 77:
#line 524 "sysY.y"
             {
            s_basenode* tmp = new s_basenode(_mulop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2311 "sysY.tab.cpp"
    break;

  case 78:
#line 531 "sysY.y"
              {
            s_basenode* tmp = new s_basenode(_addexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2321 "sysY.tab.cpp"
    break;

  case 79:
#line 536 "sysY.y"
                             {
            s_basenode* tmp = new s_basenode(_addexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2333 "sysY.tab.cpp"
    break;

  case 80:
#line 545 "sysY.y"
          {
            s_basenode* tmp = new s_basenode(_addop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2343 "sysY.tab.cpp"
    break;

  case 81:
#line 550 "sysY.y"
               {
            s_basenode* tmp = new s_basenode(_addop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2353 "sysY.tab.cpp"
    break;

  case 82:
#line 557 "sysY.y"
              {
            s_basenode* tmp = new s_basenode(_relexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2363 "sysY.tab.cpp"
    break;

  case 83:
#line 562 "sysY.y"
                             {
            s_basenode* tmp = new s_basenode(_relexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2375 "sysY.tab.cpp"
    break;

  case 84:
#line 571 "sysY.y"
           {
            s_basenode* tmp = new s_basenode(_relop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2385 "sysY.tab.cpp"
    break;

  case 85:
#line 576 "sysY.y"
             {
            s_basenode* tmp = new s_basenode(_relop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2395 "sysY.tab.cpp"
    break;

  case 86:
#line 581 "sysY.y"
              {
            s_basenode* tmp = new s_basenode(_relop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2405 "sysY.tab.cpp"
    break;

  case 87:
#line 586 "sysY.y"
             {
            s_basenode* tmp = new s_basenode(_relop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2415 "sysY.tab.cpp"
    break;

  case 88:
#line 593 "sysY.y"
             {
            s_basenode* tmp = new s_basenode(_eqexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2425 "sysY.tab.cpp"
    break;

  case 89:
#line 598 "sysY.y"
                           {
            s_basenode* tmp = new s_basenode(_eqexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2437 "sysY.tab.cpp"
    break;

  case 90:
#line 607 "sysY.y"
           {
            s_basenode* tmp = new s_basenode(_eqop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2447 "sysY.tab.cpp"
    break;

  case 91:
#line 612 "sysY.y"
             {
            s_basenode* tmp = new s_basenode(_eqop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2457 "sysY.tab.cpp"
    break;

  case 92:
#line 619 "sysY.y"
              {
            s_basenode* tmp = new s_basenode(_landexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2467 "sysY.tab.cpp"
    break;

  case 93:
#line 624 "sysY.y"
                              {
            s_basenode* tmp = new s_basenode(_landexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2479 "sysY.tab.cpp"
    break;

  case 94:
#line 633 "sysY.y"
           {
            s_basenode* tmp = new s_basenode(_landop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2489 "sysY.tab.cpp"
    break;

  case 95:
#line 640 "sysY.y"
               {
            s_basenode* tmp = new s_basenode(_lorexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2499 "sysY.tab.cpp"
    break;

  case 96:
#line 645 "sysY.y"
                              {
            s_basenode* tmp = new s_basenode(_lorexp);
            tmp->Son.push_back(yyvsp[-2]);
            tmp->Son.push_back(yyvsp[-1]);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2511 "sysY.tab.cpp"
    break;

  case 97:
#line 654 "sysY.y"
         {
            s_basenode* tmp = new s_basenode(_lorop);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2521 "sysY.tab.cpp"
    break;

  case 98:
#line 661 "sysY.y"
                {
            s_basenode* tmp = new s_basenode(_constexp);
            tmp->Son.push_back(yyvsp[0]);
            yyval = tmp;
        }
#line 2531 "sysY.tab.cpp"
    break;


#line 2535 "sysY.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 667 "sysY.y"

int s2eerror(const char* error)
{
	fprintf(stderr, "Line %d: %s\n", lineNo, error);
	exit(1);
}
void dele_tree(s_basenode* root){
  auto s = root->Son;
  if(s.size() == 0){
    delete(root);
    return;
  }
  for(int i = 0; i < s.size(); i++){
    dele_tree(s[i]);
  }
  delete(root);
  return;
}

int s2e(char* infile, char* outfile){
    lineNo = 1;
	s2eout = fopen(outfile,"w");
    s2ein = fopen(infile,"r");
	yyparse();
	scantree(root);
  fclose(s2eout);
  fclose(s2ein);
  dele_tree(root);
	return 0;
}
