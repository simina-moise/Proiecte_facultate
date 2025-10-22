#include "IdList.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
extern IdList* ids;

// Adaugă o variabilă în lista curentă de variabile
void IdList::addVar(const char* type, const char* name, bool isConst) {
    // Verifică dacă variabila există deja
    for (const IdInfo& var : vars) {
        if (var.name == name) {
            throw std::runtime_error("Variable '" + std::string(name) + "' is already defined in this scope.");
        }
    }

    // Adaugă variabila
    vars.emplace_back(type, name, clList, isConst);
}


void IdList::setVarValue(const char *name, const char *value)
{
    string strvar = string(name);
    for (IdInfo &v : vars)
    {
        if (strvar == v.name)
        {
            switch (v.getType())
            {
            case VINT:
                v.val.i = stoi(value);
                break;
            case VFLOAT:
                v.val.f = stof(value);
                break;
            case VBOOL:
                if (strcmp(value, "true") == 0)
                    v.val.b = true;
                else
                    v.val.b = false;
                break;
            case VSTRING:
                strncpy(v.val.s, value + 1, strlen(value) - 3);
                break;
            case VCHAR:
                v.val.c = value[1];
                break;
            }
        }
    }
}
// Adaugă o funcție în tabelul de simboluri
void IdList::addFunction(const char* type, const char* name, bool isConst) {
    // Verifică dacă funcția există deja
    for (const IdFunction* existingFunc : functions) {
        if (strcmp(existingFunc->name.c_str(), name) == 0) {
            throw std::runtime_error(std::string("Function '") + name + "' is already defined in this scope.");
        }
    }

    // Adaugă funcția
    printf("Added function %s of type %s\n", name, type);
    IdFunction* func = new IdFunction(type, name, this->clList, this);
    functions.push_back(func);
}


void IdList::enterScope(IdList* newScope) {
    if (!newScope) {
        throw std::runtime_error("Invalid scope to enter.");
    }
    ids = newScope; // Setează scopul curent
}

void IdList::exitScope() {
    if (!ids || !ids->parent) {
        throw std::runtime_error("Cannot exit scope: no parent scope.");
    }
    ids = ids->parent; // Revine la scopul părinte
}

bool IdList::existsVar(const char *var)
{
    string strvar = string(var);
    for (const IdInfo &v : vars)
    {
        if (strvar == v.name)
        {
            return true;
        }
    }
    for (IdFunction *v : functions)
    {
        if (strvar == v->name)
        {
            return true;
        }
    }
    return false;
}

void IdList::printVars()
{
    for (const IdInfo &v : vars)
    {
        cout << "name: " << v.name << " type:" << v.getType_asString() << endl;
    }
}
IdInfo IdList::getVar(const char *var)
{
    string strvar = string(var);
    for (IdInfo &v : vars)
    {
        if (strvar == v.name)
        {
            return v;
        }
    }
    return this->vars[0];
}
IdFunction *IdList::getFunction(const char *s)
{
    int size = this->functions.size();
    IdFunction **data = this->functions.data();
    for (int i = 0; i < size; i++)
    {
        if (strcmp(data[i]->name.c_str(), s) == 0)
            return data[i];
    }

    return nullptr;
}

bool IdList::isConst(const char *s)
{
    return this->getVar(s).isConst;
}
IdList::IdList(IdList *parent, scope_type scopeType, string scopeName)
    : parent(parent), clList(nullptr), scopeType(scopeType), scopeName(scopeName) {}

IdList::~IdList()
{
    vars.clear();
}
// Implementarea metodei writeSymbolTableToFile
void IdList::writeSymbolTableToFile(const std::string& fileName) const {
    std::ofstream outFile(fileName, std::ios::app); // Deschidere în modul "append"
    if (!outFile) {
        std::cerr << "Eroare la deschiderea fișierului: " << fileName << std::endl;
        return;
    }

    // Scrierea scopului curent
    outFile << "Scope: " << scopeName << " (" << (scopeType == GLOBAL ? "Global" : "Nested") << ")\n";

    // Scrierea variabilelor
    outFile << "Variables:\n";
    for (const auto& var : vars) {
        outFile << "  Name: " << var.name
                << ", Type: " << var.getType_asString()
                << ", Value: " << var.getValue() << "\n";
    }

    // Scrierea funcțiilor
    outFile << "Functions:\n";
    for (const auto* func : functions) {
        outFile << "  Name: " << func->name
                << ", Return Type: " << func->getType_asString() << "\n";
    }

    // Scrierea scopurilor imbricate
    if (!nestedScopes.empty()) {
        outFile << "Nested Scopes:\n";
        for (const auto* nested : nestedScopes) {
            nested->writeSymbolTableToFile(fileName);
        }
    }

    outFile.close();
}

