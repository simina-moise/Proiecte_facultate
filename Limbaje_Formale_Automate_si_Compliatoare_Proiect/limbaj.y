%{
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

%}
%union {
     char* stringVal;
     bool boolVal;
     char charVal;
     int intVal;
     float floatVal;
     struct array* arrayVal;
     class AST_value* astVal;
}

%token BGIN END ASSIGN NR 
%token<stringVal> ID ID_CLASS TYPE
%token<boolVal> BOOL
%token<charVal> CHAR
%token<intVal> INT
%token<floatVal> FLOAT
%token<stringVal> STRING
%token<stringVal> CONST 
%token ELSE WHILE FOR DO IF
%token<stringVal> COMPARE
%token AND OR NOT

%token<stringVal> CLASS
%token CLASS_SECTION
%token VAR_SECT
%token FUN_SECT
%token INIT_SECT
%token GLOBALVAR_SECTION
%token GLOBALFUN_SECTION
%token<stringVal> PRINT
%token<stringVal> TYPEOF

%type<astVal> ev_bl_expr ev_bl_expr_rules ev_expr ev_id eval_statement

%start progr

%left COMPARE
%left AND 
%left OR
%left '+'
%left '-'
%left '*' 
%left '/'
%left IF
%left ELSE

%%
progr: classSect globalvarSect globalfunSect main_block {printf("The programme is correct!\n");}
     ;

classSect   : 
            | CLASS_SECTION classDecl
            ;
            
classDecl   : classDecl CLASS ID  {
                clList->addClass($3); 
                ids = clList->getClass($3)->list; 
                ids->scopeType = CLASS_SCOPE;
                ids->scopeName = $3;
            } '{' block_class '}' {
                ids = globalIds;
            }
            | CLASS ID {
                clList->addClass($2); 
                ids = clList->getClass($2)->list;
                ids->scopeType = CLASS_SCOPE;
                ids->scopeName = $2;
            } '{' block_class '}' {
                ids = globalIds;
            }
            ;

block_class : varSect funSect initSect
            ;
varSect     :
            | VAR_SECT declarations
            ;
funSect     : 
            | FUN_SECT fun_decl
            ;

fun_decl    : TYPE ID {
                ids->addFunction($1, $2);
                currentFunctionName = ids->getFunction($2)->name; 
                isParameter = true;
            } '(' declaration_function ')' {
                isParameter = false; 
                ids = ids->getFunction(currentFunctionName.c_str())->variables;
            } '{' block '}' {
                currentFunctionName = "";
                ids = ids->parent;
            }
            | fun_decl TYPE ID {
                ids->addFunction($2, $3);
                currentFunctionName = ids->getFunction($3)->name; 
                isParameter = true;
            } '(' declaration_function ')' {
                isParameter = false; 
                ids = ids->getFunction(currentFunctionName.c_str())->variables;
            } '{' block '}' {
                currentFunctionName = "";
                ids = ids->parent;
            }
            ;

globalvarSect : GLOBALVAR_SECTION declarations
              |
              ;



globalfunSect : GLOBALFUN_SECTION fun_decl
               |
              ;

declaration_function :  
                     | decl          
	             |  decl ',' declaration_function
	             ;

initSect    :
            | INIT_SECT init
            ;

init        :
            | ID '(' ')' ';'
            ;
            
declarations :  decl ';'          
	      |  decl ';' declarations    
	      ;
	      

