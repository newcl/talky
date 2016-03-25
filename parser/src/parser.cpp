#include "../inc/parser.h"

Parser& Parser::getInstance()
{
	static Parser parser;
	return parser;
}

typedef map<DataType, string> DataType2StringMap;
typedef map<string, DataType> String2DataTypeMap;

DataType2StringMap dataType2String;
String2DataTypeMap string2DataType;

void init(){
	string2DataType["int64"] = DT_INT64;
	string2DataType["uint64"] = DT_UINT64;
	string2DataType["double"] = DT_DOUBLE;
	string2DataType["float"] = DT_FLOAT;
	string2DataType["int32"] = DT_INT32;
	string2DataType["uint32"] = DT_UINT32;
	string2DataType["int16"] = DT_INT16;
	string2DataType["uint16"] = DT_UINT16;
	string2DataType["int8"] = DT_INT8;
	string2DataType["uint8"] = DT_UINT8;
	string2DataType["bool"] = DT_BOOL;
	string2DataType["string"] = DT_STRING;
}

DataType stringToDataType(string name){
	if(string2DataType.count(name)){
		return string2DataType[name];
	}

	return DT_UNKNOWN;
}