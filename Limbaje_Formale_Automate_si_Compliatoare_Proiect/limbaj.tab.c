/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "limbaj.y"

#include <iostream>
#include <vector>
#include "IdList.h"
#include "AST.h"
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

class IdList* globalIds = new IdList(nullptr, GLOBAL, "global");
class IdList* ids = globalIds;
class ClassList* clList = new ClassList();

string currentFunctionName; // We are in a function block if this has a value
int p_index = 0;
bool isParameter; // Variables that are declared are considered parameters in a function block
string currentType;

struct array {
    int size;
    char *name; 
};


#line 98 "limbaj.tab.c"

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

#include "limbaj.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BGIN = 3,                       /* BGIN  */
  YYSYMBOL_END = 4,                        /* END  */
  YYSYMBOL_ASSIGN = 5,                     /* ASSIGN  */
  YYSYMBOL_NR = 6,                         /* NR  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_ID_CLASS = 8,                   /* ID_CLASS  */
  YYSYMBOL_TYPE = 9,                       /* TYPE  */
  YYSYMBOL_BOOL = 10,                      /* BOOL  */
  YYSYMBOL_CHAR = 11,                      /* CHAR  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_STRING = 14,                    /* STRING  */
  YYSYMBOL_CONST = 15,                     /* CONST  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_FOR = 18,                       /* FOR  */
  YYSYMBOL_DO = 19,                        /* DO  */
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_COMPARE = 21,                   /* COMPARE  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_CLASS = 25,                     /* CLASS  */
  YYSYMBOL_CLASS_SECTION = 26,             /* CLASS_SECTION  */
  YYSYMBOL_VAR_SECT = 27,                  /* VAR_SECT  */
  YYSYMBOL_FUN_SECT = 28,                  /* FUN_SECT  */
  YYSYMBOL_INIT_SECT = 29,                 /* INIT_SECT  */
  YYSYMBOL_GLOBALVAR_SECTION = 30,         /* GLOBALVAR_SECTION  */
  YYSYMBOL_GLOBALFUN_SECTION = 31,         /* GLOBALFUN_SECTION  */
  YYSYMBOL_PRINT = 32,                     /* PRINT  */
  YYSYMBOL_TYPEOF = 33,                    /* TYPEOF  */
  YYSYMBOL_34_ = 34,                       /* '+'  */
  YYSYMBOL_35_ = 35,                       /* '-'  */
  YYSYMBOL_36_ = 36,                       /* '*'  */
  YYSYMBOL_37_ = 37,                       /* '/'  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
  YYSYMBOL_40_ = 40,                       /* '('  */
  YYSYMBOL_41_ = 41,                       /* ')'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* ';'  */
  YYSYMBOL_44_ = 44,                       /* '['  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_46_ = 46,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_progr = 48,                     /* progr  */
  YYSYMBOL_classSect = 49,                 /* classSect  */
  YYSYMBOL_classDecl = 50,                 /* classDecl  */
  YYSYMBOL_51_1 = 51,                      /* $@1  */
  YYSYMBOL_52_2 = 52,                      /* $@2  */
  YYSYMBOL_block_class = 53,               /* block_class  */
  YYSYMBOL_varSect = 54,                   /* varSect  */
  YYSYMBOL_funSect = 55,                   /* funSect  */
  YYSYMBOL_fun_decl = 56,                  /* fun_decl  */
  YYSYMBOL_57_3 = 57,                      /* $@3  */
  YYSYMBOL_58_4 = 58,                      /* $@4  */
  YYSYMBOL_59_5 = 59,                      /* $@5  */
  YYSYMBOL_60_6 = 60,                      /* $@6  */
  YYSYMBOL_globalvarSect = 61,             /* globalvarSect  */
  YYSYMBOL_globalfunSect = 62,             /* globalfunSect  */
  YYSYMBOL_declaration_function = 63,      /* declaration_function  */
  YYSYMBOL_initSect = 64,                  /* initSect  */
  YYSYMBOL_init = 65,                      /* init  */
  YYSYMBOL_declarations = 66,              /* declarations  */
  YYSYMBOL_decl = 67,                      /* decl  */
  YYSYMBOL_block = 68,                     /* block  */
  YYSYMBOL_main_block = 69,                /* main_block  */
  YYSYMBOL_block_list = 70,                /* block_list  */
  YYSYMBOL_typeof_statement = 71,          /* typeof_statement  */
  YYSYMBOL_eval_statement = 72,            /* eval_statement  */
  YYSYMBOL_ev_bl_expr = 73,                /* ev_bl_expr  */
  YYSYMBOL_ev_bl_expr_rules = 74,          /* ev_bl_expr_rules  */
  YYSYMBOL_ev_expr = 75,                   /* ev_expr  */
  YYSYMBOL_ev_id = 76,                     /* ev_id  */
  YYSYMBOL_list = 77,                      /* list  */
  YYSYMBOL_statement = 78,                 /* statement  */
  YYSYMBOL_function_call = 79,             /* function_call  */
  YYSYMBOL_80_7 = 80,                      /* $@7  */
  YYSYMBOL_control_statement = 81,         /* control_statement  */
  YYSYMBOL_if_statement = 82,              /* if_statement  */
  YYSYMBOL_else_statement = 83,            /* else_statement  */
  YYSYMBOL_while_statement = 84,           /* while_statement  */
  YYSYMBOL_for_statement = 85,             /* for_statement  */
  YYSYMBOL_for_assignment = 86,            /* for_assignment  */
  YYSYMBOL_boolean_expr = 87,              /* boolean_expr  */
  YYSYMBOL_boolean_exprRules = 88,         /* boolean_exprRules  */
  YYSYMBOL_expression = 89,                /* expression  */
  YYSYMBOL_identifier_plus = 90,           /* identifier_plus  */
  YYSYMBOL_identifier_minus = 91,          /* identifier_minus  */
  YYSYMBOL_identifier_div = 92,            /* identifier_div  */
  YYSYMBOL_identifier_mul = 93,            /* identifier_mul  */
  YYSYMBOL_identifier = 94,                /* identifier  */
  YYSYMBOL_call_list = 95                  /* call_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int16 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   361

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  279

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,     2,     2,     2,     2,     2,
      40,    41,    36,    34,    42,    35,     2,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    74,    74,    77,    78,    81,    81,    89,    89,    99,
     101,   102,   104,   105,   108,   112,   108,   119,   123,   119,
     132,   133,   138,   139,   142,   143,   144,   147,   148,   151,
     152,   155,   156,   160,   172,   182,   190,   198,   206,   214,
     222,   234,   243,   260,   263,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   278,   279,   282,   283,   286,
     287,   288,   289,   295,   298,   299,   300,   301,   302,   305,
     306,   307,   308,   309,   310,   311,   315,   316,   317,   318,
     319,   320,   323,   334,   339,   341,   341,   366,   367,   368,
     370,   372,   373,   375,   378,   380,   382,   383,   384,   385,
     386,   387,   390,   392,   393,   394,   395,   396,   398,   398,
     398,   398,   399,   399,   399,   399,   400,   400,   400,   400,
     401,   401,   401,   401,   403,   404,   405,   406,   407,   408,
     410,   423,   424
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BGIN", "END",
  "ASSIGN", "NR", "ID", "ID_CLASS", "TYPE", "BOOL", "CHAR", "INT", "FLOAT",
  "STRING", "CONST", "ELSE", "WHILE", "FOR", "DO", "IF", "COMPARE", "AND",
  "OR", "NOT", "CLASS", "CLASS_SECTION", "VAR_SECT", "FUN_SECT",
  "INIT_SECT", "GLOBALVAR_SECTION", "GLOBALFUN_SECTION", "PRINT", "TYPEOF",
  "'+'", "'-'", "'*'", "'/'", "'{'", "'}'", "'('", "')'", "','", "';'",
  "'['", "']'", "'!'", "$accept", "progr", "classSect", "classDecl", "$@1",
  "$@2", "block_class", "varSect", "funSect", "fun_decl", "$@3", "$@4",
  "$@5", "$@6", "globalvarSect", "globalfunSect", "declaration_function",
  "initSect", "init", "declarations", "decl", "block", "main_block",
  "block_list", "typeof_statement", "eval_statement", "ev_bl_expr",
  "ev_bl_expr_rules", "ev_expr", "ev_id", "list", "statement",
  "function_call", "$@7", "control_statement", "if_statement",
  "else_statement", "while_statement", "for_statement", "for_assignment",
  "boolean_expr", "boolean_exprRules", "expression", "identifier_plus",
  "identifier_minus", "identifier_div", "identifier_mul", "identifier",
  "call_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-189)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-130)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -17,   -12,    14,   -14,    16,    -6,  -189,   209,    31,  -189,
      30,    61,    69,    77,  -189,    45,    86,    95,    66,  -189,
    -189,     6,   103,   209,   111,    96,   131,  -189,   109,   114,
     218,   155,   148,  -189,  -189,   161,     5,   132,   140,   151,
     156,   160,   138,    99,   159,   163,   164,  -189,   170,  -189,
    -189,  -189,   209,   165,   187,   109,   183,  -189,  -189,  -189,
    -189,  -189,   225,  -189,  -189,   189,   226,   202,  -189,   218,
     239,   204,    17,   246,    17,    29,    29,  -189,  -189,   211,
     237,   240,   242,   244,  -189,  -189,  -189,  -189,  -189,  -189,
      86,   250,   247,   218,   218,   218,   218,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,   209,   248,   225,   249,   218,   183,
    -189,  -189,  -189,  -189,  -189,    67,   251,  -189,     3,  -189,
     260,  -189,   277,   252,    12,   255,    44,  -189,    88,    74,
     141,  -189,  -189,  -189,  -189,  -189,    96,   282,  -189,  -189,
     232,    54,   253,  -189,   256,   254,   209,   279,   185,   257,
     150,   107,   153,   162,    89,   258,   264,   263,   265,    17,
      17,    17,   266,    47,   290,   267,   268,    29,    29,    29,
    -189,   218,  -189,  -189,  -189,   269,  -189,  -189,   209,   262,
      47,   218,  -189,  -189,   143,   234,   236,   243,    98,   284,
    -189,   194,   245,  -189,   270,   194,   194,   104,   158,   285,
    -189,   225,   271,   272,  -189,  -189,  -189,  -189,   273,  -189,
    -189,  -189,   274,   275,  -189,  -189,  -189,   276,   278,  -189,
    -189,  -189,   280,   281,  -189,  -189,  -189,   283,  -189,   286,
     287,   194,   288,   289,   229,   235,   238,   241,   304,   291,
     294,  -189,   292,   194,   296,  -189,  -189,  -189,  -189,  -189,
    -189,   293,   295,   297,  -189,  -189,   299,  -189,   302,  -189,
     298,   194,  -189,  -189,  -189,   311,   301,  -189,  -189,   303,
     300,   194,  -189,   318,   305,   307,  -189,   312,  -189
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    21,     0,     4,     1,     0,    23,     7,
       0,     0,     0,     0,    20,     0,     0,     0,     0,     5,
      41,    34,     0,    31,     0,    22,     0,     2,    10,     0,
       0,     0,     0,    32,    14,     0,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    84,     0,    87,
      88,    89,     0,     0,    12,    10,    69,    72,    71,    70,
      74,    73,    42,    64,    75,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    44,     0,
       0,     0,     0,     0,    51,    49,    45,    47,    11,     8,
       0,    27,     0,     0,     0,     0,     0,    33,    35,    40,
      39,    36,    37,    38,    24,     0,    82,     0,   132,   124,
      97,   126,   125,   128,   127,     0,     0,   129,     0,   100,
       0,   103,     0,     0,     0,     0,     0,    61,     0,     0,
       0,    53,    52,    50,    46,    48,    13,    29,     9,     6,
      65,    66,    68,    67,     0,    25,    24,     0,   131,     0,
      85,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,    58,    55,    56,     0,    28,    15,    24,     0,
       0,   132,    86,    96,     0,     0,     0,     0,     0,    98,
      99,     0,     0,   102,     0,     0,     0,     0,     0,    59,
      60,    63,     0,     0,    26,    18,    83,   130,    85,   109,
     110,   111,     0,    85,   113,   114,   115,     0,    85,   117,
     118,   119,     0,    85,   121,   122,   123,     0,   101,     0,
       0,    43,     0,     0,    85,   109,   110,   111,     0,     0,
       0,    62,     0,     0,     0,   104,   105,   106,   107,    81,
      93,     0,     0,     0,    76,    78,     0,    94,    91,    30,
       0,     0,    80,    77,    79,     0,     0,    90,    16,     0,
       0,     0,    19,     0,     0,     0,    92,     0,    95
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,  -189,  -189,  -189,  -189,   306,  -189,  -189,   259,
    -189,  -189,  -189,  -189,  -189,  -189,  -114,  -189,  -189,   -19,
      -5,  -188,  -189,  -189,   308,   309,   -75,  -189,   -24,  -189,
    -189,   -23,   -26,  -189,   -21,  -189,  -189,  -189,  -189,  -189,
     -59,  -189,   -98,   144,   142,   167,   168,  -189,   166
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     5,    29,    18,    53,    54,    91,    25,
      67,   203,   105,   244,     8,    17,   144,   138,   176,    14,
     229,   230,    27,    43,    44,    45,   126,   127,   198,    63,
     231,   232,    64,    71,   233,    49,   267,    50,    51,   123,
     118,   119,   120,   155,   156,   157,   158,   121,   149
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,   129,    15,    46,    33,    48,    62,   239,   240,     1,
      69,    30,    20,     4,     6,   124,     7,    47,    15,    10,
      82,    42,    83,     9,   109,   160,   161,   110,   111,   112,
     113,   114,   179,    88,   160,   161,    56,    19,    79,    57,
      58,    59,    60,    61,   162,   106,   117,    15,   117,    70,
      31,   128,   130,   166,   109,   260,   154,   115,   111,   112,
     113,   114,    16,   116,   204,   193,   168,   169,    20,   140,
     141,   142,   143,   269,   150,   125,    21,   110,   111,   151,
     152,   114,   206,   274,   148,   170,    22,   192,    23,   153,
      95,    96,   197,   199,   200,    24,   168,   169,    26,   145,
     188,   189,   190,    78,    28,    35,    36,   115,    12,   171,
      32,   160,   161,   116,    13,   173,    37,    38,    34,    39,
     160,   161,    93,    94,    95,    96,   168,   169,  -125,   172,
     183,    40,    41,   117,   117,   117,    52,   117,    36,   228,
      12,   145,  -113,  -121,  -117,   241,    13,   201,    37,    38,
     208,    39,    55,    66,   117,   209,   210,   148,   211,   216,
     221,   226,   171,    40,    41,    47,   237,    65,    68,    47,
      47,  -124,    72,   145,  -128,    93,    94,    95,    96,   171,
      73,    77,   174,  -129,  -108,  -112,  -120,  -116,  -114,  -122,
    -118,    74,    93,    94,    95,    96,    75,  -115,  -123,  -119,
      76,    36,    84,    12,    89,    47,    85,    86,   252,    13,
     253,    37,    38,    87,    39,    90,    11,    47,    12,    93,
      94,    95,    96,   -85,    13,    56,   251,   181,    57,    58,
      59,    60,    61,    98,    97,    47,    99,   100,   101,   102,
     103,   213,   104,   218,   108,    47,   214,   215,   219,   220,
     223,   107,   234,   122,   131,   224,   225,   235,   236,    93,
      94,    95,    96,  -108,  -112,  -120,  -116,    94,    95,    96,
    -113,  -121,  -117,  -114,  -122,  -118,  -115,  -123,  -119,   137,
     132,   163,   164,   133,   180,   134,   139,   135,   146,   175,
      96,   159,   184,   165,   147,   167,   178,   177,   182,   185,
     186,   187,   194,   205,   191,   195,   196,   161,   169,   202,
     243,   256,   242,   238,  -108,   245,  -112,   246,   266,  -116,
     265,   247,  -120,   270,   248,   275,   250,   217,   212,   249,
     257,   254,   255,   258,   261,   259,   262,   268,   263,   271,
     264,   277,   272,   273,   276,     0,   278,   207,     0,   136,
       0,    80,    81,   222,     0,   227,     0,     0,     0,     0,
       0,    92
};

static const yytype_int16 yycheck[] =
{
      26,    76,     7,    26,    23,    26,    30,   195,   196,    26,
       5,     5,     7,    25,     0,    74,    30,    43,    23,    25,
      43,    26,    43,     7,     7,    22,    23,    10,    11,    12,
      13,    14,   146,    52,    22,    23,     7,     7,    43,    10,
      11,    12,    13,    14,    41,    69,    72,    52,    74,    44,
      44,    75,    76,    41,     7,   243,   115,    40,    11,    12,
      13,    14,    31,    46,   178,   163,    22,    23,     7,    93,
      94,    95,    96,   261,     7,    46,     7,    10,    11,    12,
      13,    14,   180,   271,   108,    41,     9,    40,    43,   115,
      36,    37,   167,   168,   169,     9,    22,    23,     3,   104,
     159,   160,   161,     4,    38,     9,     7,    40,     9,    21,
       7,    22,    23,    46,    15,    41,    17,    18,     7,    20,
      22,    23,    34,    35,    36,    37,    22,    23,    21,    41,
      41,    32,    33,   159,   160,   161,    27,   163,     7,    41,
       9,   146,    35,    36,    37,    41,    15,   171,    17,    18,
       7,    20,    38,     5,   180,    12,    13,   181,   184,   185,
     186,   187,    21,    32,    33,   191,   192,    12,     7,   195,
     196,    21,    40,   178,    21,    34,    35,    36,    37,    21,
      40,    43,    41,    21,    34,    35,    36,    37,    35,    36,
      37,    40,    34,    35,    36,    37,    40,    35,    36,    37,
      40,     7,    43,     9,    39,   231,    43,    43,   231,    15,
     231,    17,    18,    43,    20,    28,     7,   243,     9,    34,
      35,    36,    37,    40,    15,     7,   231,    42,    10,    11,
      12,    13,    14,     7,    45,   261,    10,    11,    12,    13,
      14,     7,    40,     7,    40,   271,    12,    13,    12,    13,
       7,    12,     7,     7,    43,    12,    13,    12,    13,    34,
      35,    36,    37,    34,    35,    36,    37,    35,    36,    37,
      35,    36,    37,    35,    36,    37,    35,    36,    37,    29,
      43,    21,     5,    43,     5,    43,    39,    43,    40,     7,
      37,    40,    34,    41,    45,    40,    42,    41,    41,    35,
      37,    36,    12,    41,    38,    38,    38,    23,    23,    40,
      38,     7,    41,    43,    41,    41,    41,    41,    16,    41,
      21,    41,    41,    12,    41,     7,    39,   185,   184,    43,
      39,    43,    43,    39,    38,    43,    43,    39,    43,    38,
      43,    34,    39,    43,    39,    -1,    34,   181,    -1,    90,
      -1,    43,    43,   186,    -1,   187,    -1,    -1,    -1,    -1,
      -1,    55
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    48,    49,    25,    50,     0,    30,    61,     7,
      25,     7,     9,    15,    66,    67,    31,    62,    52,     7,
       7,     7,     9,    43,     9,    56,     3,    69,    38,    51,
       5,    44,     7,    66,     7,     9,     7,    17,    18,    20,
      32,    33,    67,    70,    71,    72,    78,    79,    81,    82,
      84,    85,    27,    53,    54,    38,     7,    10,    11,    12,
      13,    14,    75,    76,    79,    12,     5,    57,     7,     5,
      44,    80,    40,    40,    40,    40,    40,    43,     4,    67,
      71,    72,    78,    81,    43,    43,    43,    43,    66,    39,
      28,    55,    53,    34,    35,    36,    37,    45,     7,    10,
      11,    12,    13,    14,    40,    59,    75,    12,    40,     7,
      10,    11,    12,    13,    14,    40,    46,    79,    87,    88,
      89,    94,     7,    86,    87,    46,    73,    74,    75,    73,
      75,    43,    43,    43,    43,    43,    56,    29,    64,    39,
      75,    75,    75,    75,    63,    67,    40,    45,    75,    95,
       7,    12,    13,    79,    87,    90,    91,    92,    93,    40,
      22,    23,    41,    21,     5,    41,    41,    40,    22,    23,
      41,    21,    41,    41,    41,     7,    65,    41,    42,    63,
       5,    42,    41,    41,    34,    35,    37,    36,    87,    87,
      87,    38,    40,    89,    12,    38,    38,    73,    75,    73,
      73,    75,    40,    58,    63,    41,    89,    95,     7,    12,
      13,    79,    90,     7,    12,    13,    79,    91,     7,    12,
      13,    79,    92,     7,    12,    13,    79,    93,    41,    67,
      68,    77,    78,    81,     7,    12,    13,    79,    43,    68,
      68,    41,    41,    38,    60,    41,    41,    41,    41,    43,
      39,    67,    78,    81,    43,    43,     7,    39,    39,    43,
      68,    38,    43,    43,    43,    21,    16,    83,    39,    68,
      12,    38,    39,    43,    68,     7,    39,    34,    34
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    51,    50,    52,    50,    53,
      54,    54,    55,    55,    57,    58,    56,    59,    60,    56,
      61,    61,    62,    62,    63,    63,    63,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    73,    73,    74,    75,    75,    75,    75,    75,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    77,    77,
      77,    77,    78,    78,    78,    80,    79,    81,    81,    81,
      82,    83,    83,    84,    85,    86,    87,    87,    87,    87,
      87,    87,    88,    89,    89,    89,    89,    89,    90,    90,
      90,    90,    91,    91,    91,    91,    92,    92,    92,    92,
      93,    93,    93,    93,    94,    94,    94,    94,    94,    94,
      95,    95,    95
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     0,     2,     0,     7,     0,     6,     3,
       0,     2,     0,     2,     0,     0,    10,     0,     0,    11,
       2,     0,     2,     0,     0,     1,     3,     0,     2,     0,
       4,     2,     3,     5,     2,     5,     5,     5,     5,     5,
       5,     2,     4,     1,     3,     2,     3,     2,     3,     2,
       3,     2,     3,     3,     2,     4,     4,     4,     4,     3,
       3,     1,     4,     3,     1,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     2,     3,
       3,     2,     3,     6,     1,     0,     5,     1,     1,     1,
       8,     0,     4,     7,     7,    11,     3,     1,     3,     3,
       1,     4,     3,     1,     5,     5,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* progr: classSect globalvarSect globalfunSect main_block  */