decl       : TYPE ID '[' INT ']' {
                   printf("%s\n", currentFunctionName.c_str());
                   if (isParameter) {
                       ids->getFunction(currentFunctionName.c_str())->addParameter($1, $2, clList);
                       ids->getFunction(currentFunctionName.c_str())->variables->addVar($1, $2, clList);
                   } else if (!ids->existsVar($2)) {
                       struct array* newArray = new struct array;
                       newArray->size = $4;
                       newArray->name = strdup($2);
                       ids->addVar($1, $2);
                   }
               }
             | TYPE ID {
                   if (isParameter) {
                       ids->getFunction(currentFunctionName.c_str())->addParameter($1, $2, clList);
                       ids->getFunction(currentFunctionName.c_str())->variables->addVar($1, $2, clList);
                   } else if (!ids->existsVar($2)) {
                       ids->addVar($1, $2);
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $2);
                   }
               }
             | CONST TYPE ID ASSIGN ID {
                   if (!ids->existsVar($3)) {
                       ids->addVar($2, $3, true);
                       ids->setVarValue($3, $5);
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $3);
                   }
               }
             | CONST TYPE ID ASSIGN INT {
                   if (!ids->existsVar($3)) {
                       ids->addVar($2, $3, true);
                       ids->setVarValue($3, std::to_string($5).c_str());
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $3);
                   }
               }
             | CONST TYPE ID ASSIGN FLOAT {
                   if (!ids->existsVar($3)) {
                       ids->addVar($2, $3, true);
                       ids->setVarValue($3, std::to_string($5).c_str());
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $3);
                   }
               }
             | CONST TYPE ID ASSIGN STRING {
                   if (!ids->existsVar($3)) {
                       ids->addVar($2, $3, true);
                       ids->setVarValue($3, $5);
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $3);
                   }
               }
             | CONST TYPE ID ASSIGN CHAR {
                   if (!ids->existsVar($3)) {
                       ids->addVar($2, $3, true);
                       ids->setVarValue($3, std::to_string($5).c_str());
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $3);
                   }
               }
             | CONST TYPE ID ASSIGN BOOL {
                   if (!ids->existsVar($3)) {
                       ids->addVar($2, $3, true);
                       if ($5 == true) {
                           ids->setVarValue($3, "true");
                       } else {
                           ids->setVarValue($3, "false");
                       }
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $3);
                   }
               }
             | ID ID {
                   if (isParameter) {
                       ids->getFunction(currentFunctionName.c_str())->addParameter($1, $2, clList);
                   } else if (!ids->existsVar($2) && clList->existsClass($1)) {
                       ids->addVar($1, $2);
                   } else {
                       printf("Error: line [%d] variable %s is already declared!\n", yylineno, $2);
                   }
               }
             | TYPE ID ASSIGN ev_expr {
                   if (!ids->existsVar($2)) {
                       if (strcmp($1, $4->get_type().c_str()) != 0) {
                           printf("Error: line [%d] variable %s has different type compared to right side!\n", yylineno, $2);
                           printf("%s %s", $1, $4->get_type().c_str());
                       } else {
                           ids->addVar($1, $2);
                           ids->setVarValue($2, $4->get_value().c_str());
                       }
                   }
               }
             ;



      

block :  list   
     ;

main_block: BGIN block_list END  
     ;
     
block_list :  statement ';' 
     | block_list statement ';'
     | control_statement ';'
     | block_list control_statement ';'
     | eval_statement ';'
     | block_list eval_statement ';'
     | typeof_statement ';'
     | block_list typeof_statement ';'
     | block_list decl ';'
     | decl ';'
     ;

typeof_statement: TYPEOF '(' ev_bl_expr ')' { $3->print_type(); }
               | TYPEOF '(' ev_expr ')' { $3->print_type(); }
               ;

eval_statement: PRINT '(' ev_bl_expr ')' { $$ = $3; $$->print_value(); }
               | PRINT '(' ev_expr ')' { $$ = $3; $$->print_value(); }
               ;

ev_bl_expr   : ev_bl_expr AND ev_bl_expr { AST a = AST($1,"&&",$3); $$ = a.evaluate(); }
             | ev_bl_expr OR ev_bl_expr { AST a = AST($1,"||",$3); $$ = a.evaluate(); }
             | ev_bl_expr_rules { $$ = $1; }
             |  '!' '(' ev_bl_expr ')' {
    AST a = AST(nullptr, "!", $3); // Creăm un nod AST pentru negare
    $$ = a.evaluate();            // Evaluăm negarea
}
      ;

ev_bl_expr_rules : ev_expr COMPARE ev_expr { AST a = AST(ast_type::aBOOL,$1, $2,$3); $$ = a.evaluate(); }
                  ;

