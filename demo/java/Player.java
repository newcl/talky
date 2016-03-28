import java.io.*;
public class Player{
public String name;
public byte id;
public ItemInst[] itemInsts;
public Point3d position;
public void serialize(DataOutputStream dos) throws Exception{
FieldMark fm = new FieldMark(1);
fm.mark(name == null || name.length == 0 ? false : true);
fm.mark(id == 0);
fm.mark(itemInsts == null || itemInsts.length == 0 ? false : true);
fm.mark(true);
if(fm.isMarked(0)){
dos.writeUTF(name);
}
if(fm.isMarked(1)){
dos.writeByte(id);
}
if(fm.isMarked(2)){
SerializeUtil.writeVariableLength(dos, itemInsts.length);
for(int i=0; i < itemInsts.length;i++){
itemInsts[i].serialize(dos);
}
}
if(fm.isMarked(3)){
position.serialize(dos);
}
}
public void deserialize(DataInputStream dis) throws Exception{
FieldMark fm = new FieldMark(1);
dis.read(fm.getData());
if(fm.readMark()){
name = dis.readUTF();
}
if(fm.readMark()){
id = dis.readByte();
}
if(fm.readMark()){
int __0__ = SerializeUtil.readVariableLength(dis);
for(int i=0; i < itemInsts.length;i++){
itemInsts[i].deserialize(dis);
}
}
if(fm.readMark()){
position.deserialize(dis);
}
}
}
