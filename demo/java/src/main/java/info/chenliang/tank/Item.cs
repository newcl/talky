using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
namespace info.chenliang.tank{
public class Item{
public sbyte id;
public string name;
public void Serialize(MemoryEndianBinaryWriter writer){
FieldMark fm = new FieldMark(1);
fm.Mark(id != 0);
fm.Mark(name != null && name.Length() > 0);
writer.Write(fm.getData());
if(fm.IsMarked(0)){
writer.WriteInt8(id);
}
if(fm.IsMarked(1)){
writer.WriteUTF(name);
}
}
public void Deserialize(MemoryEndianBinaryReader reader){
FieldMark fm = new FieldMark(1);
reader.Read(fm.getData());
if(fm.ReadMark()){
id = reader.ReadByte();
}
if(fm.ReadMark()){
name = reader.ReadUTF();
}
}
}
}
