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




/* First part of user prologue.  */
#line 6 "decaf.y"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "include/quad.h"
    #include "include/liste.h"
    #include "include/table_symb.h"

    #define TAB_SYMBOLES (*((ctx**)tab_symbole))
    #define ERROR(msg) yyerror(tab_symbole,code_inter,next_quad,"-ERREUR-\t"msg".")

    extern int yylex();
    /* extern int numero_type[]; */
    #define YYDEBUG 1

    void yyerror (void**,void**,int*,const char* msg);

    //LONGUEUR MAXIMALE D'UN NOM DE TEMPORAIRE
    #define SIZE_MAX_NAME_TEMP 10

    //QUAD_OP SOUVENT UTILISES
    quad_op qo_vide = {QO_VIDE,-1};
    quad_op qo_un = {QO_CST,1};
    quad_op qo_zero = {QO_CST,0};

    //ITERATEUR DU NOMBRE DE TEMPORAIRES
    int num_temp = 0;

    //AJOUTE LE CODE A code_inter
    void gencode(void**,int*,q_type,quad_op,quad_op,quad_op);

    //COMPLETE LES QUADS DONT LE NUMERO EST DANS l PAR q
    void complete_liste(void** code_inter, int* l, int size, int q);

    //ITERATEUR DE CTX DE LA TABLE
    ctx* current_ctx = NULL;    

    extern char yytext[];

#line 110 "decaf.tab.c"

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
#ifndef YY_YY_DECAF_TAB_H_INCLUDED
# define YY_YY_DECAF_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "decaf.y"

    #include "include/quad.h"   
    #include "include/write_code.h" 

#line 158 "decaf.tab.c"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VIRG = 258,
    OP_PAR = 259,
    OP_CRO = 260,
    OP_BRA = 261,
    CL_BRA = 262,
    CL_CRO = 263,
    CL_PAR = 264,
    BEG = 265,
    SM = 266,
    TYPE_VOID = 267,
    U_MOINS = 268,
    IF = 269,
    ELSE = 270,
    FOR = 271,
    BREAK = 272,
    CONTINUE = 273,
    RETURN = 274,
    ID = 275,
    STRING_LIT = 276,
    HEX_LIT = 277,
    DEC_LIT = 278,
    CHAR_LIT = 279,
    WS = 280,
    BOOL_TRUE = 281,
    BOOL_FALSE = 282,
    OP_PLUS = 283,
    OP_SUB = 284,
    OP_MULT = 285,
    OP_DIV = 286,
    OP_RES = 287,
    OP_LESS = 288,
    OP_GREAT = 289,
    OP_LESS_EQ = 290,
    OP_GREAT_EQ = 291,
    OP_EQ = 292,
    OP_NOT_EQ = 293,
    OP_AND = 294,
    OP_OR = 295,
    OP_NOT = 296,
    AFF_EQ = 297,
    AFF_INC = 298,
    AFF_DEC = 299,
    TYPE_INT = 300,
    TYPE_BOOL = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 64 "decaf.y"

    char *str_val;
    long int int_val;

    // liste de types (typiquement utilisée pour les arguments de fonction)
    type_liste type_liste;
    // liste contenant l'état d'un bloc (break, return, etc...)
    control_liste control_liste;
    // expr (listes booléennes, entier, etc...)
    expr_val expr_val;

#line 228 "decaf.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void** tab_symbole, void* code_inter[], int* next_quad);

#endif /* !YY_YY_DECAF_TAB_H_INCLUDED  */



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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

