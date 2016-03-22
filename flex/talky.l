/* part 1 control information */

%{
#define YYDEBUG 1
#include <iostream>
using namespace std;
#define YYSTYPE std::string


#include "../parser/inc/parser.h"
#include "../bison/talky.tab.h"

/* disable name mangling for g++ */
#define YY_DECL extern "C" int yylex()
%}

NEWLINE					[\r?\n]

%%
enum            {
					return TOKEN_ENUM;
				}

struct			{
					return TOKEN_STRUCT;
				}

interface		{
					return TOKEN_INTERFACE;
				}

int64			{
					return TOKEN_INT64;
				}

uint64			{
					return TOKEN_UINT64;
				}

double			{
					return TOKEN_DOUBLE;
				}

float			{
					return TOKEN_FLOAT;
				}

int32			{
					return TOKEN_INT32;
				}

uint32			{
					return TOKEN_UINT32;
				}

int16			{
					return TOKEN_INT16;
				}

uint16			{
					return TOKEN_UINT16;
				}

int8			{
					return TOKEN_INT8;
				}

uint8			{
					return TOKEN_UINT8;
				}

bool			{
					return TOKEN_BOOL;
				}

string			{
					return TOKEN_STRING;
				}

array			{
					return TOKEN_ARRAY;
				}

bytes			{
					return TOKEN_BYTES;
				}

[a-ij-rs-zA-IJ-RS-Z_][a-ij-rs-zA-IJ-RS-Z0-9_]* {
					yylval = std::string( yytext, yyleng );
					return TOKEN_IDENTIFIER;
				}
[ \t]*
				{

				}
\/\/.*{NEWLINE} {
					Parser::getInstance().onNewLine();
                }
"/*"			{
					for(;;) {
						char const c = yyinput();
						//cout << "reading " << c << endl; 
						if (c == '*') {
							char const next = yyinput();
							if (next == '/')
								break;
							else
								unput(next);
						}
						else if (c == '\n') {
							Parser::getInstance().onNewLine();
						}
					}
				}
{NEWLINE}		{
					Parser::getInstance().onNewLine();
				}
.				{
					return yytext[0];
				}

%%
/* part 3 code */