#include "../inc/parser.h"

Parser& Parser::getInstance()
{
	static Parser parser;
	return parser;
}