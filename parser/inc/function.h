#ifndef __function_h__
#define __function_h__

#include <vector>

#include "type_declaration.h"

using namespace std;

class Function {
public:
    Function(string functionName):
    name(functionName)
    {
        
    }
    
    void addParam(TypeDeclaration* td);
    
    std::vector<TypeDeclaration*> params;
    string name;
    
};

#endif