#define YYUNDEFTOK  2
#define YYMAXUTOK   301


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   146,   146,   166,   187,   188,   192,   196,   197,   201,
     208,   218,   219,   224,   235,   245,   223,   263,   274,   283,
     262,   302,   306,   314,   322,   337,   347,   355,   363,   364,
     368,   372,   379,   390,   394,   403,   424,   435,   444,   489,
     493,   502,   524,   544,   523,   565,   570,   580,   590,   597,
     601,   610,   619,   623,   627,   636,   665,   674,   683,   709,
     743,   763,   791,   806,   825,   838,   848,   858,   868,   878,
     888,   898,   908,   918,   928,   944,   960,   972,   985,   995,
    1005,  1012,  1021,  1026,  1031,  1037,  1046,  1056,  1070,  1076
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VIRG", "OP_PAR", "OP_CRO", "OP_BRA",
  "CL_BRA", "CL_CRO", "CL_PAR", "BEG", "SM", "TYPE_VOID", "U_MOINS", "IF",
  "ELSE", "FOR", "BREAK", "CONTINUE", "RETURN", "ID", "STRING_LIT",
  "HEX_LIT", "DEC_LIT", "CHAR_LIT", "WS", "BOOL_TRUE", "BOOL_FALSE",
  "OP_PLUS", "OP_SUB", "OP_MULT", "OP_DIV", "OP_RES", "OP_LESS",
  "OP_GREAT", "OP_LESS_EQ", "OP_GREAT_EQ", "OP_EQ", "OP_NOT_EQ", "OP_AND",
  "OP_OR", "OP_NOT", "AFF_EQ", "AFF_INC", "AFF_DEC", "TYPE_INT",
  "TYPE_BOOL", "$accept", "program", "push_deb", "field_decls",
  "field_decl", "field_ids", "field_id", "method_decls", "method_decl",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "method_decl_args",
  "method_decl_arg", "block", "push", "pop", "var_decls", "var_decl",
  "var_ids", "type", "statements", "statement", "$@7", "$@8", "return_res",
  "N", "assign_op", "method_call", "method_call_args", "method_call_arg",
  "location", "expr", "M", "literal", "int_literal", "bool_literal", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF (-103)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-14)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,     8,    43,    24,  -103,  -103,  -103,     1,    25,  -103,
    -103,  -103,     1,  -103,    49,  -103,  -103,    45,    54,    -1,
       3,  -103,  -103,  -103,  -103,    10,  -103,    74,  -103,    98,
    -103,  -103,    89,    99,   101,  -103,    26,  -103,    26,  -103,
     104,    84,  -103,   100,    26,  -103,   102,   107,    88,   107,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,    26,  -103,  -103,
    -103,    92,  -103,  -103,    14,   186,    94,  -103,   112,    97,
     150,   152,    69,    95,   114,  -103,   157,  -103,   154,     6,
    -103,    69,   156,  -103,  -103,    69,  -103,  -103,  -103,  -103,
      69,    69,   188,  -103,  -103,   120,  -103,  -103,  -103,    69,
      69,    32,  -103,  -103,  -103,  -103,  -103,    69,   106,    69,
     138,  -103,  -103,  -103,    69,    69,    69,    69,    69,    69,
      69,    69,    69,  -103,  -103,  -103,  -103,   192,   204,   120,
      93,   199,   151,  -103,    48,  -103,    30,    30,  -103,  -103,
    -103,   165,   165,   165,   165,    69,    69,    69,    69,  -103,
      69,  -103,   198,  -103,   107,    69,   207,   207,   196,   184,
     120,  -103,   195,   120,  -103,  -103,  -103,  -103,   107,   107,
    -103,  -103
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     5,     0,     0,    33,
      34,     4,    27,    12,     0,    17,    11,     0,     0,     9,
       0,     8,    26,     2,    13,     0,    26,     0,     6,     0,
      87,    86,     0,     0,     9,     7,    22,    10,    22,    18,
      21,     0,    14,     0,     0,    24,     0,     0,     0,     0,
      26,    19,    23,    15,    29,    27,    27,    36,    20,    16,
      28,     0,    81,    32,     0,    27,     0,    30,     0,     0,
       0,     0,    50,    60,     0,    48,     0,    35,     0,     0,
      31,     0,     0,    46,    47,     0,    85,    84,    89,    88,
       0,     0,     0,    63,    62,    49,    64,    82,    83,    57,
       0,     0,    25,    39,    52,    53,    54,     0,     0,     0,
       0,    78,    79,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,    81,    81,    81,     0,    56,    59,
       0,     0,     0,    81,     0,    80,    65,    66,    67,    68,
      69,    72,    70,    73,    71,     0,     0,     0,     0,    55,
       0,    61,     0,    38,     0,     0,    74,    75,    77,    76,
      58,    37,    40,    42,    51,    81,    81,    43,     0,     0,
      41,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,  -103,  -103,  -103,  -103,   217,  -103,   233,  -103,
    -103,  -103,  -103,  -103,  -103,   208,  -103,   -49,   -24,   -47,
    -103,  -103,  -103,     0,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,   182,  -103,  -103,   183,   -80,  -102,   148,   225,  -103
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,    11,    20,    21,    12,    13,    26,
      46,    56,    22,    43,    55,    39,    40,    51,    29,    17,
      57,    60,    64,    41,    62,    77,   165,   169,    92,   166,
     107,    93,   127,   128,    94,    95,    65,    96,    97,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,   108,    33,   -13,    25,   110,    27,    14,    58,    59,
     111,   112,    18,     8,    28,     1,    75,    66,    76,   129,
     130,   145,   146,   147,   148,    67,    54,   132,     3,   134,
       5,   154,    30,    31,   136,   137,   138,   139,   140,   141,
     142,   143,   144,     4,    48,    15,     9,    10,   104,   105,
     106,   155,    23,    86,    30,    31,    87,    61,    88,    89,
     116,   117,   118,   167,   168,   156,   157,   158,   159,    19,
     160,     9,    10,    85,    24,   163,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    73,
      86,    30,    31,    87,    34,    88,    89,    37,    90,    99,
     100,   151,    36,    38,    45,   162,    25,    44,    52,    47,
      91,    49,    63,    50,    80,   133,    81,    82,   101,   170,
     171,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   135,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,    83,   153,    84,   102,   103,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    50,   114,   115,   116,   117,   118,   109,   113,
      68,   149,    69,    70,    71,    72,    73,   150,   152,   161,
     164,    74,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    35,    16,    42,    78,    79,   131,
      32
};