#line 74 "limbaj.y"
                                                        {printf("The programme is correct!\n");}
#line 1384 "limbaj.tab.c"
    break;

  case 5: /* $@1: %empty  */
#line 81 "limbaj.y"
                                  {
                clList->addClass((yyvsp[0].stringVal)); 
                ids = clList->getClass((yyvsp[0].stringVal))->list; 
                ids->scopeType = CLASS_SCOPE;
                ids->scopeName = (yyvsp[0].stringVal);
            }
#line 1395 "limbaj.tab.c"
    break;

  case 6: /* classDecl: classDecl CLASS ID $@1 '{' block_class '}'  */
#line 86 "limbaj.y"
                                  {
                ids = globalIds;
            }
#line 1403 "limbaj.tab.c"
    break;

  case 7: /* $@2: %empty  */
#line 89 "limbaj.y"
                       {
                clList->addClass((yyvsp[0].stringVal)); 
                ids = clList->getClass((yyvsp[0].stringVal))->list;
                ids->scopeType = CLASS_SCOPE;
                ids->scopeName = (yyvsp[0].stringVal);
            }
#line 1414 "limbaj.tab.c"
    break;

  case 8: /* classDecl: CLASS ID $@2 '{' block_class '}'  */
#line 94 "limbaj.y"
                                  {
                ids = globalIds;
            }
