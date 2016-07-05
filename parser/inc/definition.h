#ifndef __definition_h__
#define __definition_h__

#include <string>

#include "definition_type.h"

using namespace std;

class Definition{
public:
    std::string name;
    Definition(string name){
        this->name = name;
    }
    virtual ~Definition(){}
    void onDone(){
    }
    
    virtual DefinitionType getType()=0;
};

#endif