#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>
using namespace std;

extern "C" {
	int yyparse ();
}

inline void _assert(int v){
    
}

enum DeclarationType {
    DLT_PRIMITIVE,
    DLT_USER,
    DLT_ARRAY,
    DLT_BYTE_ARRAY,
};

enum DataType
{
    DT_INT64,	///< 8 bytes
    DT_UINT64,	///< 8 bytes.
    DT_DOUBLE,	///< 8 bytes.
    DT_FLOAT,	///< 4 bytes
    DT_INT32,	///< 4 bytes
    DT_UINT32,	///< 4 bytes
    DT_INT16,	///< 2 bytes
    DT_UINT16,	///< 2 bytes
    DT_INT8,	///< 1 bytes
    DT_UINT8,	///< 1 bytes
    DT_BOOL,	///< 1 bytes
    DT_ENUM,	///< 1 bytes
    DT_STRING,	///< len * 1 bytes.
    DT_UNKNOWN
};

string dataTypeToString(DataType dataType);
DataType stringToDataType(string name);

enum DefinitionType {
    DFT_ENUM,
    DFT_STRUCTURE,
    DFT_INTERFACE
};

class Definition{
public:
    std::string name;
    Definition(string name){
        this->name = name;
    }
    virtual ~Definition(){}
    void onDone(){
    }
    
    virtual DefinitionType getType()=0;
};

class Enum : public Definition {
public:
    Enum(string name):
    Definition(name){
    }
    
    void onNewMember(string name){
        _assert(std::find(members.begin(), members.end(), name) == members.end());
        members.push_back(name);
    }
    DefinitionType getType(){
        return DFT_ENUM;
    }
    std::vector<string> members;
};


class TypeDeclaration {
public:
    DeclarationType declarationType;
    DataType dataType;
    string name;
    Definition* userTypeDefinition;
    
    TypeDeclaration(DeclarationType theDeclarationType,
                    DataType theDataType,
                    string theName,
                    Definition* definition):
    declarationType(theDeclarationType),
    dataType(theDataType),
    name(theName),
    userTypeDefinition(definition){
    }
};


class Structure : public Definition {
public:
    Structure(string name):
    Definition(name){
        
    }
    
    void onNewMember(TypeDeclaration* td){
        members.push_back(td);
    }
    
    DefinitionType getType(){
        return DFT_STRUCTURE;
    }
    std::vector<TypeDeclaration*> members;
};


class Function {
public:
    Function(string functionName):
    name(functionName)
    {
        
    }
    
    void addParam(TypeDeclaration* td){
        params.push_back(td);
    }
    
    std::vector<TypeDeclaration*> params;
    string name;
    
};

class Interface : public Definition {
public:
    Interface(string name):
    Definition(name){
        
    }
    Function* onMemberFunction(string name){
        Function* function = new Function(name);
        functions.push_back(function);
        
        return function;
    }
    
    DefinitionType getType(){
        return DFT_INTERFACE;
    }
    
    Function* getFunction(string name){
        for(int i=0; i < functions.size(); i++){
            if(!functions[i]->name.compare(name)){
                return functions[i];
            }
        }
        return NULL;
    }
    
    std::vector<Function*> functions;
};

class Parser{
public:
    static Parser& getInstance();
    Parser():
    currentDefinition(NULL),
    userTypeDefinition(NULL),
    lineNumber(0){
        
    }
    
