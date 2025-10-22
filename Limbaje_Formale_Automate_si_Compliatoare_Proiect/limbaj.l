%{
#include <stdio.h>
#include "limbaj.tab.h"
%}
%option noyywrap
%%
"int"|"float"|"char"|"string"|"bool"|"void" {yylval.stringVal = strdup(yytext);return TYPE;}
"const" {return CONST;}

"class_section" {return CLASS_SECTION;}
"class" {yylval.stringVal = strdup(yytext);return CLASS; }
"var_section" {return VAR_SECT;}
"fun_section" {return FUN_SECT;}
"init_section" {return INIT_SECT;}

"globalvar_section" {return GLOBALVAR_SECTION;}
"globalfun_section" {return GLOBALFUN_SECTION;}


"Print" {return PRINT;}
"TypeOf" {return TYPEOF;}
"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
"while" {return WHILE;}
"do" {return DO;}
"<="|">="|"=="|"!="|"<"|">" {return COMPARE;}
"&&" {return AND;} 
"||" {return OR;}
'!' {return NOT;}

"begin_progr" {return BGIN;}
"end_progr" {return END;}

"true"|"false" {
     if(strcmp(yytext,"true") == 0) { yylval.boolVal = true;}
    else { yylval.boolVal = false;}
    return BOOL;
    }
\'[a-zA-Z0-9 _\-=+()\\/?;:'!@#$%^&*]\' {yylval.charVal = yytext[1]; return CHAR;}
([1-9][0-9]*|[0])"."[0-9]* {yylval.floatVal = atof(yytext); return FLOAT;}
[1-9][0-9]*|[0] {yylval.intVal = atoi(yytext); return INT;}
\"[a-zA-Z0-9 _\-=+()\\/?;:'!@#$%^&*]*\" {yylval.stringVal = strndup(yytext + 1, strlen(yytext +1) -1); return STRING;}



[a-zA-Z][a-zA-Z0-9]* {yylval.stringVal = strdup(yytext); return ID;}

"=" {return ASSIGN;}
[0-9]+ {return NR;}
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
