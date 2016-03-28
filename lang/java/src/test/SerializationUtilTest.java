package test;

import info.chenliang.talky.SerializationUtil;
import junit.framework.TestCase;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by chenliang on 16/3/28.
 */
public class SerializationUtilTest extends TestCase {

    public void testSerializeUtilBoundary() throws Exception{
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        SerializationUtil.writeVariableLength(dos, SerializationUtil.MAX);

        byte[] bytes = baos.toByteArray();
        assertEquals(4, bytes.length);

        DataInputStream dis = new DataInputStream(new ByteArrayInputStream(bytes));
        assertEquals(SerializationUtil.MAX, SerializationUtil.readVariableLength(dis));
    }

    public void testSerializeUtilRandom() throws Exception{
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);

        List<Integer> randomInts = new ArrayList<>();
        int totalBytes = 0;
        for (int i=0;i < 1000000;i++){
            int theInt = (int)(Math.random()*SerializationUtil.MAX);
            randomInts.add(theInt);
            totalBytes += SerializationUtil.writeVariableLength(dos, theInt);
        }

        byte[] bytes = baos.toByteArray();
        assertEquals(totalBytes, bytes.length);

        DataInputStream dis = new DataInputStream(new ByteArrayInputStream(bytes));
        for (int i=0;i < 1000000;i++){
            int theInt = randomInts.get(i);
            assertEquals(theInt, SerializationUtil.readVariableLength(dis));
        }
    }
}