    void onNewEnum(const std::string name){
        cout << "new enum " << name << endl;
        currentDefinition = new Enum(name);
        definitions[name] = currentDefinition;
    }
    void onEnumMember(const std::string name){
        cout << "new enum member " << name << endl;
        Enum* theEnum = dynamic_cast<Enum*> (currentDefinition);
        theEnum->onNewMember(name);
    }
    void onEnumDone(string name){
        currentDefinition->onDone();
    }
    void onNewStructure(const std::string name){
        cout << "new structure " << name << endl;
        currentDefinition = new Structure(name);
        definitions[name] = currentDefinition;
    }
    void onStructureMember(const std::string name){
        cout << "new structure member " << name << endl;
        TypeDeclaration* td = new TypeDeclaration(currentDeclarationType, currentDataType, name, userTypeDefinition);
        Structure* theStructure = dynamic_cast<Structure*> (currentDefinition);
        theStructure->onNewMember(td);
    }
    void onStructureDone(const std::string name){
        cout << "new structure done" << name << endl;
        currentDefinition->onDone();
    }
    void onNewInterface(const std::string name){
        cout << "new interface " << name << endl;
        currentDefinition = new Interface(name);
        definitions[name] = currentDefinition;
    }
    void onMemberFunction(const std::string name){
        cout << "new member function " << name << endl;
        Interface* theInterface = dynamic_cast<Interface*> (currentDefinition);
        Function& function = *theInterface->onMemberFunction(name);
        for(int i=0; i < currentFunctionParams.size();i++){
            function.addParam(currentFunctionParams[i]);
        }
        
        currentFunctionParams.clear();
    }
    void onFunctionParam(const std::string paramName){
        Interface* theInterface = dynamic_cast<Interface*> (currentDefinition);
        //Function& function = *theInterface->getFunction(currentFunction);
        TypeDeclaration* td = new TypeDeclaration(currentDeclarationType, currentDataType, paramName, userTypeDefinition);
        currentFunctionParams.push_back(td);
        //function.addParam(td);
        cout << "new function param " << paramName << endl;
    }
    void onNewInterfaceDone(const std::string interfaceName){
        cout << "new interface done" << interfaceName << endl;
    }
    void onDataType(DataType dataType){
        cout << "data type " << dataType << endl;
        currentDeclarationType = DLT_PRIMITIVE;
        currentDataType = dataType;
    }
    void onNewLine(){
        
    }
    void onImport(string importFile){
        
    }
    void onUserDataType(string name){
        Definition* definition = getDefinition(name);
        currentDeclarationType = DLT_USER;
        userTypeDefinition = definition;
    }
    void onNewUserArray(string name){
        Definition* definition = getDefinition(name);
        currentDeclarationType = DLT_ARRAY;
        userTypeDefinition = definition;
    }
    void onNewPrimitiveArray(string name){
        DataType dataType = stringToDataType(name);
        currentDeclarationType = DLT_ARRAY;
        currentDataType = dataType;
        userTypeDefinition = NULL;
    }
    void onNewByteArray(){}
    Definition* getDefinition(const std::string name){
        if(definitions.count(name)){
            return definitions[name];
        }
        return NULL;
    }
    
    DeclarationType currentDeclarationType;
    Definition* currentDefinition;
    std::string currentFile;
    DataType currentDataType;
    map<string, Definition*> definitions;
    Definition* userTypeDefinition;
    string currentFunction;
    vector<TypeDeclaration*> currentFunctionParams;
    int lineNumber;
    
};

class CodeGenerator {
public:
    virtual void generate(map<string, Definition*>& definitions, string path){}
};

class JavaCodeGenerator : public CodeGenerator {
    string getTypeName(TypeDeclaration& declaration){
        DeclarationType declarationType = declaration.declarationType;
        if(declarationType == DLT_PRIMITIVE){
            DataType dataType = declaration.dataType;
            return getPrimitiveTypeName(dataType);
        } else if(declarationType == DLT_USER){
            return declaration.userTypeDefinition->name;
        } else if(declarationType == DLT_ARRAY){
            if(declaration.userTypeDefinition == NULL){
                return getPrimitiveTypeName(declaration.dataType) + "[]";
            }else{
                return declaration.userTypeDefinition->name + "[]";
            }
        } else if(declarationType == DLT_BYTE_ARRAY){
            return "byte[]";
        }
        
        return "---------";
    }
    
    string getPrimitiveTypeName(DataType dataType){
        if(dataType == DT_INT64
           || dataType == DT_UINT64){
            return "long";
        } else if(dataType == DT_DOUBLE){
            return "double";
        } else if(dataType == DT_FLOAT){
            return "float";
        } else if(dataType == DT_INT32){
            return "int";
        } else if(dataType == DT_UINT32){
            return "int";
        } else if(dataType == DT_INT16){
            return "short";
        } else if(dataType == DT_UINT16){
            return "short";
        } else if(dataType == DT_INT8){
            return "byte";
        } else if(dataType == DT_UINT8){
            return "byte";
        } else if(dataType == DT_BOOL){
            return "boolean";
        } else if(dataType == DT_STRING){
            return "String";
        }
        
        return "unknown primitive type " + itoa(dataType);
    }

