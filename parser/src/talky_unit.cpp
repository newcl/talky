#include "../inc/talky_unit.h"

extern DataType stringToDataType(string);

void TalkyUnit::onNewEnum(const std::string name) {
    //cout << "new enum " << name << endl;
    currentDefinition = new Enum(name);
    definitions[name] = currentDefinition;
}
void TalkyUnit::onEnumMember(const std::string name) {
    // cout << "new enum member " << name << endl;
    Enum* theEnum = dynamic_cast<Enum*> (currentDefinition);
    theEnum->onNewMember(name);
}
void TalkyUnit::onEnumDone(string name) {
    currentDefinition->onDone();
}
void TalkyUnit::onNewStructure(const std::string name) {
    // cout << "new structure " << name << endl;
    currentDefinition = new Structure(name);
    definitions[name] = currentDefinition;
}
void TalkyUnit::onStructureMember(const std::string name) {
    // cout << "new structure member " << name << endl;
    TypeDeclaration* td = new TypeDeclaration(currentDeclarationType, currentDataType, name, userTypeDefinition);
    Structure* theStructure = dynamic_cast<Structure*> (currentDefinition);
    theStructure->onNewMember(td);
}
void TalkyUnit::onStructureDone(const std::string name) {
    // cout << "new structure done" << name << endl;
    currentDefinition->onDone();
}
void TalkyUnit::onNewInterface(const std::string name) {
    // cout << "new interface " << name << endl;
    currentDefinition = new Interface(name);
    definitions[name] = currentDefinition;
}
void TalkyUnit::onMemberFunction(const std::string name) {
    // cout << "new member function " << name << endl;
    Interface* theInterface = dynamic_cast<Interface*> (currentDefinition);
    Function& function = *theInterface->onMemberFunction(name);
    for (int i = 0; i < currentFunctionParams.size(); i++) {
        function.addParam(currentFunctionParams[i]);
    }

    currentFunctionParams.clear();
}
void TalkyUnit::onPackage(const std::string packageName) {
    currentPackage = packageName;
}
void TalkyUnit::onFunctionParam(const std::string paramName) {
    Interface* theInterface = dynamic_cast<Interface*> (currentDefinition);
    //Function& function = *theInterface->getFunction(currentFunction);
    TypeDeclaration* td = new TypeDeclaration(currentDeclarationType, currentDataType, paramName, userTypeDefinition);
    currentFunctionParams.push_back(td);
    //function.addParam(td);
    // cout << "new function param " << paramName << endl;
}
void TalkyUnit::onNewInterfaceDone(const std::string interfaceName) {
    // cout << "new interface done" << interfaceName << endl;
}
void TalkyUnit::onDataType(DataType dataType) {
    // cout << "data type " << dataType << endl;
    currentDeclarationType = DLT_PRIMITIVE;
    currentDataType = dataType;
}
void TalkyUnit::onNewLine() {

}
void TalkyUnit::onImport(string importFile) {

}
void TalkyUnit::onUserDataType(string name) {
    Definition* definition = getDefinition(name);
    currentDeclarationType = DLT_USER;
    userTypeDefinition = definition;
}
void TalkyUnit::onNewUserArray(string name) {
    Definition* definition = getDefinition(name);
    currentDeclarationType = DLT_ARRAY;
    userTypeDefinition = definition;
}
void TalkyUnit::onNewPrimitiveArray(string name) {
    DataType dataType = stringToDataType(name);
    currentDeclarationType = DLT_ARRAY;
    currentDataType = dataType;
    userTypeDefinition = NULL;
}
void TalkyUnit::onNewByteArray() {

}

Definition* TalkyUnit::getDefinition(const std::string name) {
    if (definitions.count(name)) {
        return definitions[name];
    }
    return NULL;
}