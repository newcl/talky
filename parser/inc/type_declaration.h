
#ifndef __type_declaration_h__
#define __type_declaration_h__

#include <string>
#include "data_type.h"
#include "declaration_type.h"

using namespace std;

class Definition;

class TypeDeclaration {
public:
    DeclarationType declarationType;
    DataType dataType;
    string name;
    Definition* userTypeDefinition;
    
    TypeDeclaration(DeclarationType theDeclarationType,
                    DataType theDataType,
                    string theName,
                    Definition* definition):
    declarationType(theDeclarationType),
    dataType(theDataType),
    name(theName),
    userTypeDefinition(definition){
    }
};

#endif