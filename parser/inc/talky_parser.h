#ifndef __talky_parser_h__
#define __talky_parser_h__


#include <string>
#include <iostream>

#include "enum.h"
#include "data_type.h"
#include "talky_unit.h"

class TalkyUnit;
class Definition;
class vector;

using namespace std;

class TalkyParser{
public:
    static TalkyParser& getInstance();
    TalkyParser():
    lineNumber(0){
        
    }

    void onTalkyUnitParsed(TalkyUnit* unit);
    TalkyUnit* takeTalkyUnit();

    bool hasMoreTalkyUnits();

    void parse(string filePath);

    TalkyUnit* assembleTalkyUnit(string filePath);
    
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


    TalkyUnit* currentUnit;
    vector<TalkyUnit*> parseHistory;
    vector<TalkyUnit*> parsedTalkyUnits;
    int lineNumber;
    
};

#endif