static const yytype_uint8 yycheck[] =
{
      49,    81,    26,     4,     5,    85,     3,     7,    55,    56,
      90,    91,    12,    12,    11,    10,    65,     3,    65,    99,
     100,   123,   124,   125,   126,    11,    50,   107,    20,   109,
       6,   133,    22,    23,   114,   115,   116,   117,   118,   119,
     120,   121,   122,     0,    44,    20,    45,    46,    42,    43,
      44,     3,     7,    21,    22,    23,    24,    57,    26,    27,
      30,    31,    32,   165,   166,   145,   146,   147,   148,    20,
     150,    45,    46,     4,    20,   155,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    20,
      21,    22,    23,    24,    20,    26,    27,     8,    29,     4,
       5,     8,     4,     4,    20,   154,     5,     3,    20,     9,
      41,     9,    20,     6,    20,     9,     4,    20,     4,   168,
     169,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     9,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    11,    11,    11,     7,    11,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     6,    28,    29,    30,    31,    32,    42,    11,
      14,     9,    16,    17,    18,    19,    20,     3,     9,    11,
      15,    25,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    27,    12,    38,    65,    65,   101,
      25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    48,    20,     0,     6,    49,    50,    12,    45,
      46,    51,    54,    55,    70,    20,    55,    66,    70,    20,
      52,    53,    59,     7,    20,     5,    56,     3,    11,    65,
      22,    23,    85,    65,    20,    53,     4,     8,     4,    62,
      63,    70,    62,    60,     3,    20,    57,     9,    70,     9,
       6,    64,    20,    64,    65,    61,    58,    67,    66,    66,
      68,    70,    71,    20,    69,    83,     3,    11,    14,    16,
      17,    18,    19,    20,    25,    64,    66,    72,    78,    81,
      20,     4,    20,    11,    11,     4,    21,    24,    26,    27,
      29,    41,    75,    78,    81,    82,    84,    85,    86,     4,
       5,     4,     7,    11,    42,    43,    44,    77,    82,    42,
      82,    82,    82,    11,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    79,    80,    82,
      82,    84,    82,     9,    82,     9,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    83,    83,    83,    83,     9,
       3,     8,     9,    11,    83,     3,    82,    82,    82,    82,
      82,    11,    64,    82,    15,    73,    76,    83,    83,    74,
      64,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    50,    50,    51,    52,    52,    53,
      53,    54,    54,    56,    57,    58,    55,    59,    60,    61,
      55,    62,    62,    63,    63,    64,    65,    66,    67,    67,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    72,
      72,    72,    73,    74,    72,    72,    72,    72,    72,    75,
      75,    76,    77,    77,    77,    78,    79,    79,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    83,    84,    84,    84,    84,    85,    85,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     0,     2,     0,     3,     3,     1,     1,
       4,     2,     1,     0,     0,     0,    11,     0,     0,     0,
      11,     1,     0,     4,     2,     7,     0,     0,     2,     0,
       3,     3,     1,     1,     1,     3,     0,     5,     4,     2,
       6,    10,     0,     0,    10,     3,     2,     2,     1,     1,
       0,     0,     1,     1,     1,     4,     1,     0,     3,     1,
       1,     4,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     4,     4,     4,     2,     2,
       3,     0,     1,     1,     1,     1,     1,     1,     1,     1
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
        yyerror (tab_symbole, code_inter, next_quad, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

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
                  Type, Value, tab_symbole, code_inter, next_quad); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void** tab_symbole, void* code_inter[], int* next_quad)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (tab_symbole);
  YYUSE (code_inter);
  YYUSE (next_quad);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void** tab_symbole, void* code_inter[], int* next_quad)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, tab_symbole, code_inter, next_quad);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void** tab_symbole, void* code_inter[], int* next_quad)
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
                                              , tab_symbole, code_inter, next_quad);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, tab_symbole, code_inter, next_quad); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void** tab_symbole, void* code_inter[], int* next_quad)
{
  YYUSE (yyvaluep);
  YYUSE (tab_symbole);
  YYUSE (code_inter);
  YYUSE (next_quad);
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
yyparse (void** tab_symbole, void* code_inter[], int* next_quad)
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
#line 147 "decaf.y"
            {
                int trouve = 0;

                for(int i = 0; i<TAB_SYMBOLES->size_tab; i++){
                    if(strcmp(TAB_SYMBOLES->tab[i].name,"main")==0
                    && TAB_SYMBOLES->tab[i].type.proc.nb_arg==0
                    && TAB_SYMBOLES->tab[i].type.proc.retour==T_VOID){
                        trouve=1;
                    }
                }
                
                if(trouve==0){
                    ERROR("Main non défini");
                    YYABORT;
                }
            }
#line 1563 "decaf.tab.c"
    break;

  case 3:
#line 167 "decaf.y"
            {
                TAB_SYMBOLES = push_ctx(TAB_SYMBOLES, CTX_SIMP);
                current_ctx = TAB_SYMBOLES;

                int* list_i = malloc(1*sizeof(int));
                list_i[0] = T_INT;
                newname_proc_ext("WriteInt",list_i,1,T_VOID,current_ctx);

                int* list_b = malloc(1*sizeof(int));
                list_b[0] = T_BOOL;
                newname_proc_ext("WriteBool",list_b,1,T_VOID,current_ctx);

                newname_proc_ext("ReadInt",NULL,0,T_INT,current_ctx);

                gencode(code_inter,next_quad,Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);
            }
#line 1584 "decaf.tab.c"
    break;

  case 9:
#line 202 "decaf.y"
            {
                if(newname_var_glb((yyvsp[0].str_val),(yyvsp[-1].int_val),current_ctx)==NULL){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1595 "decaf.tab.c"
    break;

  case 10:
#line 209 "decaf.y"
            {
                if( newname_tab((yyvsp[-3].str_val),(yyvsp[-4].int_val),(yyvsp[-1].expr_val).result.qo.qo_valeur.cst,current_ctx)==NULL ){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1606 "decaf.tab.c"
    break;

  case 13:
#line 224 "decaf.y"
            {
                if( strncmp("label",(yyvsp[0].str_val),5)==0 ){
                    ERROR("Méthode commencant par label interdite");
                    YYABORT;
                }
                if( newname_proc((yyvsp[0].str_val),NULL,0,(yyvsp[-1].int_val),current_ctx)==NULL ){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1621 "decaf.tab.c"
    break;

  case 14:
#line 235 "decaf.y"
            {
                symbole* s_meth = look_up((yyvsp[-4].str_val),TAB_SYMBOLES);
                s_meth->type.proc.nb_arg = (yyvsp[0].type_liste).size;
                s_meth->type.proc.arg = (yyvsp[0].type_liste).list;
                s_meth->type.proc.retour = (yyvsp[-5].int_val);

                write_method_void_decl_args(code_inter, next_quad, current_ctx, &num_temp, s_meth, (yyvsp[0].type_liste));

            }
#line 1635 "decaf.tab.c"
    break;

  case 15:
#line 245 "decaf.y"
            {
                symbole* s_meth = look_up((yyvsp[-7].str_val),TAB_SYMBOLES);

                if((yyvsp[0].control_liste).size_return!=0 && (yyvsp[0].control_liste).type_return!=(yyvsp[-8].int_val)){
                    ERROR("Types de retour incohérents");
                    YYABORT;
                }

                quad_op qo_name_meth, qo_nb_arg;
                new_qo_name(look_up((yyvsp[-7].str_val),TAB_SYMBOLES)->name,&(qo_name_meth));
                new_qo_cst((yyvsp[-3].type_liste).size,&(qo_nb_arg));
                
                gencode(code_inter,next_quad,Q_END_METH,qo_vide,qo_vide,qo_vide);
                complete_liste(code_inter,(yyvsp[0].control_liste).l_return,(yyvsp[0].control_liste).size_return,(*next_quad));
                gencode(code_inter,next_quad,Q_END_METH,qo_name_meth,qo_nb_arg,qo_vide);  
            }
#line 1656 "decaf.tab.c"
    break;

  case 17:
#line 263 "decaf.y"
            {
                if( strncmp("label",(yyvsp[0].str_val),5)==0 ){
                    ERROR("Mot commencant par label interdit");
                    YYABORT;
                }
                if( newname_proc((yyvsp[0].str_val),NULL,0,T_VOID,current_ctx)==NULL){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1671 "decaf.tab.c"
    break;

  case 18:
#line 274 "decaf.y"
            {
                symbole* s_meth = look_up((yyvsp[-4].str_val),TAB_SYMBOLES);
                s_meth->type.proc.nb_arg = (yyvsp[0].type_liste).size;
                s_meth->type.proc.arg = (yyvsp[0].type_liste).list;
                s_meth->type.proc.retour = T_VOID;

                write_method_void_decl_args(code_inter, next_quad, current_ctx, &num_temp, s_meth, (yyvsp[0].type_liste));
            }
#line 1684 "decaf.tab.c"
    break;

  case 19:
#line 283 "decaf.y"
            {
                symbole* s_meth = look_up((yyvsp[-7].str_val),TAB_SYMBOLES);

                if((yyvsp[0].control_liste).size_return!=0 && (yyvsp[0].control_liste).type_return!=T_VOID){
                    ERROR("Types de retour incohérents");
                    YYABORT;
                }
                
                quad_op qo_name_meth, qo_nb_arg;
                new_qo_name(look_up((yyvsp[-7].str_val),TAB_SYMBOLES)->name,&(qo_name_meth));
                new_qo_cst((yyvsp[-3].type_liste).size,&(qo_nb_arg));

                complete_liste(code_inter,(yyvsp[0].control_liste).l_return,(yyvsp[0].control_liste).size_return,(*next_quad));
                gencode(code_inter,next_quad,Q_END_METH,qo_name_meth,qo_nb_arg,qo_vide);
            }
#line 1704 "decaf.tab.c"
    break;

  case 21:
#line 303 "decaf.y"
            {
                (yyval.type_liste) = (yyvsp[0].type_liste);
            }
#line 1712 "decaf.tab.c"
    break;

  case 22:
#line 307 "decaf.y"
            {
                (yyval.type_liste).list = NULL;
                (yyval.type_liste).size = 0;
            }
#line 1721 "decaf.tab.c"
    break;

  case 23:
#line 315 "decaf.y"
            {
                (yyval.type_liste).list = concat_liste_int((int*)(yyvsp[-3].type_liste).list,(yyvsp[-1].int_val),(yyvsp[-3].type_liste).size,&((yyval.type_liste).size));
                if( newname_arg((yyvsp[0].str_val),(yyvsp[-1].int_val),current_ctx)==NULL){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1733 "decaf.tab.c"
    break;

  case 24:
#line 323 "decaf.y"
            {
                (yyval.type_liste).list = malloc(1*sizeof(int));
                (yyval.type_liste).list[0] = (yyvsp[-1].int_val);
                (yyval.type_liste).size = 1;
                if( newname_arg((yyvsp[0].str_val),(yyvsp[-1].int_val),current_ctx)==NULL){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1747 "decaf.tab.c"
    break;

  case 25:
#line 338 "decaf.y"
            {
                complete_liste(code_inter,(yyvsp[-3].control_liste).l_next,(yyvsp[-3].control_liste).size_next,(yyvsp[-2].int_val));
                (yyval.control_liste) = (yyvsp[-3].control_liste);
                (yyval.control_liste).l_next = creer_liste((*next_quad),&((yyval.control_liste).size_next));
                gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);
            }
#line 1758 "decaf.tab.c"
    break;

  case 26:
#line 348 "decaf.y"
            {
                current_ctx = push_ctx(current_ctx, CTX_SIMP);
                gencode(code_inter,next_quad,Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);
            }
#line 1767 "decaf.tab.c"
    break;

  case 27:
#line 356 "decaf.y"
            {
                current_ctx = current_ctx->prec;
                gencode(code_inter,next_quad,Q_POP_CTX,qo_vide,qo_vide,qo_vide);
            }
#line 1776 "decaf.tab.c"
    break;

  case 31:
#line 373 "decaf.y"
            {   
                if(newname_var((yyvsp[0].str_val),(yyvsp[-3].int_val),current_ctx)==NULL){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1787 "decaf.tab.c"
    break;

  case 32:
#line 380 "decaf.y"
            {
                if(newname_var((yyvsp[0].str_val),(yyvsp[-1].int_val),current_ctx)==NULL){
                    ERROR("Redéfinition d'un identifiant de la même portée");
                    YYABORT;
                }
            }
#line 1798 "decaf.tab.c"
    break;

  case 33:
#line 391 "decaf.y"
            {
                (yyval.int_val) = T_INT;
            }
#line 1806 "decaf.tab.c"
    break;

  case 34:
#line 395 "decaf.y"
            {
                (yyval.int_val) = T_BOOL;
            }
#line 1814 "decaf.tab.c"
    break;

  case 35:
#line 404 "decaf.y"
            {

                complete_liste(code_inter,(yyvsp[-2].control_liste).l_next,(yyvsp[-2].control_liste).size_next,(yyvsp[-1].int_val));
                (yyval.control_liste).l_next = (yyvsp[0].control_liste).l_next;
                (yyval.control_liste).size_next = (yyvsp[0].control_liste).size_next;
                (yyval.control_liste).l_break = concat_listes((yyvsp[-2].control_liste).l_break,(yyvsp[0].control_liste).l_break,(yyvsp[-2].control_liste).size_break,(yyvsp[0].control_liste).size_break,&((yyval.control_liste).size_break));
                (yyval.control_liste).l_continue = concat_listes((yyvsp[-2].control_liste).l_continue,(yyvsp[0].control_liste).l_continue,(yyvsp[-2].control_liste).size_continue,(yyvsp[0].control_liste).size_continue,&((yyval.control_liste).size_continue));
                (yyval.control_liste).l_return = concat_listes((yyvsp[-2].control_liste).l_return,(yyvsp[0].control_liste).l_return,(yyvsp[-2].control_liste).size_return,(yyvsp[0].control_liste).size_return,&((yyval.control_liste).size_return));
                
                if( (yyvsp[-2].control_liste).type_return==T_VOID){
                    (yyval.control_liste).type_return=(yyvsp[0].control_liste).type_return;
                } else if( (yyvsp[0].control_liste).type_return==T_VOID){
                    (yyval.control_liste).type_return=(yyvsp[-2].control_liste).type_return;
                } else if( (yyvsp[0].control_liste).type_return!=(yyvsp[-2].control_liste).type_return ){
                    ERROR("Types de retour incohérents");
                    YYABORT;
                } else {
                    (yyval.control_liste).type_return=(yyvsp[0].control_liste).type_return;
                }
            }
#line 1839 "decaf.tab.c"
    break;

  case 36:
#line 425 "decaf.y"
            {
                (yyval.control_liste).l_break = creer_liste_vide(&((yyval.control_liste).size_break));
                (yyval.control_liste).l_continue = creer_liste_vide(&((yyval.control_liste).size_continue));
                (yyval.control_liste).l_return = creer_liste_vide(&((yyval.control_liste).size_return));
                (yyval.control_liste).l_next = creer_liste_vide(&((yyval.control_liste).size_next));
                (yyval.control_liste).type_return = T_VOID;
            }
#line 1851 "decaf.tab.c"
    break;

  case 37:
#line 436 "decaf.y"
            {
                if((yyvsp[-2].expr_val).type!=T_STRING){
                    ERROR("WriteString n'accepte que des Strings en argument");
                    YYABORT;
                }             
                gencode(code_inter,next_quad,Q_PRINT,qo_vide,qo_vide,(yyvsp[-2].expr_val).result.qo);
                write_empty_stat(&(yyval.control_liste));
            }
#line 1864 "decaf.tab.c"
    break;

  case 38:
#line 446 "decaf.y"
            {
                // entier
                // Q_COPY : loc : _ : result
                // tab
                // Q_COPY : loc : dplc : result
                // loc ou result sont des tableaux, on le verifie apres                
                
                if( (yyvsp[-2].int_val)==AFF_INC ){    
                    if( (yyvsp[-3].expr_val).type!=(yyvsp[-1].expr_val).type || (yyvsp[-3].expr_val).type!=T_INT ){
                        ERROR("Incrémentation entre entiers uniquement");
                        YYABORT;   
                    } else {
                        write_inc_dec(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[-1].expr_val), Q_ADD);
                    }                                                
                }

                if((yyvsp[-2].int_val)==AFF_DEC){
                    if((yyvsp[-3].expr_val).type!=(yyvsp[-1].expr_val).type || (yyvsp[-3].expr_val).type!=T_INT){
                        ERROR("Décrémentation entre entiers uniquement");
                        YYABORT;   
                    } else {
                        write_inc_dec(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[-1].expr_val), Q_SUB);
                    }                                                
                }

                if((yyvsp[-2].int_val)==Q_COPY){
                    if((yyvsp[-3].expr_val).type==T_INT && (yyvsp[-1].expr_val).type==T_INT){
                        gencode(code_inter,next_quad,Q_COPY,(yyvsp[-1].expr_val).result.qo,(yyvsp[-3].expr_val).dplc,(yyvsp[-3].expr_val).result.qo);
                    } else if ((yyvsp[-3].expr_val).type==T_BOOL && (yyvsp[-1].expr_val).type==T_BOOL) {
                        write_assign_bool(code_inter, next_quad, current_ctx, (yyvsp[-3].expr_val), (yyvsp[-1].expr_val));
                    } else {    
                        ERROR("Assignation entre types différents interdite");
                        YYABORT;    
                    }
                }

                (yyval.control_liste).l_next = creer_liste_vide(&(yyval.control_liste).size_next);
                (yyval.control_liste).l_continue = creer_liste_vide(&(yyval.control_liste).size_continue);
                (yyval.control_liste).l_break = creer_liste_vide(&(yyval.control_liste).size_break);
                (yyval.control_liste).l_return = creer_liste_vide(&(yyval.control_liste).size_return);
                (yyval.control_liste).type_return = T_VOID;

            }
#line 1912 "decaf.tab.c"
    break;

  case 39:
#line 490 "decaf.y"
            {
                write_empty_stat(&(yyval.control_liste));
            }
#line 1920 "decaf.tab.c"
    break;

  case 40:
#line 494 "decaf.y"
            {
                if( (yyvsp[-3].expr_val).type != T_BOOL ){
                    ERROR("L'expression évaluée dans le if doit être booléenne");
                    YYABORT;
                } else {
                    write_if_stat(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[-1].int_val), (yyvsp[0].control_liste), &(yyval.control_liste));
                }
            }
#line 1933 "decaf.tab.c"
    break;

  case 41:
#line 503 "decaf.y"
            {
                if( (yyvsp[-7].expr_val).type != T_BOOL ){
                    ERROR("L'expression évaluée dans le if doit être booléenne");
                    YYABORT;
                } else {
                    write_if_else_stat(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-7].expr_val), (yyvsp[-5].int_val), (yyvsp[-4].control_liste), (yyvsp[-2].control_liste), (yyvsp[-1].int_val), (yyvsp[0].control_liste), &(yyval.control_liste));

                    if( (yyvsp[-4].control_liste).type_return==T_VOID){
                        (yyval.control_liste).type_return=(yyvsp[0].control_liste).type_return;
                    } else if( (yyvsp[0].control_liste).type_return==T_VOID){
                        (yyval.control_liste).type_return=(yyvsp[-4].control_liste).type_return;
                    } else if( (yyvsp[0].control_liste).type_return!=(yyvsp[-4].control_liste).type_return ){
                        ERROR("Types de retour incohérents");
                        YYABORT;
                    } else {
                        (yyval.control_liste).type_return=(yyvsp[-4].control_liste).type_return;
                    }            
                }
            
            }
#line 1958 "decaf.tab.c"
    break;

  case 42:
#line 524 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Les bornes de la boucle for doivent être des entiers");
                    YYABORT;
                }

                current_ctx = push_ctx(current_ctx, CTX_FOR);
                gencode(code_inter,next_quad,Q_PUSH_CTX,qo_vide,qo_vide,qo_vide);
                
                //protection des variables de controle de la boucle for
                symbole* s_ite;
                s_ite=newname_var((yyvsp[-4].str_val),T_INT,current_ctx);

                quad_op qo_ite;
                new_qo_name(s_ite->name,&(qo_ite));
                
                //ite = borne_inf
                gencode(code_inter,next_quad,Q_COPY,(yyvsp[-2].expr_val).result.qo,qo_vide,qo_ite);
            }
#line 1982 "decaf.tab.c"
    break;

  case 43:
#line 544 "decaf.y"
            {
                //vérification que ite < borne_sup
                quad_op qo_ite;
                new_qo_name(look_up((yyvsp[-6].str_val),current_ctx)->name,&(qo_ite));
                gencode(code_inter,next_quad,Q_GREAT,qo_ite,(yyvsp[-2].expr_val).result.qo,qo_vide); 
            }
#line 1993 "decaf.tab.c"
    break;

  case 44:
#line 551 "decaf.y"
            {

                write_end_loop_for_stat(code_inter, next_quad, &current_ctx, &num_temp, (yyvsp[-8].str_val), (yyvsp[-2].int_val), (yyvsp[0].control_liste));

                //on part de la boucle
                (yyval.control_liste).l_next = creer_liste((*next_quad),&((yyval.control_liste).size_next));
                (yyval.control_liste).l_continue = creer_liste_vide(&((yyval.control_liste).size_continue));
                (yyval.control_liste).l_break = creer_liste_vide(&((yyval.control_liste).size_break));
                (yyval.control_liste).l_return = (yyvsp[0].control_liste).l_return;
                (yyval.control_liste).size_return = (yyvsp[0].control_liste).size_return;
                (yyval.control_liste).type_return = (yyvsp[0].control_liste).type_return;

                gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);
            }
#line 2012 "decaf.tab.c"
    break;

  case 45:
#line 566 "decaf.y"
            {
                write_empty_stat(&(yyval.control_liste));   
                write_return_stat(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-1].expr_val), &(yyval.control_liste));
            }
#line 2021 "decaf.tab.c"
    break;

  case 46:
#line 571 "decaf.y"
            {
                if( dans_ctx_for(current_ctx)==0 ){
                    ERROR("Instruction break en-dehors d'une boucle for");
                    YYABORT;
                }
                write_empty_stat(&(yyval.control_liste));
                (yyval.control_liste).l_break = creer_liste((*next_quad),&((yyval.control_liste).size_break));
                gencode(code_inter,next_quad,Q_BREAK,qo_vide,qo_vide,qo_vide);
            }
#line 2035 "decaf.tab.c"
    break;

  case 47:
#line 581 "decaf.y"
            {
                if( dans_ctx_for(current_ctx)==0 ){
                    ERROR("Instruction continue en-dehors d'une boucle for");
                    YYABORT;
                }
                write_empty_stat(&(yyval.control_liste));
                (yyval.control_liste).l_continue = creer_liste((*next_quad),&((yyval.control_liste).size_continue));
                gencode(code_inter,next_quad,Q_CONTINUE,qo_vide,qo_vide,qo_vide);
            }
#line 2049 "decaf.tab.c"
    break;

  case 48:
#line 591 "decaf.y"
            {
                (yyval.control_liste) = (yyvsp[0].control_liste);
            }
#line 2057 "decaf.tab.c"
    break;

  case 49:
#line 598 "decaf.y"
            {
                (yyval.expr_val) = (yyvsp[0].expr_val);
            }
#line 2065 "decaf.tab.c"
    break;

  case 50:
#line 602 "decaf.y"
            {
                (yyval.expr_val).type = T_VOID;
                new_qo_vide(&(yyval.expr_val).dplc);
                new_qo_vide(&(yyval.expr_val).result.qo);
            }
#line 2075 "decaf.tab.c"
    break;

  case 51:
#line 611 "decaf.y"
            {
                (yyval.control_liste).l_next = creer_liste((*next_quad),&((yyval.control_liste).size_next));
                gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);
            }
#line 2084 "decaf.tab.c"
    break;

  case 52:
#line 620 "decaf.y"
            {   
                (yyval.int_val) = Q_COPY;    
            }
#line 2092 "decaf.tab.c"
    break;

  case 53:
#line 624 "decaf.y"
            {
                (yyval.int_val) = AFF_INC;
            }
#line 2100 "decaf.tab.c"
    break;

  case 54:
#line 628 "decaf.y"
            {
                (yyval.int_val) =AFF_DEC;
            }
#line 2108 "decaf.tab.c"
    break;

  case 55:
#line 637 "decaf.y"
            {
               
                
                symbole* s_meth = look_up((yyvsp[-3].str_val),TAB_SYMBOLES);

                //vérification de l'existence de la methode
                if(s_meth==NULL || s_meth->fonction!=F_METH){
                    ERROR("Appel à une méthode non définie");
                    YYABORT;
                }
                //vérification du nombre d'arguments
                if(s_meth->type.proc.nb_arg!=(yyvsp[-1].type_liste).size){
                    ERROR("Nombre d'arguments incohérent");
                    YYABORT;
                }
                //vérification du type
                for(int i = 0; i<(yyvsp[-1].type_liste).size; i++){
                    if( s_meth->type.proc.arg[i]!=(yyvsp[-1].type_liste).list[i] ){
                        ERROR("Le type des arguments de l'appel ne correspond pas à la définition de la méthode");
                        YYABORT;
                    }
                }

                write_method_call(code_inter, next_quad, current_ctx, &num_temp, s_meth, (yyvsp[-1].type_liste), &(yyval.expr_val));
            }
#line 2138 "decaf.tab.c"
    break;

  case 56:
#line 666 "decaf.y"
            {
                (yyval.type_liste) = (yyvsp[0].type_liste);
                for(int i = 0; i<(yyvsp[0].type_liste).size; i++){
                    quad_op qo_depl;
                    new_qo_cst(i+1,&(qo_depl));
                    gencode(code_inter,next_quad,Q_PARAM,qo_depl,qo_vide,((yyval.type_liste).list_arg)[i]);
                }
            }
#line 2151 "decaf.tab.c"
    break;

  case 57:
#line 675 "decaf.y"
            {
                (yyval.type_liste).list_arg = NULL;
                (yyval.type_liste).list = NULL;
                (yyval.type_liste).size = 0;
            }
#line 2161 "decaf.tab.c"
    break;

  case 58:
#line 684 "decaf.y"
            {
                (yyval.type_liste).list = concat_liste_int((int*)(yyvsp[-2].type_liste).list,(yyvsp[0].expr_val).type,(yyvsp[-2].type_liste).size,&((yyval.type_liste).size));
                (yyval.type_liste).list_arg = realloc((yyvsp[-2].type_liste).list_arg,((yyvsp[-2].type_liste).size +1)*sizeof(quad_op));

                quad_op qo_arg, qo_depl;
                //réification
                if((yyvsp[0].expr_val).type==T_BOOL){
                    complete_liste(code_inter,(yyvsp[0].expr_val).result.liste_bool.liste_true,(yyvsp[0].expr_val).result.liste_bool.size_true,(*next_quad));
                    complete_liste(code_inter,(yyvsp[0].expr_val).result.liste_bool.liste_false,(yyvsp[0].expr_val).result.liste_bool.size_false,(*next_quad)+2);
                    
                    symbole* s_temp = newname_temp(T_BOOL,current_ctx,&(num_temp));
                    quad_op qo_next;
                    new_qo_name(s_temp->name,&(qo_arg));
                    new_qo_cst((*next_quad)+3,&qo_next);

                    gencode(code_inter,next_quad,Q_COPY,qo_un,qo_vide,qo_arg);
                    gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_next);
                    gencode(code_inter,next_quad,Q_COPY,qo_zero,qo_vide,qo_arg); 
                } else if ((yyvsp[0].expr_val).type==T_INT){
                    new_qo_name((yyvsp[0].expr_val).result.qo.qo_valeur.name,&(qo_arg));
                }

                new_qo_name(qo_arg.qo_valeur.name,&((yyval.type_liste).list_arg[(yyvsp[-2].type_liste).size]));

            }
#line 2191 "decaf.tab.c"
    break;

  case 59:
#line 710 "decaf.y"
            {
                (yyval.type_liste).list = malloc(1*sizeof(int));
                (yyval.type_liste).list[0] = (yyvsp[0].expr_val).type;
                (yyval.type_liste).size = 1;
                (yyval.type_liste).list_arg = malloc(1*sizeof(quad_op));

                quad_op qo_arg, qo_depl;
                //réification
                if((yyvsp[0].expr_val).type==T_BOOL){
                    complete_liste(code_inter,(yyvsp[0].expr_val).result.liste_bool.liste_true,(yyvsp[0].expr_val).result.liste_bool.size_true,(*next_quad));
                    complete_liste(code_inter,(yyvsp[0].expr_val).result.liste_bool.liste_false,(yyvsp[0].expr_val).result.liste_bool.size_false,(*next_quad)+2);
                    
                    symbole* s_temp = newname_temp(T_BOOL,current_ctx,&(num_temp));
                    quad_op qo_next;
                    new_qo_name(s_temp->name,&(qo_arg));
                    new_qo_cst((*next_quad)+3,&qo_next);


                    gencode(code_inter,next_quad,Q_COPY,qo_un,qo_vide,qo_arg);
                    gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_next);
                    gencode(code_inter,next_quad,Q_COPY,qo_zero,qo_vide,qo_arg); 
                } else if ((yyvsp[0].expr_val).type==T_INT){
                    new_qo_name((yyvsp[0].expr_val).result.qo.qo_valeur.name,&(qo_arg));
                }
                
                new_qo_name(qo_arg.qo_valeur.name,&((yyval.type_liste).list_arg[0]));

            }
#line 2224 "decaf.tab.c"
    break;

  case 60:
#line 745 "decaf.y"
            {
                symbole* s_id = look_up((yyvsp[0].str_val),current_ctx);
                if( s_id==NULL ){
                    ERROR("Symbole non défini");
                    YYABORT;
                }
                if( s_id->fonction!=F_METH
                 && s_id->fonction!=F_TAB
                 && s_id->fonction!=F_TEMP)
                {
                    (yyval.expr_val).type = s_id->type.simple;
                    new_qo_vide(&((yyval.expr_val).dplc));
                    new_qo_name(s_id->name,&((yyval.expr_val).result.qo));
                } else {
                    ERROR("Utilisation impossible de la variable");
                    YYABORT;
                }
            }
#line 2247 "decaf.tab.c"
    break;

  case 61:
#line 765 "decaf.y"
            {
                symbole* s_tab = look_up((yyvsp[-3].str_val),current_ctx);
                
                if(s_tab==NULL){
                    ERROR("Tableau non défini");
                    YYABORT;
                }
                if((yyvsp[-1].expr_val).type!=T_INT){
                    ERROR("Index du tableau non entier");
                    YYABORT;
                }

                if( s_tab->fonction==F_TAB ){
                    (yyval.expr_val).type = s_tab->type.tab.simple;
                    (yyval.expr_val).dplc = (yyvsp[-1].expr_val).result.qo;
                    new_qo_name(s_tab->name,&((yyval.expr_val).result.qo));
                } else {
                    ERROR("La variable ne correspond pas à un tableau");
                    YYABORT;
                }
            }
#line 2273 "decaf.tab.c"
    break;

  case 62:
#line 796 "decaf.y"
            {   
                if( (yyvsp[0].expr_val).type==T_BOOL ){
                    write_location_bool_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[0].expr_val), &(yyval.expr_val));
                } else if ( (yyvsp[0].expr_val).type==T_INT ){
                    write_location_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[0].expr_val), &(yyval.expr_val));
                } else {
                    ERROR("Type de l'identificateur non reconnu");
                    YYABORT;
                }
            }
