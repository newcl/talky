

#ifndef __main_h__
#define __main_h__

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
#include "declaration_type.h"
#include "code_generator.h"
#include "data_type.h"
#include "definition_type.h"
#include "definition.h"
#include "enum.h"
#include "type_declaration.h"
#include "structure.h"
#include "function.h"
#include "interface.h"
#include "talky_unit.h"
#include "talky_parser.h"
#include "java_code_generator.h"
#include "assert.h"

using namespace std;

extern "C" {
	int yyparse ();
}



string dataTypeToString(DataType dataType);
DataType stringToDataType(string name);

#endif