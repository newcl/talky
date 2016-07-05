#ifndef __enum_h__
#define __enum_h__


#include <vector>

#include "definition.h"
#include "assert.h"

using namespace std;

class Enum : public Definition {
public:
    Enum(string name):
    Definition(name){
    }
    
    void onNewMember(string name){
        _assert(std::find(members.begin(), members.end(), name) == members.end());
        members.push_back(name);
    }
    DefinitionType getType(){
        return DFT_ENUM;
    }
    std::vector<string> members;
};

#endif