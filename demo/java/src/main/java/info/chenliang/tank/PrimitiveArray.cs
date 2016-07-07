using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
namespace info.chenliang.tank{
public class PrimitiveArray{
public sbyte[] byteArray;
public Int16[] shortArray;
public Int32[] intArray;
public Int64[] longArray;
public single[] floatArray;
public double[] doubleArray;
public void Serialize(MemoryEndianBinaryWriter writer){
FieldMark fm = new FieldMark(1);
fm.Mark(byteArray != null && byteArray.Length > 0);
fm.Mark(shortArray != null && shortArray.Length > 0);
fm.Mark(intArray != null && intArray.Length > 0);
fm.Mark(longArray != null && longArray.Length > 0);
fm.Mark(floatArray != null && floatArray.Length > 0);
fm.Mark(doubleArray != null && doubleArray.Length > 0);
writer.Write(fm.getData());
if(fm.IsMarked(0)){
SerializationUtil.WriteVariableLength(writer, byteArray.Length);
for(int i=0; i < byteArray.Length;i++){
writer.WriteInt8(byteArray[i]);
}
}
if(fm.IsMarked(1)){
SerializationUtil.WriteVariableLength(writer, shortArray.Length);
for(int i=0; i < shortArray.Length;i++){
writer.WriteInt16(shortArray[i]);
}
}
if(fm.IsMarked(2)){
SerializationUtil.WriteVariableLength(writer, intArray.Length);
for(int i=0; i < intArray.Length;i++){
writer.WriteInt32(intArray[i]);
}
}
if(fm.IsMarked(3)){
SerializationUtil.WriteVariableLength(writer, longArray.Length);
for(int i=0; i < longArray.Length;i++){
writer.WriteInt64(longArray[i]);
}
}
if(fm.IsMarked(4)){
SerializationUtil.WriteVariableLength(writer, floatArray.Length);
for(int i=0; i < floatArray.Length;i++){
writer.WriteSingle(floatArray[i]);
}
}
if(fm.IsMarked(5)){
SerializationUtil.WriteVariableLength(writer, doubleArray.Length);
for(int i=0; i < doubleArray.Length;i++){
writer.WriteDouble(doubleArray[i]);
}
}
}
public void Deserialize(MemoryEndianBinaryReader reader){
FieldMark fm = new FieldMark(1);
reader.Read(fm.getData());
if(fm.ReadMark()){
int __1__ = SerializationUtil.ReadVariableLength(reader);
byteArray = new sbyte[__1__];
for(int i=0; i < __1__;i++){
byteArray[i] = reader.ReadByte();
}
}
if(fm.ReadMark()){
int __2__ = SerializationUtil.ReadVariableLength(reader);
shortArray = new Int16[__2__];
for(int i=0; i < __2__;i++){
shortArray[i] = reader.ReadInt16();
}
}
if(fm.ReadMark()){
int __3__ = SerializationUtil.ReadVariableLength(reader);
intArray = new Int32[__3__];
for(int i=0; i < __3__;i++){
intArray[i] = reader.ReadInt32();
}
}
if(fm.ReadMark()){
int __4__ = SerializationUtil.ReadVariableLength(reader);
longArray = new Int64[__4__];
for(int i=0; i < __4__;i++){
longArray[i] = reader.ReadInt64();
}
}
if(fm.ReadMark()){
int __5__ = SerializationUtil.ReadVariableLength(reader);
floatArray = new single[__5__];
for(int i=0; i < __5__;i++){
floatArray[i] = reader.ReadSingle();
}
}
if(fm.ReadMark()){
int __6__ = SerializationUtil.ReadVariableLength(reader);
doubleArray = new double[__6__];
for(int i=0; i < __6__;i++){
doubleArray[i] = reader.ReadDouble();
}
}
}
}
}
