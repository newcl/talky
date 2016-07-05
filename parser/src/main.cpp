#include "../inc/main.h"

extern FILE* yyin;

TalkyParser& TalkyParser::getInstance()
{
	static TalkyParser parser;
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

int main(int argc, char** argv){
	init();

	po::options_description desc("Valid Options:");
	desc.add_options()
		("help", "help info")
		("file", po::value<std::string>(), "specify talky definition file")
		("output", po::value<std::string>(), "specify output directory")
		("lang", po::value<std::string>(), "specify output language");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help")){
		cout << desc << endl;
		return 0;
	}

	string talkyFile;
	if(vm.count("file")){
		talkyFile = vm["file"].as<std::string>();
		cout << "talky:" << talkyFile << endl;
	}else{
		cout << "need to specify talky definition file" << endl;
		return 1;
	}
	string outputPath;
	if(vm.count("output")){
		outputPath = vm["output"].as<std::string>();
		cout << "outputPath:" << outputPath << endl;
	}else{
		cout << "need to specify outputPath" << endl;
		return 1;
	}

	fs::path dir(outputPath);
	if(fs::is_regular_file(dir)){
		cout << "output path is a file:" << outputPath << endl;
		return 1;
	}
	// not exist create
	if(!fs::exists(dir)){
		if(boost::filesystem::create_directories(dir)) {
			//std::cout << "Success" << "\n";
		}else{

		}
	}
	

	// should exist and is a directory
	if(!fs::exists(dir) || !fs::is_directory(dir)){
		cout << "output path invalid:" << outputPath << endl;
		return 1;
	}

	// FILE* talky_flex_input_file = fopen(talkyFile.c_str(), "r");
	// if(!talky_flex_input_file){
	// 	cout << "no input found " << talkyFile << endl;
	// 	return -1;
	// }

	TalkyParser::getInstance().parse(talkyFile);
	// TODO move to Parser::parse
	do{
		TalkyUnit* talkyUnit = TalkyParser::getInstance().takeTalkyUnit();
		yyin = talkyUnit->file;
		do{
			int code = yyparse();
			if(code == 0){
				/*
				this can mean 2 things
				1. move on to the next talky file by import
				2. the current talky file is parsed successfully
				 */
				break;
			}
		}while(!feof(yyin));	

		TalkyParser::getInstance().onTalkyUnitParsed(talkyUnit);
	}while(TalkyParser::getInstance().hasMoreTalkyUnits());

	dir = fs::complete(dir);
	string absolutePath = dir.native();
	CodeGenerator* cg = new JavaCodeGenerator();

	for(int i=0; i < TalkyParser::getInstance().parsedTalkyUnits.size();i++){
		TalkyUnit* unit = TalkyParser::getInstance().parsedTalkyUnits[i];
		cg->generate(unit, absolutePath);
	}

	// all the parsing is done, write language bindings
	
	
}

void yyerror(const char* s){
	cout << "parse error " << std::string(s) << endl;
}