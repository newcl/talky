#ifndef __interface_h__
#define __interface_h__

#include <string>

#include "definition.h"
#include "function.h"

using namespace std;

class Interface : public Definition {
public:
    Interface(string name):
    Definition(name){
        
    }
    Function* onMemberFunction(string name);
    
    DefinitionType getType();
    
    Function* getFunction(string name);
    
    std::vector<Function*> functions;
};

#endif