#ifndef __talky_unit_h__
#define __talky_unit_h__

#include <map>
#include <vector>

#include "declaration_type.h"
#include "type_declaration.h"
#include "enum.h"
#include "structure.h"
#include "interface.h"
#include "function.h"

using namespace std;


class TalkyUnit{
public:
    TalkyUnit(FILE* file):
    currentDefinition(NULL),
    userTypeDefinition(NULL),
    file(file),
    currentPackage("")
    {
    }

    void onNewEnum(const std::string name);
    void onEnumMember(const std::string name);
    void onEnumDone(string name);
    void onNewStructure(const std::string name);
    void onStructureMember(const std::string name);
    void onStructureDone(const std::string name);
    void onNewInterface(const std::string name);
    void onMemberFunction(const std::string name);
    void onPackage(const std::string packageName);
    void onFunctionParam(const std::string paramName);
    void onNewInterfaceDone(const std::string interfaceName);
    void onDataType(DataType dataType);
    void onNewLine();
    void onImport(string importFile);
    void onUserDataType(string name);
    void onNewUserArray(string name);
    void onNewPrimitiveArray(string name);
    void onNewByteArray();
    Definition* getDefinition(const std::string name);

    DeclarationType currentDeclarationType;
    Definition* currentDefinition;
    std::string currentFile;
    DataType currentDataType;
    map<string, Definition*> definitions;
    Definition* userTypeDefinition;
    string currentFunction;
    vector<TypeDeclaration*> currentFunctionParams;
    string currentPackage;
    FILE* file;
};

#endif