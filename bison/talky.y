%{
#define YYDEBUG 1
#include <cstdio>
#include <iostream>
#include "../parser/inc/parser.h"
using namespace std;
// what bison needs to know from flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;
void yyerror(const char* s);

#define YYSTYPE std::string

%}

%token				TOKEN_IDENTIFIER
%token				TOKEN_ENUM
%token				TOKEN_STRUCT
%token				TOKEN_INTERFACE
%token				TOKEN_INT64
%token				TOKEN_UINT64
%token				TOKEN_DOUBLE
%token				TOKEN_FLOAT
%token				TOKEN_INT32
%token				TOKEN_UINT32
%token				TOKEN_INT16
%token				TOKEN_UINT16
%token				TOKEN_INT8
%token				TOKEN_UINT8
%token				TOKEN_BOOL
%token				TOKEN_STRING
%token				TOKEN_ARRAY
%token				TOKEN_BYTES
%token				TOKEN_UINTEGER_LITERAL

%%
talky: definitions;
definitions:
	definitions definition
	|
	/* empty */ 
	;
definition:
	enumeration | structure | interface;

enumeration:
	TOKEN_ENUM
	TOKEN_IDENTIFIER
	{
		cout << "enum definition found " << $2 << endl ;
		Parser::getInstance().onNewEnum($2);
	}
	'{' enumeration_body '}'
	{
	}
	;

enumeration_body:
	enumeration_body enumeration_member
	| 
	/* empty */
	;

enumeration_member:
	TOKEN_IDENTIFIER ','
	{
		Parser::getInstance().onEnumMember($1);
	}
	;

structure:
	TOKEN_STRUCT
	TOKEN_IDENTIFIER
	{
		Parser::getInstance().onNewStructure($2);
	}
	'{' structure_body '}'
	{
	}
	;

structure_body:
	structure_body structure_member
	|
	/* empty */
	;

structure_member:
	data_type TOKEN_IDENTIFIER ';'
	{
		Parser::getInstance().onStructureMember($2);
	}
	;

interface:
	TOKEN_INTERFACE
	TOKEN_IDENTIFIER
	{
		Parser::getInstance().onNewInterface($2);	
	}
	'{' interface_body '}'
	{
	}
	;

interface_body:
	interface_body member_function
	|
	/* empty */
	;

member_function:
	TOKEN_IDENTIFIER
	'(' function_params ')' ';'
	{	
		Parser::getInstance().onMemberFunction($1);
	}
	;

function_params:
	function_params ',' function_param
	| 
	function_param 
	|
	/* empty */
	;

function_param:
	data_type TOKEN_IDENTIFIER
	{
		Parser::getInstance().onFunctionParam($2);
	}
	;

data_type:
	basic_type
	|
	user_type
	|
	user_array_type
	|
	primitive_array_type
	|
	byte_array_type
	;
user_type:
	TOKEN_IDENTIFIER	
	{
		Parser::getInstance().onUserDataType($1);
	}
	;
basic_type:
	TOKEN_INT64	
	{ 
		Parser::getInstance().onDataType(DT_INT64); 
	}
	|
	TOKEN_UINT64 { Parser::getInstance().onDataType(DT_UINT64); }
	|
	TOKEN_DOUBLE {Parser::getInstance().onDataType(DT_DOUBLE); }
	|
	TOKEN_FLOAT	{ Parser::getInstance().onDataType(DT_FLOAT); }
	|
	TOKEN_INT32	{ Parser::getInstance().onDataType(DT_INT32); }
	|
	TOKEN_UINT32 { Parser::getInstance().onDataType(DT_UINT32); }
	|
	TOKEN_INT16	{ Parser::getInstance().onDataType(DT_INT16); }
	|
	TOKEN_UINT16 { Parser::getInstance().onDataType(DT_UINT16); }
	|
	TOKEN_INT8	{ Parser::getInstance().onDataType(DT_INT8); }
	|
	TOKEN_UINT8	{ Parser::getInstance().onDataType(DT_UINT8); }
	|
	TOKEN_BOOL	{ Parser::getInstance().onDataType(DT_BOOL); }
	|
	TOKEN_STRING { Parser::getInstance().onDataType(DT_STRING); }
	;

user_array_type:
	TOKEN_ARRAY '[' user_type ']'
	{
		Parser::getInstance().onNewUserArray($3);
	}
	;
	

primitive_array_type:
	TOKEN_ARRAY '[' basic_type ']'
	{
		Parser::getInstance().onNewPrimitiveArray($3);
	}
	;

byte_array_type:
	TOKEN_BYTES
	{
		Parser::getInstance().onNewByteArray();	
	}
	;

%%
void init();

int main(int argc, char** argv){
	init();

	FILE* talky_flex_input_file = fopen(argv[1], "r");
	if(!talky_flex_input_file){
		cout << "no input found " << argv[1] << endl;
		return -1;
	}
	cout << "parsing " << argv[1] << endl;
	yyin = talky_flex_input_file;

	do{
		yyparse();
	}while(!feof(yyin));

	CodeGenerator* cg = new JavaCodeGenerator();
	cg->generate(Parser::getInstance().definitions, "/Users/chenliang/tmp");

	//yylex();
}

void yyerror(const char* s){
	cerr << "parse error " << std::string(s) << endl;
	//exit(-1);
}