#line 2288 "decaf.tab.c"
    break;

  case 63:
#line 809 "decaf.y"
            {
                (yyval.expr_val).type = (yyvsp[0].expr_val).type;
                new_qo_vide(&((yyval.expr_val).dplc));
                if( (yyvsp[0].expr_val).type == T_INT ){
                    (yyval.expr_val) = (yyvsp[0].expr_val);
                } else if ( (yyvsp[0].expr_val).type == T_BOOL ) {
                    //return renvoie un boolean réifié, on deréifie
                    (yyval.expr_val).result.liste_bool.liste_true = creer_liste((*next_quad),&((yyval.expr_val).result.liste_bool.size_true));
                    (yyval.expr_val).result.liste_bool.liste_false = creer_liste((*next_quad)+1,&((yyval.expr_val).result.liste_bool.size_false));
                    gencode(code_inter,next_quad,Q_IF,(yyvsp[0].expr_val).result.qo,qo_vide,qo_vide);
                    gencode(code_inter,next_quad,Q_GOTO,qo_vide,qo_vide,qo_vide);                     
                } else {
                    ERROR("Retour de méthode incompatible avec les calculs");
                    YYABORT;
                }
            }
#line 2309 "decaf.tab.c"
    break;

  case 64:
#line 828 "decaf.y"
            {
                if( (yyvsp[0].expr_val).type == T_BOOL ){
                    write_bool_to_expr(code_inter,next_quad,(yyvsp[0].expr_val),&(yyval.expr_val));
                } else if( (yyvsp[0].expr_val).type == T_INT ){
                    write_int_to_expr(code_inter,next_quad,current_ctx,&num_temp,(yyvsp[0].expr_val),&(yyval.expr_val));
                } else {
                    ERROR("Littéral non reconnu");
                    YYABORT;                    
                }
            }
