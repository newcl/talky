package info.chenliang.tank;
import java.io.*;
import info.chenliang.talky.*;
public class Item{
public byte id;
public String name;
public void serialize(DataOutputStream dos) throws Exception{
FieldMark fm = new FieldMark(1);
fm.mark(id != 0);
fm.mark(name != null && name.length() > 0);
dos.write(fm.getData());
if(fm.isMarked(0)){
dos.writeByte(id);
}
if(fm.isMarked(1)){
dos.writeUTF(name);
}
}
public void deserialize(DataInputStream dis) throws Exception{
FieldMark fm = new FieldMark(1);
dis.read(fm.getData());
if(fm.readMark()){
id = dis.readByte();
}
if(fm.readMark()){
name = dis.readUTF();
}
}
}
