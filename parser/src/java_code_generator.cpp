#include <iostream>
#include <fstream>

#include "../inc/java_code_generator.h"
#include "../inc/util.h"

string JavaCodeGenerator::getTypeName(TypeDeclaration& declaration) {
    DeclarationType declarationType = declaration.declarationType;
    if (declarationType == DLT_PRIMITIVE) {
        DataType dataType = declaration.dataType;
        return getPrimitiveTypeName(dataType);
    } else if (declarationType == DLT_USER) {
        return declaration.userTypeDefinition->name;
    } else if (declarationType == DLT_ARRAY) {
        if (declaration.userTypeDefinition == NULL) {
            return getPrimitiveTypeName(declaration.dataType) + "[]";
        } else {
            return declaration.userTypeDefinition->name + "[]";
        }
    } else if (declarationType == DLT_BYTE_ARRAY) {
        return "byte[]";
    }

    return "---------";
}

string JavaCodeGenerator::getPrimitiveTypeName(DataType dataType) {
    if (dataType == DT_INT64
            || dataType == DT_UINT64) {
        return "long";
    } else if (dataType == DT_DOUBLE) {
        return "double";
    } else if (dataType == DT_FLOAT) {
        return "float";
    } else if (dataType == DT_INT32) {
        return "int";
    } else if (dataType == DT_UINT32) {
        return "int";
    } else if (dataType == DT_INT16) {
        return "short";
    } else if (dataType == DT_UINT16) {
        return "short";
    } else if (dataType == DT_INT8) {
        return "byte";
    } else if (dataType == DT_UINT8) {
        return "byte";
    } else if (dataType == DT_BOOL) {
        return "boolean";
    } else if (dataType == DT_STRING) {
        return "String";
    }

    return "unknown primitive type " + __ITOA(dataType);
}

void JavaCodeGenerator::serializeField(ofstream& ofs, TypeDeclaration& theField) {
    if (theField.declarationType == DLT_ARRAY) {
        ofs << "SerializationUtil.writeVariableLength(dos, " + theField.name + ".length);" << endl;
        if (theField.userTypeDefinition == NULL) {

            ofs << "for(int i=0; i < " + theField.name + ".length;i++){" << endl;
            if (theField.dataType == DT_INT64)
                ofs << "dos.writeLong(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_UINT64)
                ofs << "dos.writeLong(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_DOUBLE)
                ofs << "dos.writeDouble(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_FLOAT)
                ofs << "dos.writeFloat(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_INT32)
                ofs << "dos.writeInt(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_UINT32)
                ofs << "dos.writeInt(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_INT16)
                ofs << "dos.writeShort(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_UINT16)
                ofs << "dos.writeShort(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_INT8)
                ofs << "dos.writeByte(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_BOOL)
                ofs << "dos.writeBoolean(" + theField.name + "[i]);" << endl;
            else if (theField.dataType == DT_STRING)
                ofs << "dos.writeUTF(" + theField.name + "[i]);" << endl;

            ofs << "}" << endl;
        } else {
            ofs << "for(int i=0; i < " + theField.name + ".length;i++){" << endl;
            ofs << theField.name + "[i].serialize(dos);" << endl;
            ofs << "}" << endl;
        }

    } else if (theField.declarationType == DLT_USER) {
        ofs << theField.name + ".serialize(dos);" << endl;
    } else if (theField.declarationType == DLT_PRIMITIVE) {
        if (theField.dataType == DT_INT64)
            ofs << "dos.writeLong(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_UINT64)
            ofs << "dos.writeLong(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_DOUBLE)
            ofs << "dos.writeDouble(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_FLOAT)
            ofs << "dos.writeFloat(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_INT32)
            ofs << "dos.writeInt(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_UINT32)
            ofs << "dos.writeInt(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_INT16)
            ofs << "dos.writeShort(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_UINT16)
            ofs << "dos.writeShort(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_INT8)
            ofs << "dos.writeByte(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_BOOL)
            ofs << "dos.writeBoolean(" + theField.name + ");" << endl;
        else if (theField.dataType == DT_STRING)
            ofs << "dos.writeUTF(" + theField.name + ");" << endl;
    } else if (theField.declarationType == DLT_BYTE_ARRAY) {
        ofs << "SerializationUtil.writeVariableLength(dos, " + theField.name + ".length);" << endl;
        ofs << "dos.write(" + theField.name + ");" << endl;
    }
}

