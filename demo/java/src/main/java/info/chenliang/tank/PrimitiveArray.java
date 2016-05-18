package info.chenliang.tank;
import java.io.*;
import info.chenliang.talky.*;
public class PrimitiveArray{
public byte[] byteArray;
public short[] shortArray;
public int[] intArray;
public long[] longArray;
public float[] floatArray;
public double[] doubleArray;
public void serialize(DataOutputStream dos) throws Exception{
FieldMark fm = new FieldMark(1);
fm.mark(byteArray != null && byteArray.length > 0);
fm.mark(shortArray != null && shortArray.length > 0);
fm.mark(intArray != null && intArray.length > 0);
fm.mark(longArray != null && longArray.length > 0);
fm.mark(floatArray != null && floatArray.length > 0);
fm.mark(doubleArray != null && doubleArray.length > 0);
dos.write(fm.getData());
if(fm.isMarked(0)){
SerializationUtil.writeVariableLength(dos, byteArray.length);
for(int i=0; i < byteArray.length;i++){
dos.writeByte(byteArray[i]);
}
}
if(fm.isMarked(1)){
SerializationUtil.writeVariableLength(dos, shortArray.length);
for(int i=0; i < shortArray.length;i++){
dos.writeShort(shortArray[i]);
}
}
if(fm.isMarked(2)){
SerializationUtil.writeVariableLength(dos, intArray.length);
for(int i=0; i < intArray.length;i++){
dos.writeInt(intArray[i]);
}
}
if(fm.isMarked(3)){
SerializationUtil.writeVariableLength(dos, longArray.length);
for(int i=0; i < longArray.length;i++){
dos.writeLong(longArray[i]);
}
}
if(fm.isMarked(4)){
SerializationUtil.writeVariableLength(dos, floatArray.length);
for(int i=0; i < floatArray.length;i++){
dos.writeFloat(floatArray[i]);
}
}
if(fm.isMarked(5)){
SerializationUtil.writeVariableLength(dos, doubleArray.length);
for(int i=0; i < doubleArray.length;i++){
dos.writeDouble(doubleArray[i]);
}
}
}
public void deserialize(DataInputStream dis) throws Exception{
FieldMark fm = new FieldMark(1);
dis.read(fm.getData());
if(fm.readMark()){
int __1__ = SerializationUtil.readVariableLength(dis);
byteArray = new byte[__1__];
for(int i=0; i < __1__;i++){
byteArray[i] = dis.readByte();
}
}
if(fm.readMark()){
int __2__ = SerializationUtil.readVariableLength(dis);
shortArray = new short[__2__];
for(int i=0; i < __2__;i++){
shortArray[i] = dis.readShort();
}
}
if(fm.readMark()){
int __3__ = SerializationUtil.readVariableLength(dis);
intArray = new int[__3__];
for(int i=0; i < __3__;i++){
intArray[i] = dis.readInt();
}
}
if(fm.readMark()){
int __4__ = SerializationUtil.readVariableLength(dis);
longArray = new long[__4__];
for(int i=0; i < __4__;i++){
longArray[i] = dis.readLong();
}
}
if(fm.readMark()){
int __5__ = SerializationUtil.readVariableLength(dis);
floatArray = new float[__5__];
for(int i=0; i < __5__;i++){
floatArray[i] = dis.readFloat();
}
}
if(fm.readMark()){
int __6__ = SerializationUtil.readVariableLength(dis);
doubleArray = new double[__6__];
for(int i=0; i < __6__;i++){
doubleArray[i] = dis.readDouble();
}
}
}
}