#line 1422 "limbaj.tab.c"
    break;

  case 14: /* $@3: %empty  */
#line 108 "limbaj.y"
                      {
                ids->addFunction((yyvsp[-1].stringVal), (yyvsp[0].stringVal));
                currentFunctionName = ids->getFunction((yyvsp[0].stringVal))->name; 
                isParameter = true;
            }
#line 1432 "limbaj.tab.c"
    break;

  case 15: /* $@4: %empty  */
#line 112 "limbaj.y"
                                           {
                isParameter = false; 
                ids = ids->getFunction(currentFunctionName.c_str())->variables;
            }
#line 1441 "limbaj.tab.c"
    break;

  case 16: /* fun_decl: TYPE ID $@3 '(' declaration_function ')' $@4 '{' block '}'  */
#line 115 "limbaj.y"
                            {
                currentFunctionName = "";
                ids = ids->parent;
            }
#line 1450 "limbaj.tab.c"
    break;

  case 17: /* $@5: %empty  */
#line 119 "limbaj.y"
                               {
                ids->addFunction((yyvsp[-1].stringVal), (yyvsp[0].stringVal));
                currentFunctionName = ids->getFunction((yyvsp[0].stringVal))->name; 
                isParameter = true;
            }
#line 1460 "limbaj.tab.c"
    break;

  case 18: /* $@6: %empty  */
