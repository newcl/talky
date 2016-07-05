%{
#define YYDEBUG 1
#include <cstdio>
#include <iostream>
#include "../parser/inc/talky_parser.h"
using namespace std;
// what bison needs to know from flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;
void yyerror(const char* s);

#define YYSTYPE std::string
//#define YYDEBUG 1
%}
%error-verbose
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
%token				TOKEN_PACKAGE
%token				TOKEN_IDENTIFIER_PACKAGE



%%
talky: package definitions | definitions;
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
		//cout << "enum definition found " << $2 << endl ;
		TalkyParser::getInstance().onNewEnum($2);
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
		TalkyParser::getInstance().onEnumMember($1);
	}
	;

structure:
	TOKEN_STRUCT
	TOKEN_IDENTIFIER
	{
		TalkyParser::getInstance().onNewStructure($2);
	}
	'{' structure_body '}'
	{
	}
	;

package:
	TOKEN_PACKAGE TOKEN_IDENTIFIER_PACKAGE ';'
	{
		TalkyParser::getInstance().onPackage($2);
		//YYACCEPT
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
		TalkyParser::getInstance().onStructureMember($2);
	}
	;

interface:
	TOKEN_INTERFACE
	TOKEN_IDENTIFIER
	{
		TalkyParser::getInstance().onNewInterface($2);	
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
		TalkyParser::getInstance().onMemberFunction($1);
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
		TalkyParser::getInstance().onFunctionParam($2);
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
		TalkyParser::getInstance().onUserDataType($1);
	}
	;
basic_type:
	TOKEN_INT64	
	{ 
		TalkyParser::getInstance().onDataType(DT_INT64); 
	}
	|
	TOKEN_UINT64 { TalkyParser::getInstance().onDataType(DT_UINT64); }
	|
	TOKEN_DOUBLE {TalkyParser::getInstance().onDataType(DT_DOUBLE); }
	|
	TOKEN_FLOAT	{ TalkyParser::getInstance().onDataType(DT_FLOAT); }
	|
	TOKEN_INT32	{ TalkyParser::getInstance().onDataType(DT_INT32); }
	|
	TOKEN_UINT32 { TalkyParser::getInstance().onDataType(DT_UINT32); }
	|
	TOKEN_INT16	{ TalkyParser::getInstance().onDataType(DT_INT16); }
	|
	TOKEN_UINT16 { TalkyParser::getInstance().onDataType(DT_UINT16); }
	|
	TOKEN_INT8	{ TalkyParser::getInstance().onDataType(DT_INT8); }
	|
	TOKEN_UINT8	{ TalkyParser::getInstance().onDataType(DT_UINT8); }
	|
	TOKEN_BOOL	{ TalkyParser::getInstance().onDataType(DT_BOOL); }
	|
	TOKEN_STRING { TalkyParser::getInstance().onDataType(DT_STRING); }
	;

user_array_type:
	TOKEN_ARRAY '[' user_type ']'
	{
		TalkyParser::getInstance().onNewUserArray($3);
	}
	;
	

primitive_array_type:
	TOKEN_ARRAY '[' basic_type ']'
	{
		TalkyParser::getInstance().onNewPrimitiveArray($3);
	}
	;

byte_array_type:
	TOKEN_BYTES
	{
		TalkyParser::getInstance().onNewByteArray();	
	}
	;

%%
