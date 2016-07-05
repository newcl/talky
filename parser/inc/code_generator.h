#ifndef __code_generator_h__
#define __code_generator_h__


#include <string>

using namespace std;

class TalkyUnit;

class CodeGenerator {
public:
	CodeGenerator():paramNameIndex(0)
	{}

    virtual void generate(TalkyUnit* unit, string path) = 0;
    string nextParamName();
    int paramNameIndex;
};

#endif