void JavaCodeGenerator::deserializeField(ofstream& ofs, TypeDeclaration& theField) {

    if (theField.declarationType == DLT_ARRAY) {
        string arrayLength = nextParamName();
        ofs << "int " + arrayLength + " = SerializationUtil.readVariableLength(dis);" << endl;
        if (theField.userTypeDefinition == NULL) {
            ofs << theField.name + " = new " + getPrimitiveTypeName(theField.dataType) + "[" + arrayLength + "];" << endl;
            ofs << "for(int i=0; i < " + arrayLength + ";i++){" << endl;
            if (theField.dataType == DT_INT64)
                ofs << theField.name + "[i] = dis.readLong();" << endl;
            else if (theField.dataType == DT_UINT64)
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
            else if (theField.dataType == DT_BOOL)
                ofs << theField.name + "[i] = dis.readBoolean();" << endl;
            else if (theField.dataType == DT_STRING)
                ofs << theField.name + "[i] = dis.readUTF();" << endl;

            ofs << "}" << endl;
        } else {
            ofs << theField.name + " = new " + theField.userTypeDefinition->name + "[" + arrayLength + "];" << endl;
            ofs << "for(int i=0; i < " + theField.name + ".length;i++){" << endl;
            ofs << theField.name + "[i] = new " << theField.userTypeDefinition->name << "();" << endl;
            ofs << theField.name + "[i].deserialize(dis);" << endl;
            ofs << "}" << endl;
        }

    } else if (theField.declarationType == DLT_USER) {
        ofs << theField.name + " = new " << theField.userTypeDefinition->name << "();" << endl;
        ofs << theField.name + ".deserialize(dis);" << endl;
    } else if (theField.declarationType == DLT_PRIMITIVE) {
        if (theField.dataType == DT_INT64)
            ofs << theField.name + " = dis.readLong();" << endl;
        else if (theField.dataType == DT_UINT64)
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
        else if (theField.dataType == DT_BOOL)
            ofs << theField.name + " = dis.readBoolean();" << endl;
        else if (theField.dataType == DT_STRING)
            ofs << theField.name + " = dis.readUTF();" << endl;
    } else if (theField.declarationType == DLT_BYTE_ARRAY) {
        string arrayLength = nextParamName();
        ofs << "int " + arrayLength + " = SerializationUtil.readVariableLength(dis);" << endl;
        ofs << theField.name + " = new byte[" + arrayLength + "];";
        ofs << "dos.read(" + theField.name + ");" << endl;
    }
}

string JavaCodeGenerator::getParamListString(Function* function) {
    ostringstream ss;
    for (int i = 0; i < function->params.size(); i++) {
        string typeName = getTypeName(*(function->params[i]));
        ss << typeName << " " << (*(function->params[i])).name;
        if (i < function->params.size() - 1) {
            ss << ",";
        }
    }

    return ss.str();
}

string JavaCodeGenerator::getParamNameListString(Function* function) {
    ostringstream ss;
    for (int i = 0; i < function->params.size(); i++) {
        string typeName = getTypeName(*(function->params[i]));
        ss << (*(function->params[i])).name;
        if (i < function->params.size() - 1) {
            ss << ",";
        }
    }

    return ss.str();
}

