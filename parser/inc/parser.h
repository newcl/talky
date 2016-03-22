#ifndef __PARSER__
#define __PARSER__

#include <iostream>
using namespace std;

enum DataType
{
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

};

class Enum : Definition {

};

class Structure : Definition {

};

class Interface : Definition {

};

class Parser{
public:
	static Parser& getInstance();
	void onNewEnum(const std::string enumName){
		cout << "new enum " << enumName << endl; 
	}
	void onEnumMember(const std::string enumMember){
		cout << "new enum member " << enumMember << endl;
	}
	void onNewStructure(const std::string structureName){
		cout << "new structure " << structureName << endl;
	}
	void onStructureMember(const std::string structureMemberName){
		cout << "new structure member " << structureMemberName << endl;
	}
	void onNewInterface(const std::string interfaceName){
		cout << "new interface " << interfaceName << endl;
	}
	void onMemberFunction(const std::string memberFunctionName){
		cout << "new member function " << memberFunctionName << endl;
	}
	void onFunctionParam(const std::string paramName){
		cout << "new function param " << paramName << endl;
	}
	void onDataType(DataType dataType){
		cout << "data type " << dataType << endl;
	}
	void onNewLine(){
		
	}
	void onUserDataType(Definition* definition){}
	void onNewArray(){}
	void onNewByteArray(){}
	Definition* getDefinition(const std::string name){return NULL;}
	
private:

};


#endif