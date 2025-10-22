#include "AST.h"
#include <vector>      // Pentru std::vector
#include <string>      // Pentru std::string
#include <stdexcept>   // Pentru std::invalid_argument
#include <cstdio>      // Pentru printf

void error_handling()
{
    printf("ERROR, DIFFERENT TYPES!");
}
void validate_function_signature(const std::vector<std::string> &expected_types,
                                  const std::vector<std::string> &received_types)
{
    if (expected_types.size() != received_types.size())
    {
        printf("ERROR: Argument count mismatch. Expected %zu, got %zu.\n",
               expected_types.size(), received_types.size());
        throw std::invalid_argument("Function signature mismatch.");
    }

    for (size_t i = 0; i < expected_types.size(); ++i)
    {
        if (expected_types[i] != received_types[i])
        {
            printf("ERROR: Argument type mismatch at position %zu. Expected '%s', got '%s'.\n",
                   i + 1, expected_types[i].c_str(), received_types[i].c_str());
            throw std::invalid_argument("Function signature mismatch.");
        }
    }
}
void AST_value::print_value()
{
    switch (this->type)
    {
    case aINT:
        printf("%d", this->value.i);
        break;
    case aFLOAT:
        printf("%f", this->value.f);
        break;
    case aOP_UNARY:
    case aOP_BINARY:
    case aID:
    case aSTRING:
        printf("%s", this->value.s);
        break;
    case aCHAR:
        printf("%c", this->value.c);
        break;
    case aBOOL:
        printf("%s", this->value.b == true ? "TRUE" : "FALSE");
        break;
    case aERR:
        printf("ERROR AT EVAL");
        break;
    }

    printf("\n");
};
AST_value::AST_value(const char *type, const char *value)
{
    if (strcmp(type, "bool") == 0)
    {
        this->type = aBOOL;

        if (strcmp(value, "true") == 0)
            this->value.b = true;
        else
            this->value.b = false;
    }
    else if (strcmp(type, "int") == 0)
    {
        this->type = aINT;
        this->value.i = atoi(value);
    }
    else if (strcmp(type, "float") == 0)
    {
        this->type = aFLOAT;
        this->value.f = atof(value);
    }
    else if (strcmp(type, "char") == 0)
    {
        this->type = aCHAR;
        this->value.c = value[1];
    }
    else if (strcmp(type, "string") == 0)
    {
        this->type = aSTRING;
        strcpy(this->value.s, value);
    }
    else 
    {
        this->type = aOP_BINARY;
        strcpy(this->value.s, value);
    }
}
void AST_value::print_type()
{

    printf("The type is :");
    switch (this->type)
    {
    case aINT:
        printf("int");
        break;
    case aBOOL:
        printf("bool");
        break;
    case aFLOAT:
        printf("float");
        break;
    case aCHAR:
        printf("char");
        break;
    case aSTRING:
        printf("string");
        break;
    case aERR:
        printf("ERROR AT TYPE");
    }
    printf("\n");
}
std::string AST_value::get_type()
{
    switch (this->type)
    {
    case aINT:
        return std::string("int");
        break;
    case aBOOL:
        return std::string("bool");
        break;
    case aFLOAT:
        return std::string("float");
        break;
    case aCHAR:
        return std::string("char");
        break;
    case aSTRING:
        return std::string("string");
        break;
    case aERR:
        return std::string("err");
    }
    return std::string(" ");
}
AST_value::~AST_value()
{
    // delete this;
}

AST::AST(ast_type typ, AST_value *left, const char *middle, AST_value *right)
{
    this->left_node = left;
    this->right_node = right;
    this->value = new AST_value("op", middle);

    if (typ == aOP_BINARY)
        this->value = new AST_value("op", middle);
}
AST::AST(AST_value *left, const char *middle, AST_value *right)
{
    this->left_node = left;
    this->right_node = right;
    this->value = new AST_value("op", middle);
}