void JavaCodeGenerator::generate(TalkyUnit* unit, string path) {
    fs::path dir(path);
    //package
    if (unit->currentPackage != "") {
        string packagePath = unit->currentPackage;
        // std::replace(packagePath.begin(), packagePath.end(), ".", "/");
        boost::replace_all(packagePath, ".", "/");
        dir += "/" + packagePath;
        cout << "final path:" << dir << endl;
        boost::filesystem::create_directories(dir);
    }
    if (!fs::exists(dir)) {
        cout << "java generator output dir does not exist:" << dir << endl;
        exit(-1);
    }

    dir = fs::canonical(dir);
    path = dir.native();

    cout << "generating java source to:" << path << endl;

    map<string, Definition*>& definitions = unit->definitions;

    for ( map<string, Definition*>::iterator it = definitions.begin(); it != definitions.end(); ++it ) {
        Definition* definition = it->second;
        string name = definition->name;
        DefinitionType type = definition->getType();
        if (type == DFT_ENUM) {
            ofstream ofs(path + "/" + name + ".java");
            if (unit->currentPackage != "") {
                ofs << "package " << unit->currentPackage << ";" << endl;
            }
            ofs << "public class " << name << "{" << endl;

            Enum& theEnum = *dynamic_cast<Enum*>(definition);

            for (int i = 0; i < theEnum.members.size(); i++) {
                ofs << "public final static int " << theEnum.members[i] << "=" << i << ";" << endl;
            }

            ofs << "public final static int MAX_VALUE=" << theEnum.members.size() << ";" << endl;

            ofs << "public static String toString(byte value){" << endl;
            for (int i = 0; i < theEnum.members.size(); i++) {
                ofs << "if(value == " << theEnum.members[i] << "){" << endl;
                ofs << "return \"" << theEnum.members[i] << "\";" << endl;
                ofs << "}" << endl;
            }
            ofs << "return null;" << endl;

            ofs << "}" << endl;

            ofs << "public static int toValue(String name){" << endl;
            for (int i = 0; i < theEnum.members.size(); i++) {
                ofs << "if(name.equals(\"" << theEnum.members[i] << "\")){" << endl;
                ofs << "return " << theEnum.members[i] << ";" << endl;
                ofs << "}" << endl;
            }
            ofs << "return -1;" << endl;

            ofs << "}" << endl;

            ofs << "}" << endl;
            ofs.close();
        } else if (type == DFT_STRUCTURE) {
            ofstream ofs(path + "/" + name + ".java");
            if (unit->currentPackage != "") {
                ofs << "package " << unit->currentPackage << ";" << endl;
            }
            ofs << "import java.io.*;" << endl;
            ofs << "import info.chenliang.talky.*;" << endl;
            ofs << "public class " << name << "{" << endl;

            Structure& theStructure = *dynamic_cast<Structure*>(definition);
            std::vector<TypeDeclaration*>& fields = theStructure.members;
            for (int i = 0; i < fields.size(); i++) {
                TypeDeclaration& theField = *fields[i];
                string dataTypeName = getTypeName(theField);
                ofs << "public " << dataTypeName << " " << theField.name << ";" << endl;
            }

            //serializer
            ofs << "public void serialize(DataOutputStream dos) throws Exception{" << endl;

            //mark fields that need serialization
            int fieldMarkSize = (fields.size() + 7) / 8;
            ofs << "FieldMark fm = new FieldMark(" << fieldMarkSize << ");" << endl;
            for (int i = 0; i < fields.size(); i++) {
                TypeDeclaration& theField = *fields[i];
                if (theField.declarationType == DLT_ARRAY
                        || theField.declarationType == DLT_BYTE_ARRAY) {
                    //fm.mark(name == null || name.length == 0 ? false : true);
                    ofs << "fm.mark(" << theField.name << " != null && " << theField.name << ".length > 0);" << endl;
                } else if (theField.declarationType == DLT_USER) {
                    ofs << "fm.mark(true);" << endl;
                } else if (theField.declarationType == DLT_PRIMITIVE) {
                    if (theField.dataType == DT_INT64
                            || theField.dataType == DT_UINT64
                            || theField.dataType == DT_DOUBLE
                            || theField.dataType == DT_FLOAT
                            || theField.dataType == DT_INT32
                            || theField.dataType == DT_UINT32
                            || theField.dataType == DT_INT16
                            || theField.dataType == DT_UINT16
                            || theField.dataType == DT_INT8) {
                        ofs << "fm.mark(" << theField.name << " != 0);" << endl;
                    } else if (theField.dataType == DT_BOOL) {
                        ofs << "fm.mark(true);" << endl;
                    } else if (theField.dataType == DT_STRING) {
                        ofs << "fm.mark(" << theField.name << " != null && " << theField.name << ".length() > 0);" << endl;
                    }
                }
            }
            // serialize the field mark
            ofs << "dos.write(fm.getData());" << endl;
            //actual serilization code
            for (int i = 0; i < fields.size(); i++) {
                TypeDeclaration& theField = *fields[i];
                ofs << "if(fm.isMarked(" + __ITOA(i) + ")){" << endl;
                serializeField(ofs, theField);
                ofs << "}" << endl;
            }

            // ofs << "}" << endl;
            ofs << "}" << endl;

            //deserializer
            ofs << "public void deserialize(DataInputStream dis) throws Exception{" << endl;
            ofs << "FieldMark fm = new FieldMark(" << fieldMarkSize << ");" << endl;
            ofs << "dis.read(fm.getData());" << endl;
            for (int i = 0; i < fields.size(); i++) {
                TypeDeclaration& theField = *fields[i];
                ofs << "if(fm.readMark()){" << endl;
                deserializeField(ofs, theField);
                ofs << "}" << endl;
            }
            ofs << "}" << endl;

            ofs << "}" << endl;
            ofs.close();
        } else if (type == DFT_INTERFACE) {
            Interface& theInterface = *dynamic_cast<Interface*>(definition);
            // 1. proxy class
            ofstream ofs(path + "/" + name + "Proxy" + ".java");
            if (unit->currentPackage != "") {
                ofs << "package " << unit->currentPackage << ";" << endl;
            }
            ofs << "import java.io.*;" << endl;
            ofs << "import info.chenliang.talky.*;" << endl;
            ofs << "public abstract class " + name + "Proxy {" << endl;
            for (int i = 0; i < theInterface.functions.size(); i++) {
                ofs << "public abstract void " + theInterface.functions[i]->name + "(" + getParamListString(theInterface.functions[i]) + ");" << endl;
            }
            ofs << "}" << endl;
            ofs.close();


            // 2. stub
            ofs.open(path + "/" + name + "Stub" + ".java");
            if (unit->currentPackage != "") {
                ofs << "package " << unit->currentPackage << ";" << endl;
            }
            ofs << "import java.io.*;" << endl;
            ofs << "import info.chenliang.talky.*;" << endl;
            ofs << "public abstract class " + name + "Stub {" << endl;
            ofs << "protected abstract DataOutputStream begin();" << endl;
            ofs << "protected abstract void end();" << endl;

            for (int i = 0; i < theInterface.functions.size(); i++) {
                ofs << "public void " + theInterface.functions[i]->name + "(" + getParamListString(theInterface.functions[i]) + ") throws Exception{" << endl;
                ofs << "DataOutputStream dos = begin();" << endl;
                ofs << "dos.write(" << i << ");" << endl;
                for (int j = 0; j < theInterface.functions[i]->params.size(); j++) {
                    serializeField(ofs, *(theInterface.functions[i]->params[j]));
                }

                ofs << "end();" << endl;
                ofs << "}" << endl;
            }
            ofs << "}" << endl;
            ofs.close();

            // 3. dispatcher
            ofs.open(path + "/" + name + "Dispatcher" + ".java");
            if (unit->currentPackage != "") {
                ofs << "package " << unit->currentPackage << ";" << endl;
            }
            ofs << "import java.io.*;" << endl;
            ofs << "import info.chenliang.talky.*;" << endl;
            ofs << "public class " + name + "Dispatcher {" << endl;
            // 1. dispatcher method
            ofs << "public static void dispatch(DataInputStream dis, " + name + "Proxy proxy) throws Exception{" << endl;
            ofs << "int fid = (int)(dis.read()&0xFFFF);" << endl;
            ofs << "switch(fid)" << endl;
            ofs << "{" << endl;
            for (int i = 0; i < theInterface.functions.size(); i++) {
                ofs << "case " + __ITOA(i) + ":" << endl;
                ofs << "{" << endl;
                ofs << theInterface.functions[i]->name << "(dis, proxy);" << endl;
                ofs << "}" << endl;
                ofs << "break;" << endl;
            }
            ofs << "}" << endl; // switch
            ofs << "}" << endl; // dispatch method
            // 2. deserialize param and call proxy
            for (int i = 0; i < theInterface.functions.size(); i++) {
                ofs << "protected static void " + theInterface.functions[i]->name + "(DataInputStream dis, " + name + "Proxy proxy) throws Exception{" << endl;
                for (int j = 0; j < theInterface.functions[i]->params.size(); j++) {
                    string typeName = getTypeName(*theInterface.functions[i]->params[j]);
                    ofs << typeName << " " << theInterface.functions[i]->params[j]->name << ";" << endl;
                }
                for (int j = 0; j < theInterface.functions[i]->params.size(); j++) {
                    deserializeField(ofs, *theInterface.functions[i]->params[j]);
                }

                //make the call
                ofs << "proxy." << theInterface.functions[i]->name << "(" + getParamNameListString(theInterface.functions[i]) + ");" << endl;

                ofs << "}" << endl;
            }
            ofs << "}" << endl;
            ofs.close();

        }


    }


}