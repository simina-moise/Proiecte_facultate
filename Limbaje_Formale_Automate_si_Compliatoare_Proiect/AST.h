#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>      // Pentru std::vector
#include <string>      // Pentru std::string
#include <stdexcept>   // Pentru std::invalid_argument
#include <cstdio>  
enum ast_type
{
    aINT,       // integer
    aCHAR,      // char
    aSTRING,    // string
    aFLOAT,     // float
    aOP_UNARY,  // operator meant to work with one subtree
    aOP_BINARY, // operator meant to work with two subtrees
    aBOOL,      // bool
    aID,        // identificator de variabila
    aERR     
};

class AST_value
{
public:
    union
    {
        int i;
        char c;
        char s[100];
        float f;
        bool b;
    } value;
    ast_type type;

    void print_value();
    void print_type();
    std::string get_type();
    std::string get_value();
    AST_value(const char* type, const char* value);
    ~AST_value();
};
class AST
{
public:
    AST_value *left_node;
    AST_value *right_node;
    AST_value *value;

    AST(ast_type typ,AST_value* left, const char* middle, AST_value* right);
    AST(AST_value* left, const char* middle, AST_value* right);
    AST(AST_value value);
        static void validate_function_signature(const std::vector<std::string> &expected_types,
                                            const std::vector<std::string> &received_types);
    
    void *get_value();
    void set_value(void *value);
    void print_value();
    void add_left_node(AST_value *node);
    void add_right_node(AST_value *node);
    AST_value* evaluate();
    ~AST();
};