#line 123 "limbaj.y"
                                           {
                isParameter = false; 
                ids = ids->getFunction(currentFunctionName.c_str())->variables;
            }
#line 1469 "limbaj.tab.c"
    break;

  case 19: /* fun_decl: fun_decl TYPE ID $@5 '(' declaration_function ')' $@6 '{' block '}'  */
#line 126 "limbaj.y"
                            {
                currentFunctionName = "";
                ids = ids->parent;
            }
#line 1478 "limbaj.tab.c"
    break;

  case 33: /* decl: TYPE ID '[' INT ']'  */
#line 160 "limbaj.y"
                                 {
                   printf("%s\n", currentFunctionName.c_str());
                   if (isParameter) {
                       ids->getFunction(currentFunctionName.c_str())->addParameter((yyvsp[-4].stringVal), (yyvsp[-3].stringVal), clList);
                       ids->getFunction(currentFunctionName.c_str())->variables->addVar((yyvsp[-4].stringVal), (yyvsp[-3].stringVal), clList);
                   } else if (!ids->existsVar((yyvsp[-3].stringVal))) {
                       struct array* newArray = new struct array;
                       newArray->size = (yyvsp[-1].intVal);
                       newArray->name = strdup((yyvsp[-3].stringVal));
                       ids->addVar((yyvsp[-4].stringVal), (yyvsp[-3].stringVal));
                   }
               }
