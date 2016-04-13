package info.chenliang.talky;

import java.io.DataInputStream;
import java.io.DataOutputStream;

/**
 * Created by chenliang on 16/3/28.
 */
public class SerializationUtil {
    public final static int MAX = 0X3FFFFFFF;

    public static int writeVariableLength(DataOutputStream dos, int length) throws Exception{
        if(length < 0){
            throw new IllegalArgumentException("input shoule be positive " + length);
        }

        if(length > MAX){
            throw new RuntimeException("overflow max="+MAX+" input="+length);
        }

        if(length <= 0x3F){
            byte[] data = new byte[]{(byte)(length)};
            dos.write(data);
            return 1;
        }else if(length <= 0x3FFF){
            byte[] data = new byte[]{(byte)(1 << 6 | length >>> 8), (byte)(length & 0xFF)};
            dos.write(data);
            return 2;
        }else if(length <= 0x3FFFFF){
            byte[] data = new byte[]{(byte)(2 << 6 | length >>> 16), (byte)((length >>> 8) & 0xFF), (byte)(length & 0xFF)};
            dos.write(data);
            return 3;
        }else if(length <= 0x3FFFFFFF){
            byte[] data = new byte[]{(byte)(3 << 6 | length >>> 24), (byte)((length >>> 16) & 0xFF), (byte)((length >>> 8) & 0xFF), (byte)(length & 0xFF)};
            dos.write(data);
            return 4;
        }else{
            throw new RuntimeException("should not be here");
        }
    }

    public static int readVariableLength(DataInputStream dis) throws Exception{
        int highestByte = dis.read();
        int bytes = (highestByte >>> 6) + 1;
        int value = highestByte & 0x3F;
        for(int i=0; i < bytes-1; i++){
            int theByte = dis.read();
            value = (value << 8) | theByte;
        }
        return value;
    }

}
