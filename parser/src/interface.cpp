#include "../inc/interface.h"

Function* Interface::onMemberFunction(string name) {
    Function* function = new Function(name);
    functions.push_back(function);

    return function;
}

DefinitionType Interface::getType() {
    return DFT_INTERFACE;
}

Function* Interface::getFunction(string name) {
    for (int i = 0; i < functions.size(); i++) {
        if (!functions[i]->name.compare(name)) {
            return functions[i];
        }
    }
    return NULL;
}