#line 1495 "limbaj.tab.c"
    break;

  case 34: /* decl: TYPE ID  */
#line 172 "limbaj.y"
                       {
                   if (isParameter) {
                       ids->getFunction(currentFunctionName.c_str())->addParameter((yyvsp[-1].stringVal), (yyvsp[0].stringVal), clList);
                       ids->getFunction(currentFunctionName.c_str())->variables->addVar((yyvsp[-1].stringVal), (yyvsp[0].stringVal), clList);
                   } else if (!ids->existsVar((yyvsp[0].stringVal))) {
                       ids->addVar((yyvsp[-1].stringVal), (yyvsp[0].stringVal));
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[0].stringVal));
                   }
               }
#line 1510 "limbaj.tab.c"
    break;

  case 35: /* decl: CONST TYPE ID ASSIGN ID  */
#line 182 "limbaj.y"
                                       {
                   if (!ids->existsVar((yyvsp[-2].stringVal))) {
                       ids->addVar((yyvsp[-3].stringVal), (yyvsp[-2].stringVal), true);
                       ids->setVarValue((yyvsp[-2].stringVal), (yyvsp[0].stringVal));
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[-2].stringVal));
                   }
               }
#line 1523 "limbaj.tab.c"
    break;

  case 36: /* decl: CONST TYPE ID ASSIGN INT  */
