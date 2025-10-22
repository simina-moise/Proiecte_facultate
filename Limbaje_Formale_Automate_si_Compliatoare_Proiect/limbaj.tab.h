/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LIMBAJ_TAB_H_INCLUDED
# define YY_YY_LIMBAJ_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BGIN = 258,                    /* BGIN  */
    END = 259,                     /* END  */
    ASSIGN = 260,                  /* ASSIGN  */
    NR = 261,                      /* NR  */
    ID = 262,                      /* ID  */
    ID_CLASS = 263,                /* ID_CLASS  */
    TYPE = 264,                    /* TYPE  */
    BOOL = 265,                    /* BOOL  */
    CHAR = 266,                    /* CHAR  */
    INT = 267,                     /* INT  */
    FLOAT = 268,                   /* FLOAT  */
    STRING = 269,                  /* STRING  */
    CONST = 270,                   /* CONST  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    FOR = 273,                     /* FOR  */
    DO = 274,                      /* DO  */
    IF = 275,                      /* IF  */
    COMPARE = 276,                 /* COMPARE  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    NOT = 279,                     /* NOT  */
    CLASS = 280,                   /* CLASS  */
    CLASS_SECTION = 281,           /* CLASS_SECTION  */
    VAR_SECT = 282,                /* VAR_SECT  */
    FUN_SECT = 283,                /* FUN_SECT  */
    INIT_SECT = 284,               /* INIT_SECT  */
    GLOBALVAR_SECTION = 285,       /* GLOBALVAR_SECTION  */
    GLOBALFUN_SECTION = 286,       /* GLOBALFUN_SECTION  */
    PRINT = 287,                   /* PRINT  */
    TYPEOF = 288                   /* TYPEOF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "limbaj.y"

     char* stringVal;
     bool boolVal;
     char charVal;
     int intVal;
     float floatVal;
     struct array* arrayVal;
     class AST_value* astVal;

#line 107 "limbaj.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LIMBAJ_TAB_H_INCLUDED  */