    string itoa(int i){
		ostringstream oss;
        oss << i;
        return oss.str();
    }
    
    void serializeField(ofstream& ofs, TypeDeclaration& theField){
        if(theField.declarationType == DLT_ARRAY){
            ofs << "SerializeUtil.writeVariableLength(dos, " + theField.name + ".length);" << endl;
            if(theField.userTypeDefinition == NULL){
                
                ofs << "for(int i=0; i < "+theField.name+".length;i++){" << endl;
                if(theField.dataType == DT_INT64)
                    ofs << "dos.writeLong("+theField.name+"[i]);" << endl;
                else if(theField.dataType == DT_UINT64)
                    ofs << "dos.writeLong("+theField.name+"[i]);" << endl;
                else if (theField.dataType == DT_DOUBLE)
                    ofs << "dos.writeDouble("+theField.name+"[]);" << endl;
                else if (theField.dataType == DT_FLOAT)
                    ofs << "dos.writeFloat("+theField.name+"[]);" << endl;
                else if (theField.dataType == DT_INT32)
                    ofs << "dos.writeInt("+theField.name+"[]);" << endl;
                else if (theField.dataType == DT_UINT32)
                    ofs << "dos.writeInt("+theField.name+"[]);" << endl;
                else if (theField.dataType == DT_INT16)
                    ofs << "dos.writeShort("+theField.name+"[]);" << endl;
                else if (theField.dataType == DT_UINT16)
                    ofs << "dos.writeShort("+theField.name+"[]);" << endl;
                else if (theField.dataType == DT_INT8)
                    ofs << "dos.writeByte("+theField.name+"[]);" << endl;
                else if(theField.dataType == DT_BOOL)
                    ofs << "dos.writeBoolean("+theField.name+"[]);" << endl;
                else if(theField.dataType == DT_STRING)
                    ofs << "dos.writeUTF("+theField.name+"[]);" << endl;
                
                ofs << "}" << endl;
            }else{
                ofs << "for(int i=0; i < "+theField.name+".length;i++){" << endl;
                ofs << theField.name + "[i].serialize(dos);" << endl;
                ofs << "}" << endl;
            }
            
	    			} else if(theField.declarationType == DLT_USER){
                        ofs << theField.name + ".serialize(dos);" << endl;
                    } else if(theField.declarationType == DLT_PRIMITIVE){
                        if(theField.dataType == DT_INT64)
                            ofs << "dos.writeLong("+theField.name+");" << endl;
                        else if(theField.dataType == DT_UINT64)
                            ofs << "dos.writeLong("+theField.name+");" << endl;
                        else if (theField.dataType == DT_DOUBLE)
                            ofs << "dos.writeDouble("+theField.name+");" << endl;
                        else if (theField.dataType == DT_FLOAT)
                            ofs << "dos.writeFloat("+theField.name+");" << endl;
                        else if (theField.dataType == DT_INT32)
                            ofs << "dos.writeInt("+theField.name+");" << endl;
                        else if (theField.dataType == DT_UINT32)
                            ofs << "dos.writeInt("+theField.name+");" << endl;
                        else if (theField.dataType == DT_INT16)
                            ofs << "dos.writeShort("+theField.name+");" << endl;
                        else if (theField.dataType == DT_UINT16)
                            ofs << "dos.writeShort("+theField.name+");" << endl;
                        else if (theField.dataType == DT_INT8)
                            ofs << "dos.writeByte("+theField.name+");" << endl;
                        else if(theField.dataType == DT_BOOL)
                            ofs << "dos.writeBoolean("+theField.name+");" << endl;
                        else if(theField.dataType == DT_STRING)
                            ofs << "dos.writeUTF("+theField.name+");" << endl;
                    }else if(theField.declarationType == DLT_BYTE_ARRAY){
                        ofs << "SerializeUtil.writeVariableLength(dos, " + theField.name + ".length);" << endl;
                        ofs << "dos.write(" + theField.name + ");" << endl;
                    }
    }

    string nextParamName(){
    	static int index = 0;
    	return "__" + itoa((index++)) + "__";
    }