#line 190 "limbaj.y"
                                        {
                   if (!ids->existsVar((yyvsp[-2].stringVal))) {
                       ids->addVar((yyvsp[-3].stringVal), (yyvsp[-2].stringVal), true);
                       ids->setVarValue((yyvsp[-2].stringVal), std::to_string((yyvsp[0].intVal)).c_str());
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[-2].stringVal));
                   }
               }
#line 1536 "limbaj.tab.c"
    break;

  case 37: /* decl: CONST TYPE ID ASSIGN FLOAT  */
#line 198 "limbaj.y"
                                          {
                   if (!ids->existsVar((yyvsp[-2].stringVal))) {
                       ids->addVar((yyvsp[-3].stringVal), (yyvsp[-2].stringVal), true);
                       ids->setVarValue((yyvsp[-2].stringVal), std::to_string((yyvsp[0].floatVal)).c_str());
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[-2].stringVal));
                   }
               }
#line 1549 "limbaj.tab.c"
    break;

  case 38: /* decl: CONST TYPE ID ASSIGN STRING  */
#line 206 "limbaj.y"
                                           {
                   if (!ids->existsVar((yyvsp[-2].stringVal))) {
                       ids->addVar((yyvsp[-3].stringVal), (yyvsp[-2].stringVal), true);
                       ids->setVarValue((yyvsp[-2].stringVal), (yyvsp[0].stringVal));
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[-2].stringVal));
                   }
               }
#line 1562 "limbaj.tab.c"
    break;

  case 39: /* decl: CONST TYPE ID ASSIGN CHAR  */
#line 214 "limbaj.y"
                                         {
                   if (!ids->existsVar((yyvsp[-2].stringVal))) {
                       ids->addVar((yyvsp[-3].stringVal), (yyvsp[-2].stringVal), true);
                       ids->setVarValue((yyvsp[-2].stringVal), std::to_string((yyvsp[0].charVal)).c_str());
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[-2].stringVal));
                   }
               }
#line 1575 "limbaj.tab.c"
    break;

  case 40: /* decl: CONST TYPE ID ASSIGN BOOL  */
#line 222 "limbaj.y"
                                         {
                   if (!ids->existsVar((yyvsp[-2].stringVal))) {
                       ids->addVar((yyvsp[-3].stringVal), (yyvsp[-2].stringVal), true);
                       if ((yyvsp[0].boolVal) == true) {
                           ids->setVarValue((yyvsp[-2].stringVal), "true");
                       } else {
                           ids->setVarValue((yyvsp[-2].stringVal), "false");
                       }
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[-2].stringVal));
                   }
               }
#line 1592 "limbaj.tab.c"
    break;

  case 41: /* decl: ID ID  */
#line 234 "limbaj.y"
                     {
                   if (isParameter) {
                       ids->getFunction(currentFunctionName.c_str())->addParameter((yyvsp[-1].stringVal), (yyvsp[0].stringVal), clList);
                   } else if (!ids->existsVar((yyvsp[0].stringVal)) && clList->existsClass((yyvsp[-1].stringVal))) {
                       ids->addVar((yyvsp[-1].stringVal), (yyvsp[0].stringVal));
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, (yyvsp[0].stringVal));
                   }
               }
#line 1606 "limbaj.tab.c"
    break;

  case 42: /* decl: TYPE ID ASSIGN ev_expr  */
