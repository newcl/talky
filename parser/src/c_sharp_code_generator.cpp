#include <iostream>
#include <fstream>

#include "../inc/c_sharp_code_generator.h"
#include "../inc/util.h"

string CSharpCodeGenerator::getTypeName(TypeDeclaration& declaration) {
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

string CSharpCodeGenerator::getPrimitiveTypeName(DataType dataType) {
    if (dataType == DT_INT64) {
        return "Int64";
        if (dataType == DT_UINT64) {
            return "UInt64";
        } else if (dataType == DT_DOUBLE) {
            return "double";
        } else if (dataType == DT_FLOAT) {
            return "single";
        } else if (dataType == DT_INT32) {
            return "Int32";
        } else if (dataType == DT_UINT32) {
            return "UInt32";
        } else if (dataType == DT_INT16) {
            return "Int16";
        } else if (dataType == DT_UINT16) {
            return "UInt16";
        } else if (dataType == DT_INT8) {
            return "sbyte";
        } else if (dataType == DT_UINT8) {
            return "byte";
        } else if (dataType == DT_BOOL) {
            return "bool";
        } else if (dataType == DT_STRING) {
            return "string";
        }

        return "unknown primitive type " + __ITOA(dataType);
    }

    void CSharpCodeGenerator::writeField(ofstream & ofs, DataType dataType, string fieldName) {
        if (dataType == DT_INT64)
            ofs << "writer.WriteInt64(" + fieldName + ");" << endl;
        else if (dataType == DT_UINT64)
            ofs << "writer.WriteUInt64(" + fieldName + ");" << endl;
        else if (dataType == DT_DOUBLE)
            ofs << "writer.WriteDouble(" + fieldName + ");" << endl;
        else if (dataType == DT_FLOAT)
            ofs << "writer.WriteSingle(" + fieldName + ");" << endl;
        else if (dataType == DT_INT32)
            ofs << "writer.WriteInt32(" + fieldName + ");" << endl;
        else if (dataType == DT_UINT32)
            ofs << "writer.WriteUInt32(" + fieldName + ");" << endl;
        else if (dataType == DT_INT16)
            ofs << "writer.WriteInt16(" + fieldName + ");" << endl;
        else if (dataType == DT_UINT16)
            ofs << "writer.WriteUInt16(" + fieldName + ");" << endl;
        else if (dataType == DT_INT8)
            ofs << "writer.WriteInt8(" + fieldName + ");" << endl;
        else if (dataType == DT_BOOL)
            ofs << "writer.WriteBoolean(" + fieldName + ");" << endl;
        else if (dataType == DT_STRING)
            ofs << "writer.WriteUTF(" + fieldName + ");" << endl;

    }

    void CSharpCodeGenerator::readField(ofstream & ofs, DataType dataType, string fieldName) {
        if (dataType == DT_INT64)
            ofs << fieldName + " = reader.ReadInt64();" << endl;
        else if (dataType == DT_UINT64)
            ofs << fieldName + " = reader.ReadUInt64();" << endl;
        else if (dataType == DT_DOUBLE)
            ofs << fieldName + " = reader.ReadDouble();" << endl;
        else if (dataType == DT_FLOAT)
            ofs << fieldName + " = reader.ReadSingle();" << endl;
        else if (dataType == DT_INT32)
            ofs << fieldName + " = reader.ReadInt32();" << endl;
        else if (dataType == DT_UINT32)
            ofs << fieldName + " = reader.ReadUInt32();" << endl;
        else if (dataType == DT_INT16)
            ofs << fieldName + " = reader.ReadInt16();" << endl;
        else if (dataType == DT_UINT16)
            ofs << fieldName + " = reader.ReadUInt16();" << endl;
        else if (dataType == DT_INT8)
            ofs << fieldName + " = reader.ReadByte();" << endl;
        else if (dataType == DT_BOOL)
            ofs << fieldName + " = reader.ReadBoolean();" << endl;
        else if (dataType == DT_STRING)
            ofs << fieldName + " = reader.ReadUTF();" << endl;

    }

    void CSharpCodeGenerator::serializeField(ofstream & ofs, TypeDeclaration & theField) {
        if (theField.declarationType == DLT_ARRAY) {
            ofs << "SerializationUtil.WriteVariableLength(writer, " + theField.name + ".Length);" << endl;
            if (theField.userTypeDefinition == NULL) {

                ofs << "for(int i=0; i < " + theField.name + ".Length;i++){" << endl;

                writeField(ofs, theField.dataType, theField.name + "[i]");

                ofs << "}" << endl;
            } else {
                ofs << "for(int i=0; i < " + theField.name + ".Length;i++){" << endl;
                ofs << theField.name + "[i].Serialize(writer);" << endl;
                ofs << "}" << endl;
            }

        } else if (theField.declarationType == DLT_USER) {
            ofs << theField.name + ".Serialize(writer);" << endl;
        } else if (theField.declarationType == DLT_PRIMITIVE) {
            writeField(ofs, theField.dataType, theField.name);

        } else if (theField.declarationType == DLT_BYTE_ARRAY) {
            ofs << "SerializationUtil.WriteVariableLength(writer, " + theField.name + ".Length);" << endl;
            ofs << "writer.Write(" + theField.name + ");" << endl;
        }
    }

    void CSharpCodeGenerator::deserializeField(ofstream & ofs, TypeDeclaration & theField) {

        if (theField.declarationType == DLT_ARRAY) {
            string arrayLength = nextParamName();
            ofs << "int " + arrayLength + " = SerializationUtil.ReadVariableLength(reader);" << endl;
            if (theField.userTypeDefinition == NULL) {
                ofs << theField.name + " = new " + getPrimitiveTypeName(theField.dataType) + "[" + arrayLength + "];" << endl;
                ofs << "for(int i=0; i < " + arrayLength + ";i++){" << endl;

                readField(ofs, theField.dataType, theField.name + "[i]");

                ofs << "}" << endl;
            } else {
                ofs << theField.name + " = new " + theField.userTypeDefinition->name + "[" + arrayLength + "];" << endl;
                ofs << "for(int i=0; i < " + theField.name + ".Length;i++){" << endl;
                ofs << theField.name + "[i] = new " << theField.userTypeDefinition->name << "();" << endl;
                ofs << theField.name + "[i].Deserialize(reader);" << endl;
                ofs << "}" << endl;
            }

        } else if (theField.declarationType == DLT_USER) {
            ofs << theField.name + " = new " << theField.userTypeDefinition->name << "();" << endl;
            ofs << theField.name + ".Deserialize(reader);" << endl;
        } else if (theField.declarationType == DLT_PRIMITIVE) {
            readField(ofs, theField.dataType, theField.name);

        } else if (theField.declarationType == DLT_BYTE_ARRAY) {
            string arrayLength = nextParamName();
            ofs << "int " + arrayLength + " = SerializationUtil.ReadVariableLength(reader);" << endl;
            ofs << theField.name + " = new byte[" + arrayLength + "];";
            ofs << "reader.Read(" + theField.name + ");" << endl;
        }
    }

    string CSharpCodeGenerator::getParamListString(Function * function) {
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

    string CSharpCodeGenerator::getParamNameListString(Function * function) {
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

    void CSharpCodeGenerator::generateUsingNamespaces(ofstream & ofs) {
        ofs << "using System;" << endl;
        ofs << "using System.IO;" << endl;
        ofs << "using MiscUtil;" << endl;
        ofs << "using MiscUtil.IO;" << endl;
        ofs << "using MiscUtil.Conversion;" << endl;
        ofs << "using Talky;" << endl;
    }

    void CSharpCodeGenerator::generateDispatcher(string file, TalkyUnit * unit, Interface & theInterface) {
        ofstream ofs(file);
        if (unit->currentPackage != "") {
            ofs << "namespace " << unit->currentPackage << "{" << endl;
        }

        generateUsingNamespaces(ofs);

        ofs << "public class " + name + "Dispatcher {" << endl;
        // 1. dispatcher method
        ofs << "public static void Dispatch(MemoryEndianBinaryReader reader, " + name + "Proxy proxy) {" << endl;
        ofs << "int fid = reader.ReadByte();" << endl;
        ofs << "switch(fid)" << endl;
        ofs << "{" << endl;
        for (int i = 0; i < theInterface.functions.size(); i++) {
            ofs << "case " + __ITOA(i) + ":" << endl;
            ofs << "{" << endl;
            ofs << theInterface.functions[i]->name << "(reader, proxy);" << endl;
            ofs << "}" << endl;
            ofs << "break;" << endl;
        }
        ofs << "}" << endl; // switch
        ofs << "}" << endl; // dispatch method
        // 2. deserialize param and call proxy
        for (int i = 0; i < theInterface.functions.size(); i++) {
            ofs << "protected static void " + theInterface.functions[i]->name + "(MemoryEndianBinaryReader reader, " + name + "Proxy proxy) throws Exception{" << endl;
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

        if (unit->currentPackage != "") {
            ofs << "}" << endl;
        }
        ofs.close();
    }
    void CSharpCodeGenerator::generateProxy(string file, TalkyUnit * unit, Interface & theInterface) {
        ofstream ofs(file);

        generateUsingNamespaces(ofs);

        if (unit->currentPackage != "") {
            ofs << "namespace " << unit->currentPackage << "{" << endl;
        }

        ofs << "public abstract class " + name + "Proxy {" << endl;
        for (int i = 0; i < theInterface.functions.size(); i++) {
            ofs << "public abstract void " + theInterface.functions[i]->name + "(" + getParamListString(theInterface.functions[i]) + ");" << endl;
        }
        ofs << "}" << endl;
        if (unit->currentPackage != "") {
            ofs << "}" << endl;
        }
        ofs.close();
    }
    void CSharpCodeGenerator::generateStub(string file, TalkyUnit * unit, Interface & theInterface) {
        ofstream ofs(file);
        if (unit->currentPackage != "") {
            ofs << "namespace " << unit->currentPackage << "{" << endl;
        }

        generateUsingNamespaces(ofs);

        ofs << "public abstract class " + name + "Stub {" << endl;
        ofs << "protected abstract MemoryEndianBinaryWriter Begin();" << endl;
        ofs << "protected abstract void End();" << endl;

        for (int i = 0; i < theInterface.functions.size(); i++) {
            ofs << "public void " + theInterface.functions[i]->name + "(" + getParamListString(theInterface.functions[i]) + "){" << endl;
            ofs << "MemoryEndianBinaryWriter writer = Begin();" << endl;
            ofs << "writer.WriteByte(" << i << ");" << endl;
            for (int j = 0; j < theInterface.functions[i]->params.size(); j++) {
                serializeField(ofs, *(theInterface.functions[i]->params[j]));
            }

            ofs << "End();" << endl;
            ofs << "}" << endl;
        }
        ofs << "}" << endl;
        if (unit->currentPackage != "") {
            ofs << "}" << endl;
        }
        ofs.close();
    }

    void CSharpCodeGenerator::generate(TalkyUnit * unit, string path) {
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
            cout << "csharp generator output dir does not exist:" << dir << endl;
            exit(-1);
        }

        dir = fs::canonical(dir);
        path = dir.native();

        cout << "generating csharp source to:" << path << endl;

        map<string, Definition*>& definitions = unit->definitions;

        for ( map<string, Definition*>::iterator it = definitions.begin(); it != definitions.end(); ++it ) {
            Definition* definition = it->second;
            string name = definition->name;
            DefinitionType type = definition->getType();
            if (type == DFT_ENUM) {
                ofstream ofs(path + "/" + name + ".cs");
                if (unit->currentPackage != "") {
                    ofs << "namespace " << unit->currentPackage << "{" << endl;
                }
                ofs << "public class " << name << "{" << endl;

                Enum& theEnum = *dynamic_cast<Enum*>(definition);

                for (int i = 0; i < theEnum.members.size(); i++) {
                    ofs << "public const int " << theEnum.members[i] << "=" << i << ";" << endl;
                }

                ofs << "public const int MAX_VALUE=" << theEnum.members.size() << ";" << endl;

                ofs << "public static string ToString(byte value){" << endl;
                for (int i = 0; i < theEnum.members.size(); i++) {
                    ofs << "if(value == " << theEnum.members[i] << "){" << endl;
                    ofs << "return \"" << theEnum.members[i] << "\";" << endl;
                    ofs << "}" << endl;
                }
                ofs << "return null;" << endl;

                ofs << "}" << endl;

                ofs << "public static int ToValue(string name){" << endl;
                for (int i = 0; i < theEnum.members.size(); i++) {
                    ofs << "if(name == \"" << theEnum.members[i] << "\")){" << endl;
                    ofs << "return " << theEnum.members[i] << ";" << endl;
                    ofs << "}" << endl;
                }
                ofs << "return -1;" << endl;

                ofs << "}" << endl;

                ofs << "}" << endl;

                if (unit->currentPackage != "") {
                    ofs << "}" << endl;
                }

                ofs.close();
            } else if (type == DFT_STRUCTURE) {
                generateUsingNamespaces();

                ofstream ofs(path + "/" + name + ".cs");
                if (unit->currentPackage != "") {
                    ofs << "namespace " << unit->currentPackage << "{" << endl;
                }

                ofs << "public class " << name << "{" << endl;

                Structure& theStructure = *dynamic_cast<Structure*>(definition);
                std::vector<TypeDeclaration*>& fields = theStructure.members;
                for (int i = 0; i < fields.size(); i++) {
                    TypeDeclaration& theField = *fields[i];
                    string dataTypeName = getTypeName(theField);
                    ofs << "public " << dataTypeName << " " << theField.name << ";" << endl;
                }

                //serializer
                ofs << "public void Serialize(MemoryEndianBinaryWriter writer){" << endl;

                //mark fields that need serialization
                int fieldMarkSize = (fields.size() + 7) / 8;
                ofs << "FieldMark fm = new FieldMark(" << fieldMarkSize << ");" << endl;
                for (int i = 0; i < fields.size(); i++) {
                    TypeDeclaration& theField = *fields[i];
                    if (theField.declarationType == DLT_ARRAY
                            || theField.declarationType == DLT_BYTE_ARRAY) {
                        //fm.mark(name == null || name.length == 0 ? false : true);
                        ofs << "fm.Mark(" << theField.name << " != null && " << theField.name << ".Length > 0);" << endl;
                    } else if (theField.declarationType == DLT_USER) {
                        ofs << "fm.Mark(true);" << endl;
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
                            ofs << "fm.Mark(" << theField.name << " != 0);" << endl;
                        } else if (theField.dataType == DT_BOOL) {
                            ofs << "fm.Mark(true);" << endl;
                        } else if (theField.dataType == DT_STRING) {
                            ofs << "fm.Mark(" << theField.name << " != null && " << theField.name << ".Length() > 0);" << endl;
                        }
                    }
                }
                // serialize the field mark
                ofs << "writer.Write(fm.getData());" << endl;
                //actual serilization code
                for (int i = 0; i < fields.size(); i++) {
                    TypeDeclaration& theField = *fields[i];
                    ofs << "if(fm.IsMarked(" + __ITOA(i) + ")){" << endl;
                    serializeField(ofs, theField);
                    ofs << "}" << endl;
                }

                // ofs << "}" << endl;
                ofs << "}" << endl;

                //deserializer
                ofs << "public void Deserialize(MemoryEndianBinaryReader reader){" << endl;
                ofs << "FieldMark fm = new FieldMark(" << fieldMarkSize << ");" << endl;
                ofs << "reader.Read(fm.getData());" << endl;
                for (int i = 0; i < fields.size(); i++) {
                    TypeDeclaration& theField = *fields[i];
                    ofs << "if(fm.ReadMark()){" << endl;
                    deserializeField(ofs, theField);
                    ofs << "}" << endl;
                }
                ofs << "}" << endl;

                ofs << "}" << endl;

                if (unit->currentPackage != "") {
                    ofs << "}" << endl;
                }
                ofs.close();
            } else if (type == DFT_INTERFACE) {
                Interface& theInterface = *dynamic_cast<Interface*>(definition);

                generateProxy(path + "/" + name + "Proxy" + ".cs", unit, theInterface);

                generateStub(path + "/" + name + "Stub" + ".cs", unit, theInterface);

                generateDispatcher(path + "/" + name + "Dispatcher" + ".cs", unit, theInterface);

            }


        }


    }