#line 2324 "decaf.tab.c"
    break;

  case 65:
#line 840 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),(yyvsp[-2].expr_val),(yyvsp[0].expr_val),&(yyval.expr_val),Q_ADD);  
                }   
            }
#line 2337 "decaf.tab.c"
    break;

  case 66:
#line 850 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),(yyvsp[-2].expr_val),(yyvsp[0].expr_val),&(yyval.expr_val),Q_SUB); 
                }
            }
#line 2350 "decaf.tab.c"
    break;

  case 67:
#line 860 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),(yyvsp[-2].expr_val),(yyvsp[0].expr_val),&(yyval.expr_val),Q_MULT);
                }
            }
#line 2363 "decaf.tab.c"
    break;

  case 68:
#line 870 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),(yyvsp[-2].expr_val),(yyvsp[0].expr_val),&(yyval.expr_val),Q_DIV);
                }
            }
#line 2376 "decaf.tab.c"
    break;

  case 69:
#line 880 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations arithmétiques entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_arith_to_expr(code_inter,next_quad,current_ctx,&(num_temp),(yyvsp[-2].expr_val),(yyvsp[0].expr_val),&(yyval.expr_val),Q_RES);
                }
            }
#line 2389 "decaf.tab.c"
    break;

  case 70:
#line 890 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-2].expr_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_GREAT);
                }
            }
