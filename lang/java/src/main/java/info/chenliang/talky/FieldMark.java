package info.chenliang.talky;

/**
 * Created by chenliang on 16/3/28.
 */
public class FieldMark {
    public byte[] data;
    public int readIndex;
    public int writeIndex;

    public FieldMark(int bytes){
        data = new byte[bytes];
    }

    public void mark(boolean isMarked){
        if(writeIndex >= data.length * 8){
            throw new RuntimeException("overflow writeIndex=" + writeIndex + " data.length=" +data.length );
        }

        int byteIndex = writeIndex / 8;
        int bitIndex = writeIndex % 8;
        data[byteIndex] |= isMarked ? 1 << (7 - bitIndex) : 0;
        writeIndex ++;
    }

    public boolean isMarked(int index){
        int byteIndex = index / 8;
        int bitIndex = index % 8;
        return (data[byteIndex] & 1 << (7 - bitIndex)) != 0;
    }

    public boolean readMark(){
        boolean isMarked = isMarked(readIndex++);
        return isMarked;
    }
}