ev_expr : ev_id { $$ = $1; }
          | ev_expr '+' ev_expr { AST a = AST($1,"+",$3); $$ = a.evaluate(); }
          | ev_expr '-' ev_expr { AST a = AST($1,"-",$3); $$ = a.evaluate(); }
          | ev_expr '/' ev_expr { AST a = AST($1,"/",$3); $$ = a.evaluate(); }
          | ev_expr '*' ev_expr { AST a = AST($1,"*",$3); $$ = a.evaluate(); }
          ;

ev_id : ID { $$ = new AST_value(ids->getVar($1).getType_asString().c_str(),ids->getVar($1).getValue().c_str()); }
       | INT { $$ = new AST_value("int",std::to_string($1).c_str()); }
       | CHAR { $$ = new AST_value("char",std::to_string($1).c_str()); }
       | BOOL { if($1 == true) { $$ = new AST_value("bool","true"); } else { $$ = new AST_value("bool","false"); }}
       | STRING { $$ = new AST_value("string",$1); } 
       | FLOAT { $$ = new AST_value("float",std::to_string($1).c_str()); } 
       | function_call { /* Logic for function calls */ }
       ;


list : statement ';' 
     | list statement ';'
     | control_statement ';'
     | list control_statement ';'
     | list decl ';'
     | decl ';'
     ;

statement: ID ASSIGN ev_expr {
          if (!ids->existsVar($1)) {
               printf("Error: line [%d] variable %s is not defined\n", yylineno, $1);
          } else {
               if(ids->getVar($1).getType_asString() != $3->get_type()) {
                    printf("Error: line [%d] variables %s type doesnt match with right part of assignment \n", yylineno, $1);
               } else {
                    //printf("Correct: line [%d] %s %s", yylineno, ids->getVar($1).getType_asString().c_str(), $3->get_type().c_str());
               }
          }
          }
          | ID '[' INT ']' ASSIGN expression {
          if (!ids->existsVar($1)) {
               printf("Error: line [%d] variable %s is not defined", yylineno, $1);
          }
          }
         | function_call;

function_call: ID {
    // Verifică dacă funcția există
    if (ids->existsVar($1)) {
        currentFunctionName = $1; 
        p_index = ids->getFunction(currentFunctionName.c_str())->paramters.size() - 1; // Inițializăm p_index la ultimul index
    } else {
        printf("Error: line [%d] function %s is not defined\n", yylineno, $1);
    }
} '(' call_list ')' {
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
;


control_statement : if_statement
                  | while_statement
                  | for_statement;

if_statement        : IF '(' boolean_expr ')' '{' block '}' else_statement;

else_statement      :
                    | ELSE '{' block '}';

while_statement     : WHILE '(' boolean_expr ')' '{' block '}';


for_statement       : FOR '(' for_assignment ')' '{' block '}';

for_assignment : ID ASSIGN INT ';' ID COMPARE INT ';' ID '+' '+';

boolean_expr : '(' boolean_expr ')'
             | BOOL
             | boolean_expr AND boolean_expr
             | boolean_expr OR boolean_expr
             | boolean_exprRules
             | '!' '(' boolean_expr ')' ;
             

boolean_exprRules : expression COMPARE expression;

expression : identifier
          | '(' identifier_plus '+' identifier_plus ')' 
          | '(' identifier_minus '-' identifier_minus ')'
          | '(' identifier_div '/' identifier_div ')'
          | '(' identifier_mul '*' identifier_mul ')';

identifier_plus: ID | INT | FLOAT | function_call;
identifier_minus: ID | INT | FLOAT | function_call;
identifier_div: ID | INT | FLOAT | function_call;
identifier_mul: ID | INT | FLOAT | function_call;

identifier : ID 
           | INT 
           | CHAR 
           | STRING 
           | FLOAT 
           | function_call;

call_list : ev_expr ',' call_list {
    auto functionSignature = ids->getFunction(currentFunctionName.c_str());
    
    // Verificăm tipul argumentului
    std::string expectedType = functionSignature->paramters[p_index].getType_asString();
    std::string actualType = $1->get_type();
    
    if (actualType != expectedType) {
        printf("Error: line [%d] variable is not correct type! Expected: %s, but got: %s\n", yylineno, expectedType.c_str(), actualType.c_str());
    }
    
    p_index--; // Decrementăm p_index pentru a verifica următorul argument
}
| ev_expr 
|
;
%%
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
