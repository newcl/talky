#ifndef __java_code_generator__
#define __java_code_generator__

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/replace.hpp>

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
#include "assert.h"
#include "code_generator.h"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

class JavaCodeGenerator : public CodeGenerator {
public:
    JavaCodeGenerator(){}

    string getTypeName(TypeDeclaration& declaration);

    string getPrimitiveTypeName(DataType dataType);

    void serializeField(ofstream& ofs, TypeDeclaration& theField);

    void deserializeField(ofstream& ofs, TypeDeclaration& theField);

    string getParamListString(Function* function);

    string getParamNameListString(Function* function);

    void generate(TalkyUnit* unit, string path);
};


#endif