#line 2402 "decaf.tab.c"
    break;

  case 71:
#line 900 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-2].expr_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_GREAT_EQ);
                }
            }
#line 2415 "decaf.tab.c"
    break;

  case 72:
#line 910 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-2].expr_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_LESS);
                }
            }
#line 2428 "decaf.tab.c"
    break;

  case 73:
#line 920 "decaf.y"
            {
                if( (yyvsp[-2].expr_val).type!=T_INT || (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("Opérations de comparaison arithmétique entre entiers seulement");
                    YYABORT;
                } else {
                    write_op_log_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-2].expr_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_LESS_EQ);
                }
            }
#line 2441 "decaf.tab.c"
    break;

  case 74:
#line 931 "decaf.y"
            {
                if( (yyvsp[-3].expr_val).type!=(yyvsp[0].expr_val).type ){
                    ERROR("Comparaison d'égalité seulement entre mêmes types");
                    YYABORT;
                } else {
                    if( (yyvsp[-3].expr_val).type==T_INT ){
                        write_op_eq_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_EQ);                 
                    }
                    if( (yyvsp[-3].expr_val).type==T_BOOL ){
                        write_op_eq_bool_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[-1].int_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_EQ);
                    }
                }
            }
#line 2459 "decaf.tab.c"
    break;

  case 75:
