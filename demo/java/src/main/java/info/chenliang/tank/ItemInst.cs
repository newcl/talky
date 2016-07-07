using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
namespace info.chenliang.tank{
public class ItemInst{
public sbyte seq;
public sbyte itemId;
public sbyte count;
public void Serialize(MemoryEndianBinaryWriter writer){
FieldMark fm = new FieldMark(1);
fm.Mark(seq != 0);
fm.Mark(itemId != 0);
fm.Mark(count != 0);
writer.Write(fm.getData());
if(fm.IsMarked(0)){
writer.WriteInt8(seq);
}
if(fm.IsMarked(1)){
writer.WriteInt8(itemId);
}
if(fm.IsMarked(2)){
writer.WriteInt8(count);
}
}
public void Deserialize(MemoryEndianBinaryReader reader){
FieldMark fm = new FieldMark(1);
reader.Read(fm.getData());
if(fm.ReadMark()){
seq = reader.ReadByte();
}
if(fm.ReadMark()){
itemId = reader.ReadByte();
}
if(fm.ReadMark()){
count = reader.ReadByte();
}
}
}
}