void IdList::gen_symbol_table(symb_printable *result)
{
    result->append("Scope: " + scopeName);
    result->append("Variables: ");
    result->append("{");
    result->change_indent(2);
    for (IdInfo var : this->vars)
    {
        result->append("{");
        result->change_indent(1);

        result->append(string("Name: ").append(var.name));
        result->append(string("Type: ").append(var.getType_asString()));
        string value("Value: ");
        switch (var.type_enum)
        {
        case VINT:
        {
            value.append(std::to_string(var.val.i));
            result->append(value);
        }
        break;
        case VFLOAT:
        {
            result->append(std::to_string(var.val.f));
            result->append(value);
        }
        break;
        case VCHAR:
        {
            value.append(std::to_string(var.val.c));
            result->append(value);
        }
        break;
        case VBOOL:
        {
            if (var.val.b == true)
                value.append("true");
            else
                value.append("false");
            result->append(value);
        }
        break;
        case VSTRING:
        {
            value.append(var.val.s);
            result->append(value);
        }
        break;
        case VCLASS:
        {
            result->append(value);
            var.val.cls->list->gen_symbol_table(result);
            // todo
        }
        break;
        }
        result->change_indent(-1);
        result->append("}");
    }
    result->change_indent(-2);
    result->append("}");
    result->append("Functions: ");
    result->append("{");
    result->change_indent(2);
    for (IdFunction *func : this->functions)
    {
        result->append("{");
        result->change_indent(1);

        result->append(string("Name: ").append(func->name));
        result->append(string("Type: ").append(func->getType_asString()));
        result->append(string("Parameters: "));
        result->append("{");
        result->change_indent(1);

        for (IdInfo param : func->paramters)
        {
            result->append("{");
            result->change_indent(1);

            result->append(string("Name: ").append(param.name));
            result->append(string("Type: ").append(param.getType_asString()));

            result->change_indent(-1);
            result->append("}");
        }
        for (IdInfo param : func->variables->vars)
        {
            result->append("{");
            result->change_indent(1);

            result->append(string("Name: ").append(param.name));
            result->append(string("Type: ").append(param.getType_asString()));

            result->change_indent(-1);
            result->append("}");
        }

        result->change_indent(-1);
        result->append("}");

        result->change_indent(-1);
        result->append("}");
    }
    result->change_indent(-2);
    result->append("}");
}
std::string scopeTypeToString(scope_type type) {
    switch (type) {
        case GLOBAL:
            return "Global";
        case CLASS_SCOPE:
            return "Class";
        case FUNCTION:
            return "Function";
        case BLOCK:
            return "Block";
        default:
            return "Unknown";
    }
}

 
void IdList::printTable()
{
    symb_printable result;
    gen_symbol_table(&result);
    cout << result.result;
}

ClassType::ClassType(const std::string& nam)
    : name(nam), list(new IdList(nullptr, CLASS_SCOPE, nam)) {}


void ClassList::addClass(const char* name) {
    for (auto& existingClass : classes) {
        if (strcmp(existingClass->name.c_str(), name) == 0) {
            return; // Clasa există deja
        }
    }
    classes.push_back(new ClassType(name));
}

