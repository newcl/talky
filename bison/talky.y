%{
#include <cstdio>
#include <iostream>
using namespace std;
// what bison needs to know from flex
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;
void yyerror(const char* s);

%}
// used to represent any possible data structure 
// returned by flex, defaults to int for yystype
%union {
	int ival;
	float fval;
	char* sval;
}

%token <ival> INT;
%token <fval> FLOAT;
%token <sval> STRING;

%%
talky:
	INT talky		{cout << "bison found integer:" << $1 << endl;}
	| FLOAT talky	{cout << "bison found float:" << $1 << endl;}
	| STRING talky	{cout << "bison found string:" << $1 << endl;}
	| INT			{cout << "bison found integer2:" << $1 << endl;}
	| FLOAT 		{cout << "bison found float2:" << $1 << endl;}
	| STRING 		{cout << "bison found string2:" << $1 << endl;}
	;

%%
int main(int argc, char** argv){
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

	yylex();
}

void yyerror(const char* s){
	cerr << "parse error " << s << endl;
	exit(-1);
}