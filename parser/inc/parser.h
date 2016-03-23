#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

inline void _assert(int v){

}

enum DataType
{
	DT_UNKNOWN,	///unknown
	DT_INT64,	///< 8 bytes
	DT_UINT64,	///< 8 bytes.
	DT_DOUBLE,	///< 8 bytes.
	DT_FLOAT,	///< 4 bytes
	DT_INT32,	///< 4 bytes
	DT_UINT32,	///< 4 bytes
	DT_INT16,	///< 2 bytes
	DT_UINT16,	///< 2 bytes
	DT_INT8,	///< 1 bytes
	DT_UINT8,	///< 1 bytes
	DT_BOOL,	///< 1 bytes
	DT_ENUM,	///< 1 bytes
	DT_STRING,	///< len * 1 bytes.
	DT_USER
};

class Definition{
public:
	std::string name;
	Definition(string name){
		this->name = name;
	}
	virtual ~Definition(){}
	void onDone(){

	}
};

class Enum : public Definition {
public:
	Enum(string name):
	Definition(name){

	}

	void onNewMember(string name){
		_assert(std::find(members.begin(), members.end(), name) == members.end());
		members.push_back(name);
	}

	std::vector<string> members;
};


class TypeDeclaration {
public:
	DataType dataType;
	string name;
	Definition* userTypeDefinition;

	TypeDeclaration(DataType dataType, string theName, Definition* definition):
	dataType(dataType),
	name(theName),
	userTypeDefinition(definition){

	}
};


class Structure : public Definition {
public:
	Structure(string name):
	Definition(name){

	}

	void onNewMember(DataType dataType, string name, Definition* definition){
		TypeDeclaration* td = new TypeDeclaration(dataType, name, definition);
		members.push_back(td);
	}

	std::vector<TypeDeclaration*> members;
};


class Function {
public:
	Function(string functionName):
	name(functionName)
	{

	}
	std::vector<TypeDeclaration> params;
	string name;
};

class Interface : public Definition {
public:
	Interface(string name):
	Definition(name){

	}
	void onMemberFunction(string name){
		Function* function = new Function(name);
		functions.push_back(function);
	}
	std::vector<Function*> functions;
};

class Parser{
public:
	static Parser& getInstance();
	Parser():
	currentDefinition(NULL),
	userTypeDefinition(NULL){

	}

	void onNewEnum(const std::string name){
		cout << "new enum " << name << endl;
		currentDefinition = new Enum(name);
		definitions[name] = currentDefinition;
	}
	void onEnumMember(const std::string name){
		cout << "new enum member " << name << endl;
		Enum* theEnum = dynamic_cast<Enum*> (currentDefinition);
		theEnum->onNewMember(name);
	}
	void onEnumDone(string name){
		currentDefinition->onDone();
	}
	void onNewStructure(const std::string name){
		cout << "new structure " << name << endl;
		currentDefinition = new Structure(name);
		definitions[name] = currentDefinition;
	}
	void onStructureMember(const std::string name){
		cout << "new structure member " << name << endl;
		Structure* theStructure = dynamic_cast<Structure*> (currentDefinition);
		theStructure->onNewMember(currentDataType, name, userTypeDefinition);	
	}
	void onStructureDone(const std::string name){
		cout << "new structure done" << name << endl;
		currentDefinition->onDone();
	}
	void onNewInterface(const std::string name){
		cout << "new interface " << name << endl;
		currentDefinition = new Interface(name);
		definitions[name] = currentDefinition;
	}
	void onMemberFunction(const std::string name){
		cout << "new member function " << name << endl;
		Interface* theInterface = dynamic_cast<Interface*> (currentDefinition);
		theInterface->onMemberFunction(name);
	}
	void onFunctionParam(const std::string paramName){
		cout << "new function param " << paramName << endl;
	}
	void onNewInterfaceDone(const std::string interfaceName){
		cout << "new interface done" << interfaceName << endl;
	}
	void onDataType(DataType dataType){
		cout << "data type " << dataType << endl;
	}
	void onNewLine(){

	}
	void onImport(string importFile){

	}
	void onUserDataType(Definition* definition){}
	void onNewArray(){}
	void onNewByteArray(){}
	Definition* getDefinition(const std::string name){
		if(definitions.count(name)){
			return definitions[name];
		}
		return NULL;
	}
	
	Definition* currentDefinition;
	std::string currentFile;
	DataType currentDataType;
	map<string, Definition*> definitions;
	Definition* userTypeDefinition;
};


#endif