#line 947 "decaf.y"
            {
                if( (yyvsp[-3].expr_val).type!=(yyvsp[0].expr_val).type ){
                    ERROR("Comparaison d'égalité seulement entre mêmes types");
                    YYABORT;
                } else {
                    if( (yyvsp[-3].expr_val).type==T_INT ){
                        write_op_eq_int_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_NOT_EQ);                      
                    }
                    if( (yyvsp[-3].expr_val).type==T_BOOL ){
                        write_op_eq_bool_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[-1].int_val), (yyvsp[0].expr_val), &(yyval.expr_val), Q_NOT_EQ);                       
                    }
                }
            }
#line 2477 "decaf.tab.c"
    break;

  case 76:
#line 962 "decaf.y"
            {
                if( (yyvsp[-3].expr_val).type!=T_BOOL 
                 || (yyvsp[0].expr_val).type!=T_BOOL )
                {
                    ERROR("Opération OR entre booléens seulement");
                    YYABORT;
                } else {
                    write_or_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[-1].int_val), (yyvsp[0].expr_val), &(yyval.expr_val));
                }                   
            }
#line 2492 "decaf.tab.c"
    break;

  case 77:
#line 974 "decaf.y"
            {
                if( (yyvsp[-3].expr_val).type!=T_BOOL 
                    || (yyvsp[0].expr_val).type!=T_BOOL )
                {
                    ERROR("Opération AND entre booléens seulement");
                    YYABORT;
                } else {
                    write_and_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[-3].expr_val), (yyvsp[-1].int_val), (yyvsp[0].expr_val), &(yyval.expr_val));
                }                       
            }
