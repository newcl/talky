#ifndef __enum_h__
#define __enum_h__


#include <vector>
#include <algorithm>

#include "definition.h"
#include "assert.h"

using namespace std;

class Enum : public Definition {
public:
    Enum(string name):
    Definition(name){
    }
    
    void onNewMember(string name);
    DefinitionType getType();
    std::vector<string> members;
};

#endif