    void deserializeField(ofstream& ofs, TypeDeclaration& theField){

        if(theField.declarationType == DLT_ARRAY){
        	string arrayLength = nextParamName();
            ofs << "int " + arrayLength + " = SerializeUtil.readVariableLength(dis);" << endl;
            if(theField.userTypeDefinition == NULL){
            	ofs << theField.name + " = new " + getPrimitiveTypeName(theField.dataType) + "["+arrayLength+"];" << endl;
                ofs << "for(int i=0; i < "+arrayLength+";i++){" << endl;
                if(theField.dataType == DT_INT64)
                    ofs << theField.name + "[i] = dis.readLong();" << endl;
                else if(theField.dataType == DT_UINT64)
                    ofs << theField.name + "[i] = dis.readLong();" << endl;
                else if (theField.dataType == DT_DOUBLE)
                    ofs << theField.name + "[i] = dis.readDouble();" << endl;
                else if (theField.dataType == DT_FLOAT)
                    ofs << theField.name + "[i] = dis.readFloat();" << endl;
                else if (theField.dataType == DT_INT32)
                    ofs << theField.name + "[i] = dis.readInt();" << endl;
                else if (theField.dataType == DT_UINT32)
                    ofs << theField.name + "[i] = dis.readInt();" << endl;
                else if (theField.dataType == DT_INT16)
                    ofs << theField.name + "[i] = dis.readShort();" << endl;
                else if (theField.dataType == DT_UINT16)
                    ofs << theField.name + "[i] = dis.readShort();" << endl;
                else if (theField.dataType == DT_INT8)
                    ofs << theField.name + "[i] = dis.readByte();" << endl;
                else if(theField.dataType == DT_BOOL)
                    ofs << theField.name + "[i] = dis.readBoolean();" << endl;
                else if(theField.dataType == DT_STRING)
                    ofs << theField.name + "[i] = dis.readUTF();" << endl;
                
                ofs << "}" << endl;
            }else{
                ofs << "for(int i=0; i < "+theField.name+".length;i++){" << endl;
                ofs << theField.name + "[i].deserialize(dis);" << endl;
                ofs << "}" << endl;
            }
            
	    			} else if(theField.declarationType == DLT_USER){
                        ofs << theField.name + ".deserialize(dis);" << endl;
                    } else if(theField.declarationType == DLT_PRIMITIVE){
                        if(theField.dataType == DT_INT64)
		                    ofs << theField.name + " = dis.readLong();" << endl;
		                else if(theField.dataType == DT_UINT64)
		                    ofs << theField.name + " = dis.readLong();" << endl;
		                else if (theField.dataType == DT_DOUBLE)
		                    ofs << theField.name + " = dis.readDouble();" << endl;
		                else if (theField.dataType == DT_FLOAT)
		                    ofs << theField.name + " = dis.readFloat();" << endl;
		                else if (theField.dataType == DT_INT32)
		                    ofs << theField.name + " = dis.readInt();" << endl;
		                else if (theField.dataType == DT_UINT32)
		                    ofs << theField.name + " = dis.readInt();" << endl;
		                else if (theField.dataType == DT_INT16)
		                    ofs << theField.name + " = dis.readShort();" << endl;
		                else if (theField.dataType == DT_UINT16)
		                    ofs << theField.name + " = dis.readShort();" << endl;
		                else if (theField.dataType == DT_INT8)
		                    ofs << theField.name + " = dis.readByte();" << endl;
		                else if(theField.dataType == DT_BOOL)
		                    ofs << theField.name + " = dis.readBoolean();" << endl;
		                else if(theField.dataType == DT_STRING)
		                    ofs << theField.name + " = dis.readUTF();" << endl;
                    }else if(theField.declarationType == DLT_BYTE_ARRAY){
                    	string arrayLength = nextParamName();
            			ofs << "int " + arrayLength + " = SerializeUtil.readVariableLength(dis);" << endl;
            			ofs << theField.name + " = new byte["+arrayLength+"];";
                        ofs << "dos.read(" + theField.name + ");" << endl;
                    }
    }
    
    string getParamListString(Function* function){
        ostringstream ss;
        for(int i=0;i < function->params.size();i++){
            string typeName = getTypeName(*(function->params[i]));
            ss << typeName << " " << (*(function->params[i])).name;
            if(i < function->params.size() - 1){
            	ss << ",";
            }
        }

        return ss.str();
    }

