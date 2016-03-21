/* part 1 control information */

%{
#include <iostream>
using namespace std;
/* disable name mangling for g++ */
#define YY_DECL extern "C" int yylex()
%}

%%
	/* <--- this tab is essential part 2 flex grammer */
[\t\n ]*			;
[0-9]*\.[0-9]+		{cout << "Found float point number:" << yytext << endl;}
[0-9]+				{cout << "Found integer:" << yytext << endl;}
[a-zA-Z0-9]+		{cout << "Found string:" << yytext << endl;}
.					{cout << "unrecognized:" << yytext << endl;}

%%

/* part 3 code */
int main(int argc, char** argv){
	yylex();
}

/*
for more info about flex and bison, please refer to this article:
http://aquamentus.com/flex_bison.html
*/