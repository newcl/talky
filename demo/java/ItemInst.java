import java.io.*;

public class ItemInst {
    public byte seq;
    public byte itemId;
    public byte count;

    public void serialize(DataOutputStream dos) throws Exception {
        FieldMark fm = new FieldMark(1);
        fm.mark(seq == 0);
        fm.mark(itemId == 0);
        fm.mark(count == 0);
        if (fm.isMarked(0)) {
            dos.writeByte(seq);
        }
        if (fm.isMarked(1)) {
            dos.writeByte(itemId);
        }
        if (fm.isMarked(2)) {
            dos.writeByte(count);
        }
    }

    public void deserialize(DataInputStream dis) throws Exception {
        FieldMark fm = new FieldMark(1);
        dis.read(fm.getData());
        if (fm.readMark()) {
            seq = dis.readByte();
        }
        if (fm.readMark()) {
            itemId = dis.readByte();
        }
        if (fm.readMark()) {
            count = dis.readByte();
        }
    }
}
