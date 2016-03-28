import java.io.*;
public class Point3d{
public float x;
public float y;
public float z;
public void serialize(DataOutputStream dos) throws Exception{
FieldMark fm = new FieldMark(1);
fm.mark(x == 0);
fm.mark(y == 0);
fm.mark(z == 0);
if(fm.isMarked(0)){
dos.writeFloat(x);
}
if(fm.isMarked(1)){
dos.writeFloat(y);
}
if(fm.isMarked(2)){
dos.writeFloat(z);
}
}
public void deserialize(DataInputStream dis) throws Exception{
FieldMark fm = new FieldMark(1);
dis.read(fm.getData());
if(fm.readMark()){
x = dis.readFloat();
}
if(fm.readMark()){
y = dis.readFloat();
}
if(fm.readMark()){
z = dis.readFloat();
}
}
}
