using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
namespace info.chenliang.tank{
public class Point3d{
public single x;
public single y;
public single z;
public void Serialize(MemoryEndianBinaryWriter writer){
FieldMark fm = new FieldMark(1);
fm.Mark(x != 0);
fm.Mark(y != 0);
fm.Mark(z != 0);
writer.Write(fm.getData());
if(fm.IsMarked(0)){
writer.WriteSingle(x);
}
if(fm.IsMarked(1)){
writer.WriteSingle(y);
}
if(fm.IsMarked(2)){
writer.WriteSingle(z);
}
}
public void Deserialize(MemoryEndianBinaryReader reader){
FieldMark fm = new FieldMark(1);
reader.Read(fm.getData());
if(fm.ReadMark()){
x = reader.ReadSingle();
}
if(fm.ReadMark()){
y = reader.ReadSingle();
}
if(fm.ReadMark()){
z = reader.ReadSingle();
}
}
}
}
