/* part 1 control information */

%{
#include <iostream>
#include "../bison/talky.tab.h"
using namespace std;
/* disable name mangling for g++ */
#define YY_DECL extern "C" int yylex()
int linenum = 0;
%}

%%
	//part 2 flex grammer */
[\t\n ]*			;
[0-9]*\.[0-9]+		{ yylval.fval = atof(yytext); return FLOAT;}
[0-9]+				{ yylval.ival = atoi(yytext); return INT;}
[a-zA-Z0-9]+		{
						// yytext may change, make a hard copy
						yylval.sval = strdup(yytext);
						return STRING;
					}
.					{cout << "unrecognized:" << yytext << endl;}
%%

/* part 3 code */
//moved to bison file ../bison/talky.y

/*
for more info about flex and bison, please refer to this article:
http://aquamentus.com/flex_bison.html
*/