#include "../inc/talky_parser.h"

void TalkyParser::onTalkyUnitParsed(TalkyUnit* unit) {
    parsedTalkyUnits.push_back(unit);
}

TalkyUnit* TalkyParser::takeTalkyUnit() {
    TalkyUnit* unit = parseHistory.back();
    parseHistory.pop_back();
    return unit;
}

bool TalkyParser::hasMoreTalkyUnits() {
    return parseHistory.size() > 0;
}

void TalkyParser::parse(string filePath) {
    currentUnit = assembleTalkyUnit(filePath);
    parseHistory.push_back(currentUnit);
}

TalkyUnit* TalkyParser::assembleTalkyUnit(string filePath) {
    FILE* talkyFile = fopen(filePath.c_str(), "r");
    if (!talkyFile)
    {
        cout << "talky file does not exist:" << filePath << endl;
        exit(-1);
    }
    return new TalkyUnit(talkyFile);
}

void TalkyParser::onNewEnum(const std::string name) {
    // cout << "new enum " << name << endl;
    // currentDefinition = new Enum(name);
    // definitions[name] = currentDefinition;
    currentUnit->onNewEnum(name);
}
void TalkyParser::onEnumMember(const std::string name) {
    // cout << "new enum member " << name << endl;
    // Enum* theEnum = dynamic_cast<Enum*> (currentDefinition);
    // theEnum->onNewMember(name);
    currentUnit->onEnumMember(name);
}
void TalkyParser::onEnumDone(string name) {
    // currentDefinition->onDone();
    currentUnit->onEnumDone(name);
}
void TalkyParser::onNewStructure(const std::string name) {
    // cout << "new structure " << name << endl;
    // currentDefinition = new Structure(name);
    // definitions[name] = currentDefinition;
    currentUnit->onNewStructure(name);
}
void TalkyParser::onStructureMember(const std::string name) {
    // cout << "new structure member " << name << endl;
    // TypeDeclaration* td = new TypeDeclaration(currentDeclarationType, currentDataType, name, userTypeDefinition);
    // Structure* theStructure = dynamic_cast<Structure*> (currentDefinition);
    // theStructure->onNewMember(td);
    currentUnit->onStructureMember(name);
}
void TalkyParser::onStructureDone(const std::string name) {
    // cout << "new structure done" << name << endl;
    // currentDefinition->onDone();
    currentUnit->onStructureDone(name);
}
void TalkyParser::onNewInterface(const std::string name) {
    // cout << "new interface " << name << endl;
    // currentDefinition = new Interface(name);
    // definitions[name] = currentDefinition;
    currentUnit->onNewInterface(name);
}
void TalkyParser::onMemberFunction(const std::string name) {
    // cout << "new member function " << name << endl;
    // Interface* theInterface = dynamic_cast<Interface*> (currentDefinition);
    // Function& function = *theInterface->onMemberFunction(name);
    // for(int i=0; i < currentFunctionParams.size();i++){
    //     function.addParam(currentFunctionParams[i]);
    // }

    // currentFunctionParams.clear();
    currentUnit->onMemberFunction(name);
}
void TalkyParser::onPackage(const std::string packageName) {
    // currentPackage = packageName;
    cout << "onPackage" << packageName << endl;
    currentUnit->onPackage(packageName);
}
void TalkyParser::onFunctionParam(const std::string paramName) {
    // Interface* theInterface = dynamic_cast<Interface*> (currentDefinition);
    // //Function& function = *theInterface->getFunction(currentFunction);
    // TypeDeclaration* td = new TypeDeclaration(currentDeclarationType, currentDataType, paramName, userTypeDefinition);
    // currentFunctionParams.push_back(td);
    // //function.addParam(td);
    // cout << "new function param " << paramName << endl;

    currentUnit->onFunctionParam(paramName);
}
void TalkyParser::onNewInterfaceDone(const std::string interfaceName) {
    // cout << "new interface done" << interfaceName << endl;
    currentUnit->onNewInterfaceDone(interfaceName);
}
void TalkyParser::onDataType(DataType dataType) {
    // cout << "data type " << dataType << endl;
    // currentDeclarationType = DLT_PRIMITIVE;
    // currentDataType = dataType;

    currentUnit->onDataType(dataType);
}
void TalkyParser::onNewLine() {
    currentUnit->onNewLine();
}
void TalkyParser::onImport(string importFile) {
    // currentUnit->onImport(importFile);
    parseHistory.push_back(currentUnit);

    currentUnit = assembleTalkyUnit(importFile);
    parseHistory.push_back(currentUnit);
    //stop the current yyparse execution and get into the next one
}
void TalkyParser::onUserDataType(string name) {
    // Definition* definition = getDefinition(name);
    // currentDeclarationType = DLT_USER;
    // userTypeDefinition = definition;
    currentUnit->onUserDataType(name);
}
void TalkyParser::onNewUserArray(string name) {
    // Definition* definition = getDefinition(name);
    // currentDeclarationType = DLT_ARRAY;
    // userTypeDefinition = definition;
    currentUnit->onNewUserArray(name);
}
void TalkyParser::onNewPrimitiveArray(string name) {
    // DataType dataType = stringToDataType(name);
    // currentDeclarationType = DLT_ARRAY;
    // currentDataType = dataType;
    // userTypeDefinition = NULL;

    currentUnit->onNewPrimitiveArray(name);
}
void TalkyParser::onNewByteArray() {}
Definition* TalkyParser::getDefinition(const std::string name) {
    // if(definitions.count(name)){
    //     return definitions[name];
    // }
    // return NULL;
    return currentUnit->getDefinition(name);
}