void *AST::get_value()
{
    return this->value;
};
AST::~AST()
{
}
void AST::set_value(void *value)
{
    switch (this->value->type)
    {
    case aINT:
        this->value->value.i = *(int *)value;
        break;
    case aFLOAT:
        this->value->value.f = *(float *)value;
        break;
    case aOP_UNARY:
    case aOP_BINARY:
    case aID:
    case aSTRING:
        strcpy(this->value->value.s, (char *)value);
        break;
    case aCHAR:
        this->value->value.c = *(char *)value;
        break;
    case aBOOL:
        this->value->value.b = *(bool *)value;
        break;
    default:
        error_handling();
    }
};
std::string AST_value::get_value()
{
    switch (this->type)
    {
    case aINT:
        return std::to_string(this->value.i);
        break;
    case aBOOL:
        return this->value.b ? "true" : "false"; // Eliminăm comparația suplimentară
        break;
    case aFLOAT:
        return  std::to_string(this->value.f);
        break;
    case aCHAR:
        return  std::to_string(this->value.c);
        break;
    case aSTRING:
        return  this->value.s;
        break;
    case aERR:
        return  "err";
    }
    return std::string(" ");
}
void AST::print_value()
{
    this->value->print_value();
};
void AST::add_left_node(AST_value *node)
{
    this->left_node = node;
};
void AST::add_right_node(AST_value *node)
{
    this->right_node = node;
}
AST_value *AST::evaluate()
{
    switch (this->value->type)
    {
    case aOP_UNARY:
  {
    if (this->left_node == nullptr) {
        printf("Error: Unary operator '!' has no operand.\n");
        AST_value* errorNode = new AST_value("err", "missing operand");
        errorNode->type = aERR;
        return errorNode;
    }

    char* value = (char*)this->get_value();

    if (strcmp(value, "!") == 0) {
        if (this->left_node->type != aBOOL) {
            if (this->left_node->type == aINT || this->left_node->type == aFLOAT) {
                this->left_node->value.b = this->left_node->value.i != 0; // Conversie numerică la boolean
                this->left_node->type = aBOOL;
            } else {
                printf("Error: Unary operator '!' cannot be applied to type '%d'.\n", this->left_node->type);
                this->left_node->type = aERR;
                return this->left_node;
            }
        }

        // Aplicăm negarea
        this->right_node->value.b = !this->left_node->value.b;
        return this->left_node;
    }

    printf("Error: Invalid unary operator '%s'.\n", value);
    this->left_node->type = aERR;
    return this->left_node;
}

break;

    case aOP_BINARY:
    {
        
        char *value = (char *)this->get_value();

        AST_value *ret_left = this->left_node;
        AST_value *ret_right = this->right_node;

        if (this->left_node->type == aERR || this->right_node->type == aERR)
        {
            this->left_node->type = aERR;
            return this->left_node;
        }
       

        if (!strcmp(value, "+"))
        {
            if (ret_left->type != ret_right->type || ret_left->type == aCHAR || ret_left->type == aSTRING || ret_left->type == aBOOL)
            {
                printf("%d %d", ret_left->type, ret_right->type);
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.i += ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.f += ret_right->value.f;
                break;
            }
        }
        else if (!strcmp(value, "-"))
        {
            if (ret_left->type != ret_right->type || ret_left->type == aCHAR || ret_left->type == aSTRING || ret_left->type == aBOOL)
            {
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.i -= ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.f -= ret_right->value.f;
                break;
            }
        }
        else if (!strcmp(value, "*"))
        {
            if (ret_left->type != ret_right->type || ret_left->type == aCHAR || ret_left->type == aSTRING || ret_left->type == aBOOL)
            {
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.i *= ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.f *= ret_right->value.f;
                break;
            }
        }
        else if (!strcmp(value, "/"))
        {
            if (ret_left->type != ret_right->type || ret_left->type == aCHAR || ret_left->type == aSTRING || ret_left->type == aBOOL)
            {
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.i /= ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.f /= ret_right->value.f;
                break;
            }
        }
        /// ===================== BOOLEAN OPERATION =====================

        else if (!strcmp(value, "||"))
{
    // Asigură-te că ambele părți ale expresiei sunt booleene
    if (ret_left->type != aBOOL)
    {
        if (ret_left->type == aINT || ret_left->type == aFLOAT)
        {
            ret_left->value.b = ret_left->value.i != 0; // Convertim numeric la boolean
            ret_left->type = aBOOL;
        }
        else
        {
            this->left_node->type = aERR;
            return this->left_node;
        }
    }

    if (ret_right->type != aBOOL)
    {
        if (ret_right->type == aINT || ret_right->type == aFLOAT)
        {
            ret_right->value.b = ret_right->value.i != 0; // Convertim numeric la boolean
            ret_right->type = aBOOL;
        }
        else
        {
            this->left_node->type = aERR;
            return this->left_node;
        }
    }

    // Evaluarea operatorului ||
    ret_left->value.b = ret_left->value.b || ret_right->value.b;
    ret_left->type = aBOOL; // Setăm rezultatul la bool
    return ret_left;
}

        else if (!strcmp(value, "&&"))
{
    // Verifică și convertește operanzii la boolean, dacă este posibil
    if (ret_left->type != aBOOL)
    {
        if (ret_left->type == aINT || ret_left->type == aFLOAT)
        {
            ret_left->value.b = ret_left->value.i != 0; // Convert numeric la boolean
            ret_left->type = aBOOL;
        }
        else
        {
            this->left_node->type = aERR;
            return this->left_node;
        }
        
    }

    if (ret_right->type != aBOOL)
    {
        if (ret_right->type == aINT || ret_right->type == aFLOAT)
        {
            ret_right->value.b = ret_right->value.i != 0; // Convert numeric la boolean
            ret_right->type = aBOOL;
        }
        else
        {
            this->left_node->type = aERR;
            return this->left_node;
        }
    }

    // Evaluează operatorul `&&`
    ret_left->value.b = ret_left->value.b && ret_right->value.b;
    ret_left->type = aBOOL; // Setăm rezultatul la bool




    return ret_left;

}

       else if (!strcmp(value, "=="))
{
    // Permite comparații între tipuri compatibile (int și float)
    if (!((ret_left->type == ret_right->type) || 
          ((ret_left->type == aINT || ret_left->type == aFLOAT) && 
           (ret_right->type == aINT || ret_right->type == aFLOAT))))
    {
        this->left_node->type = aERR;
        return this->left_node;
    }
  
    bool res = false;

    switch (ret_left->type)
    {
    case aINT:
        if (ret_right->type == aINT)
            res = ret_left->value.i == ret_right->value.i;
        else if (ret_right->type == aFLOAT)
            res = ret_left->value.i == ret_right->value.f;
        break;
    case aFLOAT:
        if (ret_right->type == aINT)
            res = ret_left->value.f == ret_right->value.i;
        else if (ret_right->type == aFLOAT)
            res = ret_left->value.f == ret_right->value.f;
        break;
    case aBOOL:
        res = ret_left->value.b == ret_right->value.b;
        break;
    case aCHAR:
        res = ret_left->value.c == ret_right->value.c;
        break;
    case aSTRING:
        res = strcmp(ret_left->value.s, ret_right->value.s) == 0;
        break;
    default:
        this->left_node->type = aERR;
        return this->left_node;
    }

    // Setează rezultatul ca boolean
    AST_value* resultNode = new AST_value("result", "comparison result");

    resultNode->value.b = res; // Setează rezultatul
    resultNode->type = aBOOL; // Setează tipul la boolean
    return resultNode; // Returnează nodul cu tipul corect
}


        else if (!strcmp(value, "!="))
        {
            if (ret_left->type != ret_right->type)
            {
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.b = ret_left->value.i != ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.b = ret_left->value.f != ret_right->value.f;
                break;
            case aBOOL:
                ret_left->value.b = ret_left->value.b != ret_right->value.b;
                break;
            case aCHAR:
                ret_left->value.b = ret_left->value.c != ret_right->value.c;
                break;
            case aSTRING:
                ret_left->value.b = 0 != strcmp(ret_left->value.s, ret_right->value.s);
                break;
            }

            ret_left->type = aBOOL;
            return ret_left;
        }
        else if (!strcmp(value, ">"))
{
    // Permite comparații între tipuri compatibile (int și float)
    if (!((ret_left->type == ret_right->type) || 
          ((ret_left->type == aINT || ret_left->type == aFLOAT) && 
           (ret_right->type == aINT || ret_right->type == aFLOAT))))
    {
        this->left_node->type = aERR;
        return this->left_node;
    }

    bool res = false;

    switch (ret_left->type)
    {
    case aINT:
        if (ret_right->type == aINT)
            res = ret_left->value.i > ret_right->value.i;
        else if (ret_right->type == aFLOAT)
            res = ret_left->value.i > ret_right->value.f;
        break;
    case aFLOAT:
        if (ret_right->type == aINT)
            res = ret_left->value.f > ret_right->value.i;
        else if (ret_right->type == aFLOAT)
            res = ret_left->value.f > ret_right->value.f;
        break;
    default:
        this->left_node->type = aERR;
        return this->left_node;
    }

    ret_left->value.b = res;
    ret_left->type = aBOOL; 
    return ret_left;
}

        else if (!strcmp(value, ">="))
        {

            if (ret_left->type != ret_right->type)
            {
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.b = ret_left->value.i >= ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.b = ret_left->value.f >= ret_right->value.f;
                break;
            case aBOOL:
                ret_left->value.b = ret_left->value.b >= ret_right->value.b;
                break;
            case aCHAR:
                ret_left->value.b = ret_left->value.c >= ret_right->value.c;
                break;
            case aSTRING:
                ret_left->value.b = 0 <= strcmp(ret_left->value.s, ret_right->value.s);
                break;
            }

            ret_left->type = aBOOL;
            return ret_left;
        }
        else if (!strcmp(value, "<"))
        {

            if (ret_left->type != ret_right->type)
            {
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.b = ret_left->value.i < ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.b = ret_left->value.f < ret_right->value.f;
                break;
            case aBOOL:
                ret_left->value.b = ret_left->value.b < ret_right->value.b;
                break;
            case aCHAR:
                ret_left->value.b = ret_left->value.c < ret_right->value.c;
                break;
            case aSTRING:
                ret_left->value.b = 0 > strcmp(ret_left->value.s, ret_right->value.s);
                break;
            }

            ret_left->type = aBOOL;
            return ret_left;
        }
        else if (!strcmp(value, "<="))
        {

            if (ret_left->type != ret_right->type)
            {
                this->left_node->type = aERR;
                return this->left_node;
            }

            switch (ret_left->type)
            {
            case aINT:
                ret_left->value.b = ret_left->value.i <= ret_right->value.i;
                break;
            case aFLOAT:
                ret_left->value.b = ret_left->value.f <= ret_right->value.f;
                break;
            case aBOOL:
                ret_left->value.b = ret_left->value.b <= ret_right->value.b;
                break;
            case aCHAR:
                ret_left->value.b = ret_left->value.c <= ret_right->value.c;
                break;
            case aSTRING:
                ret_left->value.b = 0 >= strcmp(ret_left->value.s, ret_right->value.s);
                break;
            }

            ret_left->type = aBOOL;
        }
        /// ===================== BOOLEAN OPERATION =====================
        
        return ret_left;
    }
    break;
    case aINT:
    case aFLOAT:
    case aBOOL:
    case aCHAR:
    case aSTRING:
        return nullptr;
        break;
    }
    return nullptr;
};