bool ClassList::existsClass(const char* name) {
    for (auto& v : classes) {
        if (strcmp(name, v->name.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

ClassType* ClassList::getClass(const char* name) {
    for (auto& cls : classes) {
        if (strcmp(cls->name.c_str(), name) == 0) {
            return cls;
        }
    }
    return nullptr;
}


IdInfo::IdInfo(const char *type, const char *name, ClassList *clList, bool isConst)
{
    this->name = string(name);

    if (strcmp(type, "float") == 0)
    {
        this->type_enum = VFLOAT;
        this->val.f = 0;
    }
    else if (strcmp(type, "int") == 0)
    {
        this->type_enum = VINT;
        this->val.i = 0;
    }
    else if (strcmp(type, "char") == 0)
    {
        this->type_enum = VCHAR;
        this->val.c = '0';
    }
    else if (strcmp(type, "bool") == 0)
    {
        this->type_enum = VBOOL;
        this->val.b = false;
    }
    else if (strcmp(type, "string") == 0)
    {
        this->type_enum = VSTRING;
        this->val.s = new char[1];
    }
    else // is class instance
    {
        this->type_enum = VCLASS;
        this->val.cls = clList->getClass(type);
    }
};
string IdInfo::getType_asString() const
{
    switch (this->type_enum)
    {
    case VBOOL:
    {
        string ret("bool");
        return ret;
    }
    break;
    case VCHAR:
    {
        string ret("char");
        return ret;
    }
    break;
    case VCLASS:
    {
        string ret(this->val.cls->name);
        return ret;
    }
    break;
    case VFLOAT:
    {
        string ret("float");
        return ret;
    }
    break;
    case VINT:
    {
        string ret("int");
        return ret;
    }
    break;
    case VSTRING:
    {

        string ret("string");
        return ret;
    }
    break;
    }
    return string("");
}

value_type IdInfo::getType() const
{
    return this->type_enum;
}
string IdInfo::getValue() const
{
    switch (this->type_enum)
    {
    case VBOOL:
    {
        string ret;
        if(this->val.b == true)
            ret ="true";
        else
            ret= "false";

        return ret;
    }
    break;
    case VCHAR:
    {
        string ret;
        ret.push_back(this->val.c);
        return ret;
    }
    break;
    case VCLASS:
    {
        string ret("0");
        return ret;
    }
    break;
    case VFLOAT:
    {
        string ret(std::to_string(this->val.f));
        return ret;
    }
    break;
    case VINT:
    {
        string ret(std::to_string(this->val.i));
        return ret;
    }
    break;
    case VSTRING:
    {

        string ret(this->val.s);
        return ret;
    }
    break;
    }
    return string("");
}
IdFunction::IdFunction(const char *type, const char *name, ClassList *clList, IdList *parent)
{
    this->name = string(name);

    if (strcmp(type, "float") == 0)
    {
        this->return_type = VFLOAT;
        this->val.f = 0;
    }
    else if (strcmp(type, "int") == 0)
    {
        this->return_type = VINT;
        this->val.i = 0;
    }
    else if (strcmp(type, "char") == 0)
    {
        this->return_type = VCHAR;
        this->val.c = '0';
    }
    else if (strcmp(type, "bool") == 0)
    {
        this->return_type = VBOOL;
        this->val.b = false;
    }
    else if (strcmp(type, "string") == 0)
    {
        this->return_type = VSTRING;
        this->val.s = new char[1];
    }
    else // is class instance
    {
        this->return_type = VCLASS;
        this->val.cls = clList->getClass(type);
    }
    this->variables = new IdList(parent, FUNCTION, name);
}
string IdFunction::getType_asString() const
{
    switch (this->return_type)
    {
    case VBOOL:
    {
        string ret("bool");
        return ret;
    }
    break;
    case VCHAR:
    {
        string ret("char");
        return ret;
    }
    break;
    case VCLASS:
    {
        string ret(this->val.cls->name);
        return ret;
    }
    break;
    case VFLOAT:
    {
        string ret("float");
        return ret;
    }
    break;
    case VINT:
    {
        string ret("int");
        return ret;
    }
    break;
    case VSTRING:
    {

        string ret("string");
        return ret;
    }
    break;
    }
    return string("");
}
value_type IdFunction::getType() const
{
    return this->return_type;
}
void IdFunction::addParameter(const char *type, const char *name, ClassList *clList, bool isConst)
{
    printf("added parameter %s of type %s to function %s\n",name,type,this->name.c_str());
    this->paramters.push_back(IdInfo(type, name, clList, isConst));
}
value_type IdFunction::getParameterType(int paramteter_index)
{
    return this->paramters[paramteter_index].getType();
}