    string getParamNameListString(Function* function){
        ostringstream ss;
        for(int i=0;i < function->params.size();i++){
            string typeName = getTypeName(*(function->params[i]));
            ss << (*(function->params[i])).name;
            if(i < function->params.size() - 1){
            	ss << ",";
            }
        }

        return ss.str();
    }
    
    void generate(map<string, Definition*>& definitions, string path){
        
        for( map<string, Definition*>::iterator it = definitions.begin(); it != definitions.end(); ++it ) {
            Definition* definition = it->second;
            string name = definition->name;
            DefinitionType type = definition->getType();
            if(type == DFT_ENUM){
                ofstream ofs(path + "/" + name + ".java");
                ofs << "public class " << name << "{" << endl;
                
                Enum& theEnum = *dynamic_cast<Enum*>(definition);
                
                for(int i=0; i < theEnum.members.size();i++){
                    ofs << "public final static int " << theEnum.members[i] << "=" << i << ";" << endl;
                }
                
                ofs << "public final static int MAX_VALUE=" << theEnum.members.size() << ";" << endl;
                
                ofs << "public static String toString(byte value){" << endl;
                for(int i=0; i < theEnum.members.size();i++){
                    ofs << "if(value == " << theEnum.members[i] << "){" << endl;
                    ofs << "return \"" << theEnum.members[i] << "\";" << endl;
                    ofs << "}" << endl;
                }
                ofs << "return null;" << endl;
                
                ofs << "}" << endl;
                
                ofs << "public static int toValue(String name){" << endl;
                for(int i=0; i < theEnum.members.size();i++){
                    ofs << "if(name.equals(\"" << theEnum.members[i] << "\")){" << endl;
                    ofs << "return " << theEnum.members[i] << ";" << endl;
                    ofs << "}" << endl;
                }
                ofs << "return -1;" << endl;
                
                ofs << "}" << endl;
                
                ofs << "}" << endl;

                ofs << "}" << endl;			
            	ofs.close();
            } else if(type == DFT_STRUCTURE){
                ofstream ofs(path + "/" + name + ".java");
                ofs << "import java.io.*;" << endl;
                ofs << "public class " << name << "{" << endl;
                
                Structure& theStructure = *dynamic_cast<Structure*>(definition);
                std::vector<TypeDeclaration*>& fields = theStructure.members;
                for(int i=0; i < fields.size(); i++){
                    TypeDeclaration& theField = *fields[i];
                    string dataTypeName = getTypeName(theField);
                    ofs << "public " << dataTypeName << " " << theField.name << ";" << endl;
                }
                
                //serializer
                ofs << "public void serialize(DataOutputStream dos) throws Exception{" << endl;
                
                //mark fields that need serialization
                int fieldMarkSize = (fields.size()+7)/8;
                ofs << "FieldMark fm = new FieldMark(" << fieldMarkSize << ");" << endl;
                for(int i=0; i < fields.size(); i++){
                    TypeDeclaration& theField = *fields[i];
                    if(theField.declarationType == DLT_ARRAY
                       ||theField.declarationType == DLT_BYTE_ARRAY){
                        //fm.mark(name == null || name.length == 0 ? false : true);
                        ofs << "fm.mark(" << theField.name << " == null || "<< theField.name << ".length == 0 ? false : true);" << endl;
                    } else if(theField.declarationType == DLT_USER){
                        ofs << "fm.mark(true);" << endl;
                    } else if(theField.declarationType == DLT_PRIMITIVE){
                        if(theField.dataType == DT_INT64 
                           ||theField.dataType == DT_UINT64 
                           ||theField.dataType == DT_DOUBLE 
                           ||theField.dataType == DT_FLOAT 
                           ||theField.dataType == DT_INT32 
                           ||theField.dataType == DT_UINT32 
                           ||theField.dataType == DT_INT16 
                           ||theField.dataType == DT_UINT16 
                           ||theField.dataType == DT_INT8){
                            ofs << "fm.mark(" << theField.name << " == 0);" << endl;
                        }else if(theField.dataType == DT_BOOL){
                            ofs << "fm.mark(true);" << endl;
                        }else if(theField.dataType == DT_STRING){
                            ofs << "fm.mark(" << theField.name << " == null || "<< theField.name << ".length == 0 ? false : true);" << endl;
                        }
                    }
                }	    		
                //actual serilization code
                for(int i=0; i < fields.size(); i++){
                    TypeDeclaration& theField = *fields[i];
                    ofs << "if(fm.isMarked("+itoa(i)+")){" << endl;
                    serializeField(ofs, theField);
                    ofs << "}" << endl;		
                }	 
                
                // ofs << "}" << endl;
                ofs << "}" << endl;			

                //deserializer
                ofs << "public void deserialize(DataInputStream dis) throws Exception{" << endl;
				ofs << "FieldMark fm = new FieldMark(" << fieldMarkSize << ");" << endl;
				ofs << "dis.read(fm.getData());" << endl;
				for(int i=0; i < fields.size(); i++){
                    TypeDeclaration& theField = *fields[i];
                    ofs << "if(fm.readMark()){" << endl;
                    deserializeField(ofs, theField);
                    ofs << "}" << endl;		
                }
                ofs << "}" << endl;		

                ofs << "}" << endl;			
            	ofs.close();
            } else if(type == DFT_INTERFACE){
                Interface& theInterface = *dynamic_cast<Interface*>(definition);
                // 1. proxy class
                ofstream ofs(path + "/" + name + "Proxy" + ".java");
                ofs << "import java.io.*;" << endl;
                ofs << "public abstract class " + name + "Proxy {" << endl;
                for(int i=0; i < theInterface.functions.size();i++){
                    ofs << "public abstract void "+ theInterface.functions[i]->name +"(" + getParamListString(theInterface.functions[i]) + ");"	<< endl;
                }
                ofs << "}" << endl;		
                ofs.close();


                // 2. stub
                ofs.open(path + "/" + name + "Stub" + ".java");
                ofs << "import java.io.*;" << endl;
                ofs << "public abstract class " + name + "Stub {" << endl;
				ofs << "protected abstract DataOutputStream begin();" << endl;
				ofs << "protected abstract void end();" << endl;

                for(int i=0; i < theInterface.functions.size();i++){
                    ofs << "public void "+ theInterface.functions[i]->name +"(" + getParamListString(theInterface.functions[i]) + ") throws Exception{" << endl;	
					ofs << "DataOutputStream dos = begin();" << endl;
                    for(int i=0;i < theInterface.functions[i]->params.size();i++){
                    	serializeField(ofs, *(theInterface.functions[i]->params[i]));
                    }

                    ofs << "end();" << endl;
                    ofs << "}" << endl;
                }
                ofs << "}" << endl;			
                ofs.close();

                // 3. dispatcher
                ofs.open(path + "/" + name + "Dispatcher" + ".java");
                ofs << "import java.io.*;" << endl;
                ofs << "public class " + name + "Dispatcher {" << endl;
                // 1. dispatcher method
                ofs << "public static void dispatch(DataInputStream dis, "+name+"Proxy proxy) throws Exception{" << endl;
				ofs << "int fid = (int)(dis.read()&0xFFFF);"<<endl;
				ofs << "switch(fid)" << endl;
				ofs << "{" << endl;
				for(int i=0; i < theInterface.functions.size();i++){
					ofs << "case " + itoa(i) + ":" << endl;
					ofs << "{" << endl;
					ofs << theInterface.functions[i]->name << "(dis, proxy);" << endl;
					ofs << "}" << endl;
					ofs << "break;" << endl;
                }
				ofs << "}" << endl; // switch
				ofs << "}" << endl; // dispatcher
                // 2. deserialize param and call proxy
                for(int i=0; i < theInterface.functions.size();i++){
                	ofs << "protected static void "+theInterface.functions[i]->name+"(DataInputStream dis, "+name+"Proxy proxy) throws Exception{" << endl;
                	for(int j=0; j<theInterface.functions[i]->params.size();j++){
                		string typeName = getTypeName(*theInterface.functions[i]->params[j]);
                		ofs << typeName << " " << theInterface.functions[i]->params[j]->name << ";" << endl;
                	}
					for(int j=0; j<theInterface.functions[i]->params.size();j++){
                		deserializeField(ofs, *theInterface.functions[i]->params[j]);
                	}

                	//make the call
                	ofs << "proxy." << theInterface.functions[i]->name << "(" + getParamNameListString(theInterface.functions[i]) + ");" << endl;

                	ofs << "}" << endl;
                }
                ofs << "}" << endl;			

                ofs << "}" << endl;			
            	ofs.close();
            	
            }
            
            
        }
        
        
    }
};

#endif