#line 2507 "decaf.tab.c"
    break;

  case 78:
#line 987 "decaf.y"
            {
                if( (yyvsp[0].expr_val).type!=T_INT ){
                    ERROR("L'opération unaire - ne s'applique qu'aux entiers");
                    YYABORT;
                } else {
                    write_neg_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[0].expr_val), &(yyval.expr_val));
                }                
            }
#line 2520 "decaf.tab.c"
    break;

  case 79:
#line 997 "decaf.y"
            {
                if( (yyvsp[0].expr_val).type!=T_BOOL ){
                    ERROR("L'opérateur ! ne s'applique qu'aux booléens");
                    YYABORT;
                } else {
                    write_not_to_expr(code_inter, next_quad, current_ctx, &num_temp, (yyvsp[0].expr_val), &(yyval.expr_val));
                }
            }
#line 2533 "decaf.tab.c"
    break;

  case 80:
#line 1006 "decaf.y"
            {
                (yyval.expr_val) = (yyvsp[-1].expr_val);
            }
#line 2541 "decaf.tab.c"
    break;

  case 81:
#line 1013 "decaf.y"
            {   
                (yyval.int_val) = (*next_quad); 
            }
#line 2549 "decaf.tab.c"
    break;

  case 82:
#line 1023 "decaf.y"
            {
                (yyval.expr_val) = (yyvsp[0].expr_val);
            }
#line 2557 "decaf.tab.c"
    break;

  case 83:
#line 1028 "decaf.y"
            {
                (yyval.expr_val) = (yyvsp[0].expr_val);
            }
#line 2565 "decaf.tab.c"
    break;

  case 84:
#line 1032 "decaf.y"
            {
                (yyval.expr_val).type = T_INT;
                new_qo_vide(&((yyval.expr_val).dplc));
                new_qo_cst((yyvsp[0].int_val),&((yyval.expr_val).result.qo));                
            }
#line 2575 "decaf.tab.c"
    break;

  case 85:
#line 1038 "decaf.y"
            {
                (yyval.expr_val).type = T_STRING;
                symbole* str = newname_string((yyvsp[0].str_val),TAB_SYMBOLES,&num_temp);
                new_qo_name(str->name,&((yyval.expr_val).result.qo));                 
            }
#line 2585 "decaf.tab.c"
    break;

  case 86:
#line 1047 "decaf.y"
            {
                (yyval.expr_val).type = T_INT;
                if(-2147483648>(yyvsp[0].int_val) || (yyvsp[0].int_val)>2147483648){
                    ERROR("Décimal hors limites");
                    YYABORT;
                }
                new_qo_vide(&((yyval.expr_val).dplc));
                new_qo_cst((yyvsp[0].int_val),&((yyval.expr_val).result.qo));
            }
#line 2599 "decaf.tab.c"
    break;

  case 87:
#line 1057 "decaf.y"
            {
                (yyval.expr_val).type = T_INT;
                printf("%li",(yyvsp[0].int_val));
                if(-2147483648>(yyvsp[0].int_val) || (yyvsp[0].int_val)>2147483648){
                    ERROR("Décimal hors limites");
                    YYABORT;
                }
                new_qo_vide(&((yyval.expr_val).dplc));
                new_qo_cst((yyvsp[0].int_val),&((yyval.expr_val).result.qo));
            }
#line 2614 "decaf.tab.c"
    break;

  case 88:
#line 1071 "decaf.y"
            {
                (yyval.expr_val).type = T_BOOL;
                new_qo_vide(&((yyval.expr_val).dplc));
                new_qo_cst(0,&((yyval.expr_val).result.qo));
            }
#line 2624 "decaf.tab.c"
    break;

  case 89:
#line 1077 "decaf.y"
            {
                (yyval.expr_val).type = T_BOOL;
                new_qo_vide(&((yyval.expr_val).dplc));
                new_qo_cst(1,&((yyval.expr_val).result.qo));
            }
#line 2634 "decaf.tab.c"
    break;


#line 2638 "decaf.tab.c"

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
      yyerror (tab_symbole, code_inter, next_quad, YY_("syntax error"));
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
        yyerror (tab_symbole, code_inter, next_quad, yymsgp);
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
                      yytoken, &yylval, tab_symbole, code_inter, next_quad);
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
                  yystos[yystate], yyvsp, tab_symbole, code_inter, next_quad);
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
  yyerror (tab_symbole, code_inter, next_quad, YY_("memory exhausted"));
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
                  yytoken, &yylval, tab_symbole, code_inter, next_quad);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, tab_symbole, code_inter, next_quad);
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
#line 1085 "decaf.y"


void yyerror (void** tab_symbole, void** code_inter, int* next_quad, const char* msg){
    fprintf(stderr,"%s\n",msg);
}

void new_qo_cst(int cst, quad_op* res){
    res->qo_type = QO_CST;
    res->qo_valeur.cst = cst;
}
void new_qo_name(char* name, quad_op* res){
    res->qo_type = QO_NAME;
    res->qo_valeur.name = name;
}
void new_qo_vide(quad_op* res){
    res->qo_type = QO_VIDE;
    res->qo_valeur.cst = -1;
}
