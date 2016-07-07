using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
namespace info.chenliang.tank{
public class Player{
public string name;
public sbyte id;
public ItemInst[] itemInsts;
public Point3d position;
public void Serialize(MemoryEndianBinaryWriter writer){
FieldMark fm = new FieldMark(1);
fm.Mark(name != null && name.Length() > 0);
fm.Mark(id != 0);
fm.Mark(itemInsts != null && itemInsts.Length > 0);
fm.Mark(true);
writer.Write(fm.getData());
if(fm.IsMarked(0)){
writer.WriteUTF(name);
}
if(fm.IsMarked(1)){
writer.WriteInt8(id);
}
if(fm.IsMarked(2)){
SerializationUtil.WriteVariableLength(writer, itemInsts.Length);
for(int i=0; i < itemInsts.Length;i++){
itemInsts[i].Serialize(writer);
}
}
if(fm.IsMarked(3)){
position.Serialize(writer);
}
}
public void Deserialize(MemoryEndianBinaryReader reader){
FieldMark fm = new FieldMark(1);
reader.Read(fm.getData());
if(fm.ReadMark()){
name = reader.ReadUTF();
}
if(fm.ReadMark()){
id = reader.ReadByte();
}
if(fm.ReadMark()){
int __0__ = SerializationUtil.ReadVariableLength(reader);
itemInsts = new ItemInst[__0__];
for(int i=0; i < itemInsts.Length;i++){
itemInsts[i] = new ItemInst();
itemInsts[i].Deserialize(reader);
}
}
if(fm.ReadMark()){
position = new Point3d();
position.Deserialize(reader);
}
}
}
}
