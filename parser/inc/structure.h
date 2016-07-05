#ifndef __structure_h__
#define __structure_h__

#include <vector>

#include "definition.h"
#include "type_declaration.h"

using namespace std;

class Structure : public Definition {
public:
    Structure(string name):
    Definition(name){
        
    }
    
    void onNewMember(TypeDeclaration* td);
    
    DefinitionType getType();
    std::vector<TypeDeclaration*> members;
};

#endif