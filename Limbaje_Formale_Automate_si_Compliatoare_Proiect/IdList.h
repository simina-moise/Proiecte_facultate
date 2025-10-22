#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

enum value_type
{
    VINT,
    VFLOAT,
    VBOOL,
    VCHAR,
    VSTRING,
    VCLASS
};

enum scope_type {
    GLOBAL,
    CLASS_SCOPE,  // Modificat pentru a evita conflictul
    FUNCTION,
    BLOCK
};
std::string scopeTypeToString(scope_type type);

class IdList;
class ClassType;
class IdInfo;
class ClassList;
class IdFunction;
class Declaration {
public:
    std::string type;
    std::string name;

    Declaration(const std::string& t, const std::string& n) : type(t), name(n) {}
};

class symb_printable
{
public:
    int tab_count = 0;
    string result;

    void append(string sir)
    {
        for (int i = 0; i < tab_count; i++)
            result.append(" ");
        result.append(sir);
        result.append("\n");
    }
    void change_indent(int amount)
    {
        tab_count += amount * 2;
    }
};

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class IdList {
    std::vector<IdInfo> vars;
    std::vector<IdFunction*> functions;
    std::vector<IdList*> nestedScopes;

public:
    IdList* parent;
    ClassList* clList = nullptr;
    scope_type scopeType;
    std::string scopeName;

    IdList(IdList* parent = nullptr, scope_type scopeType = GLOBAL, std::string scopeName = "global");
    
    // Metode pentru variabile
    bool existsVar(const char* s);
    void addVar(const char* type, const char* name, bool isConst = false);
    void setVarValue(const char* name, const char* value);
    IdInfo getVar(const char* s);
    bool isConst(const char* s);

    // Metode pentru funcții
    void addFunction(const char* type, const char* name, bool isConst = false);
    IdFunction* getFunction(const char* s);

    // Generare tabel de simboluri (output standard sau în fișier)
    void gen_symbol_table(symb_printable* result);
void writeSymbolTableToFile(const std::string& fileName) const;


    // Metode pentru scopuri
    void enterScope(IdList* newScope);
    void exitScope();
    void addNestedScope(const std::string& name, scope_type scopeType);

    // Afișări
    void printVars();
    void printTable();

    // Destructor
    ~IdList();

    // Accesarea părintelui
    IdList* getParent() {
        return parent;
    }
};



class ClassType {
public:
    std::string name;         // Numele clasei (tip std::string pentru flexibilitate)
    IdList* list;             // Lista variabilelor și metodelor clasei
    std::vector<std::string> constructors; // Lista constructorilor clasei

    // Constructorul clasei

    ClassType(const std::string& nam);

    // Adaugă un constructor în clasă
    void addConstructor(const std::string& constructorName) {
        constructors.push_back(constructorName);
    }

    // Afișează informații despre scopul clasei
    void printScope() const {
        std::cout << "Scope: " << name << " (Class)" << std::endl;
        for (const auto& constructor : constructors) {
            std::cout << "  Constructor: " << constructor << std::endl;
        }
    }

    // Destructor pentru gestionarea memoriei
    ~ClassType() {
        delete list;
    }
};



class ClassList
{
public:
    std::vector<ClassType *> classes;
    ClassType *currentClass = nullptr; // Clasa curentă

    void addClass(const char *name);
    bool existsClass(const char *name);
    ClassType *getClass(const char *name);

    // Metodă pentru setarea clasei curente
    void setCurrentClass(const char *name) {
        currentClass = getClass(name); // Setează clasa curentă dacă există
    }

    // Metodă pentru resetarea clasei curente
    void resetCurrentClass() {
        currentClass = nullptr;
    }
};

class IdInfo
{
public:
    value_type type_enum;
    string name;
    union data
    {
        int i;
        float f;
        bool b;
        char c;
        char *s;
        ClassType *cls;
    } val;
    bool isConst;

    IdInfo(const char *type, const char *name, ClassList *clList, bool isConst);
    string getType_asString() const;
    value_type getType() const;
    string getValue() const;
};
class IdFunction
{
public:
    value_type return_type;
    string name;
    std::string scopeType;
    std::string scopeName;
    union
    {
        int i;
        float f;
        bool b;
        char c;
        char *s;
        ClassType *cls;
    } val;
    vector<IdInfo> paramters;
    IdList *variables;
     void printScope() const {
        std::cout << "Scope: " << scopeName << " (" << scopeType << ")" << std::endl;
    }
    IdFunction(const char *type, const char *name, ClassList *clList, IdList *parent);
    
    void addParameter(const char *type, const char *name, ClassList *clList, bool isConst = false);
    bool existsParameter(const char *s)
    {
        string strvar = string(s);
        for (const IdInfo &v : paramters)
        {
            if (strvar == v.name)
            {
                return true;
            }
        }
        return false;
    }
    IdInfo getParameter(const char *s)
    {
        string strvar = string(s);
        for (const IdInfo &v : paramters)
        {
            if (strvar == v.name)
            {
                return v;
            }
        }
        return paramters[0];
    }
  
    value_type getParameterType(int paramteter_index);
    string getType_asString() const;
    value_type getType() const;
};