#line 243 "limbaj.y"
                                      {
                   if (!ids->existsVar((yyvsp[-2].stringVal))) {
                       if (strcmp((yyvsp[-3].stringVal), (yyvsp[0].astVal)->get_type().c_str()) != 0) {
                           printf("Error: line [%d] variable %s has different type compared to right side!\n", yylineno, (yyvsp[-2].stringVal));
                           printf("%s %s", (yyvsp[-3].stringVal), (yyvsp[0].astVal)->get_type().c_str());
                       } else {
                           ids->addVar((yyvsp[-3].stringVal), (yyvsp[-2].stringVal));
                           ids->setVarValue((yyvsp[-2].stringVal), (yyvsp[0].astVal)->get_value().c_str());
                       }
                   }
               }
#line 1622 "limbaj.tab.c"
    break;

  case 55: /* typeof_statement: TYPEOF '(' ev_bl_expr ')'  */
#line 278 "limbaj.y"
                                            { (yyvsp[-1].astVal)->print_type(); }
#line 1628 "limbaj.tab.c"
    break;

  case 56: /* typeof_statement: TYPEOF '(' ev_expr ')'  */
#line 279 "limbaj.y"
                                        { (yyvsp[-1].astVal)->print_type(); }
#line 1634 "limbaj.tab.c"
    break;

  case 57: /* eval_statement: PRINT '(' ev_bl_expr ')'  */
#line 282 "limbaj.y"
                                         { (yyval.astVal) = (yyvsp[-1].astVal); (yyval.astVal)->print_value(); }
#line 1640 "limbaj.tab.c"
    break;

  case 58: /* eval_statement: PRINT '(' ev_expr ')'  */
#line 283 "limbaj.y"
                                       { (yyval.astVal) = (yyvsp[-1].astVal); (yyval.astVal)->print_value(); }
#line 1646 "limbaj.tab.c"
    break;

  case 59: /* ev_bl_expr: ev_bl_expr AND ev_bl_expr  */
#line 286 "limbaj.y"
                                         { AST a = AST((yyvsp[-2].astVal),"&&",(yyvsp[0].astVal)); (yyval.astVal) = a.evaluate(); }
#line 1652 "limbaj.tab.c"
    break;

  case 60: /* ev_bl_expr: ev_bl_expr OR ev_bl_expr  */
#line 287 "limbaj.y"
                                        { AST a = AST((yyvsp[-2].astVal),"||",(yyvsp[0].astVal)); (yyval.astVal) = a.evaluate(); }
#line 1658 "limbaj.tab.c"
    break;

  case 61: /* ev_bl_expr: ev_bl_expr_rules  */
