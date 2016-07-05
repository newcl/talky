#include "../inc/code_generator.h"
#include "../inc/util.h"

string CodeGenerator::nextParamName() {
    return "__" + __ITOA((paramNameIndex++)) + "__";
}