#line 288 "limbaj.y"
                                { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1664 "limbaj.tab.c"
    break;

  case 62: /* ev_bl_expr: '!' '(' ev_bl_expr ')'  */
#line 289 "limbaj.y"
                                       {
    AST a = AST(nullptr, "!", (yyvsp[-1].astVal)); // Creăm un nod AST pentru negare
    (yyval.astVal) = a.evaluate();            // Evaluăm negarea
}
#line 1673 "limbaj.tab.c"
    break;

  case 63: /* ev_bl_expr_rules: ev_expr COMPARE ev_expr  */
#line 295 "limbaj.y"
                                           { AST a = AST(ast_type::aBOOL,(yyvsp[-2].astVal), (yyvsp[-1].stringVal),(yyvsp[0].astVal)); (yyval.astVal) = a.evaluate(); }
#line 1679 "limbaj.tab.c"
    break;

  case 64: /* ev_expr: ev_id  */
#line 298 "limbaj.y"
                { (yyval.astVal) = (yyvsp[0].astVal); }
#line 1685 "limbaj.tab.c"
    break;

  case 65: /* ev_expr: ev_expr '+' ev_expr  */
#line 299 "limbaj.y"
                                { AST a = AST((yyvsp[-2].astVal),"+",(yyvsp[0].astVal)); (yyval.astVal) = a.evaluate(); }
#line 1691 "limbaj.tab.c"
    break;

  case 66: /* ev_expr: ev_expr '-' ev_expr  */
#line 300 "limbaj.y"
                                { AST a = AST((yyvsp[-2].astVal),"-",(yyvsp[0].astVal)); (yyval.astVal) = a.evaluate(); }
#line 1697 "limbaj.tab.c"
    break;

  case 67: /* ev_expr: ev_expr '/' ev_expr  */
#line 301 "limbaj.y"
                                { AST a = AST((yyvsp[-2].astVal),"/",(yyvsp[0].astVal)); (yyval.astVal) = a.evaluate(); }
#line 1703 "limbaj.tab.c"
    break;

  case 68: /* ev_expr: ev_expr '*' ev_expr  */
#line 302 "limbaj.y"
                                { AST a = AST((yyvsp[-2].astVal),"*",(yyvsp[0].astVal)); (yyval.astVal) = a.evaluate(); }
#line 1709 "limbaj.tab.c"
    break;

  case 69: /* ev_id: ID  */
#line 305 "limbaj.y"
           { (yyval.astVal) = new AST_value(ids->getVar((yyvsp[0].stringVal)).getType_asString().c_str(),ids->getVar((yyvsp[0].stringVal)).getValue().c_str()); }
#line 1715 "limbaj.tab.c"
    break;

  case 70: /* ev_id: INT  */
#line 306 "limbaj.y"
             { (yyval.astVal) = new AST_value("int",std::to_string((yyvsp[0].intVal)).c_str()); }
#line 1721 "limbaj.tab.c"
    break;

  case 71: /* ev_id: CHAR  */
#line 307 "limbaj.y"
              { (yyval.astVal) = new AST_value("char",std::to_string((yyvsp[0].charVal)).c_str()); }
#line 1727 "limbaj.tab.c"
    break;

  case 72: /* ev_id: BOOL  */
#line 308 "limbaj.y"
              { if((yyvsp[0].boolVal) == true) { (yyval.astVal) = new AST_value("bool","true"); } else { (yyval.astVal) = new AST_value("bool","false"); }}
#line 1733 "limbaj.tab.c"
    break;

  case 73: /* ev_id: STRING  */
#line 309 "limbaj.y"
                { (yyval.astVal) = new AST_value("string",(yyvsp[0].stringVal)); }
#line 1739 "limbaj.tab.c"
    break;

  case 74: /* ev_id: FLOAT  */
#line 310 "limbaj.y"
               { (yyval.astVal) = new AST_value("float",std::to_string((yyvsp[0].floatVal)).c_str()); }
#line 1745 "limbaj.tab.c"
    break;

  case 75: /* ev_id: function_call  */
#line 311 "limbaj.y"
                       { /* Logic for function calls */ }
#line 1751 "limbaj.tab.c"
    break;

  case 82: /* statement: ID ASSIGN ev_expr  */
#line 323 "limbaj.y"
                             {
          if (!ids->existsVar((yyvsp[-2].stringVal))) {
               printf("Error: line [%d] variable %s is not defined\n", yylineno, (yyvsp[-2].stringVal));
          } else {
               if(ids->getVar((yyvsp[-2].stringVal)).getType_asString() != (yyvsp[0].astVal)->get_type()) {
                    printf("Error: line [%d] variables %s type doesnt match with right part of assignment \n", yylineno, (yyvsp[-2].stringVal));
               } else {
                    //printf("Correct: line [%d] %s %s", yylineno, ids->getVar($1).getType_asString().c_str(), $3->get_type().c_str());
               }
          }
          }
#line 1767 "limbaj.tab.c"
    break;

  case 83: /* statement: ID '[' INT ']' ASSIGN expression  */
#line 334 "limbaj.y"
                                             {
          if (!ids->existsVar((yyvsp[-5].stringVal))) {
               printf("Error: line [%d] variable %s is not defined", yylineno, (yyvsp[-5].stringVal));
          }
          }
#line 1777 "limbaj.tab.c"
    break;

  case 85: /* $@7: %empty  */
#line 341 "limbaj.y"
                  {
    // Verifică dacă funcția există
    if (ids->existsVar((yyvsp[0].stringVal))) {
        currentFunctionName = (yyvsp[0].stringVal); 
        p_index = ids->getFunction(currentFunctionName.c_str())->paramters.size() - 1; // Inițializăm p_index la ultimul index
    } else {
        printf("Error: line [%d] function %s is not defined\n", yylineno, (yyvsp[0].stringVal));
    }
}
#line 1791 "limbaj.tab.c"
    break;

  case 86: /* function_call: ID $@7 '(' call_list ')'  */
#line 349 "limbaj.y"
                    {
    // Verificăm dacă p_index este valid
    auto functionSignature = ids->getFunction(currentFunctionName.c_str());
    
    // Verificăm dacă au fost furnizate prea multe argumente
    if (p_index >= functionSignature->paramters.size()) {
        printf("Error: line [%d] too many parameters in function call!\n", yylineno);
    } else if (p_index < 0) {
        printf("Error: line [%d] too few parameters in function call!\n", yylineno);
    }
    
    // Resetăm p_index pentru a verifica argumentele
    p_index = functionSignature->paramters.size() - 1; // Resetăm p_index la numărul de parametrii - 1
}
#line 1810 "limbaj.tab.c"
    break;

  case 130: /* call_list: ev_expr ',' call_list  */
#line 410 "limbaj.y"
                                  {
    auto functionSignature = ids->getFunction(currentFunctionName.c_str());
    
    // Verificăm tipul argumentului
    std::string expectedType = functionSignature->paramters[p_index].getType_asString();
    std::string actualType = (yyvsp[-2].astVal)->get_type();
    
    if (actualType != expectedType) {
        printf("Error: line [%d] variable is not correct type! Expected: %s, but got: %s\n", yylineno, expectedType.c_str(), actualType.c_str());
    }
    
    p_index--; // Decrementăm p_index pentru a verifica următorul argument
}
#line 1828 "limbaj.tab.c"
    break;


#line 1832 "limbaj.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 426 "limbaj.y"

void yyerror(const char * s){
printf("error: %s at line:%d\n",s,yylineno);
}

#include <fcntl.h>
#include <unistd.h>


int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     globalIds->clList = clList;
     yyparse();
     cout << "Variables:" <<endl;
     ids->printVars();

     symb_printable* str = new symb_printable;
     ids->gen_symbol_table(str);

     int fd = open("./sym.txt",O_RDWR | O_CREAT, 0666);
     ftruncate(fd,0);
     ftruncate(fd,str->result.size());
     write(fd,str->result.c_str(),str->result.size());

    
} 
