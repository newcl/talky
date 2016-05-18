package info.chenliang.tank;

import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertTrue;

/**
 * Created by chenliang on 16/4/13.
 */
public class SerializationTest {

    @Test
    public void testItem() throws Exception{
        Item item = new Item();
        item.id = 11;
        item.name = "magic mana";

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        item.serialize(dos);

        DataInputStream dis = new DataInputStream(new ByteArrayInputStream(baos.toByteArray()));
        Item copy = new Item();
        copy.deserialize(dis);

        assertTrue(copy.id == 11);
        assertTrue(copy.name.equals("magic mana"));
    }

    @Test
    public void testItemInst() throws Exception{
        ItemInst item = new ItemInst();
        item.count = 3;
        item.itemId = 122;
        item.seq = 100;

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        item.serialize(dos);

        DataInputStream dis = new DataInputStream(new ByteArrayInputStream(baos.toByteArray()));
        ItemInst copy = new ItemInst();
        copy.deserialize(dis);

        assertTrue(copy.count == item.count);
        assertTrue(copy.itemId == item.itemId);
        assertTrue(copy.seq == item.seq);
    }

    @Test
    public void testPlayer() throws Exception{

        Player player = new Player();
        player.id = 100;
        player.name = "griffin";
        player.position = new Point3d();
        player.position.x = 30;
        player.position.y = 40;
        player.position.z = 50;
        player.itemInsts = new ItemInst[3];

        player.itemInsts[0] = new ItemInst();
        player.itemInsts[0].count = 10;
        player.itemInsts[0].itemId = 11;
        player.itemInsts[0].seq = 12;

        player.itemInsts[1] = new ItemInst();
        player.itemInsts[1].count = 20;
        player.itemInsts[1].itemId = 21;
        player.itemInsts[1].seq = 22;

        player.itemInsts[2] = new ItemInst();
        player.itemInsts[2].count = 30;
        player.itemInsts[2].itemId = 31;
        player.itemInsts[2].seq = 32;


        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        player.serialize(dos);

        DataInputStream dis = new DataInputStream(new ByteArrayInputStream(baos.toByteArray()));
        Player copy = new Player();
        copy.deserialize(dis);

        assertTrue(copy.id == player.id);
        assertTrue(copy.name.equals(player.name));
        assertTrue(copy.position.x == player.position.x);
        assertTrue(copy.position.y == player.position.y);
        assertTrue(copy.position.z == player.position.z);
        assertTrue(copy.itemInsts.length == player.itemInsts.length);
        for (int i=0; i < copy.itemInsts.length; i++){
            assertTrue(copy.itemInsts[i].count == player.itemInsts[i].count);
            assertTrue(copy.itemInsts[i].itemId == player.itemInsts[i].itemId);
            assertTrue(copy.itemInsts[i].seq == player.itemInsts[i].seq);
        }
    }

    @Test
    public void testPrimitiveArray() throws Exception{
        byte[] bytes = new byte[]{-1,2,3,11,29};
        short[] shorts = new short[]{-32,2323,222,-211,33};
        int[] ints = new int[]{-31341,2341,334,10,0};
        long[] longs = new long[]{13,-2,33,89,-100};
        float[] floats = new float[]{2,0.8f,-92,-993.234f};
        double[] doubles = new double[]{2,0.8f,-92,-993.234f};


        PrimitiveArray primitiveArray = new PrimitiveArray();
        primitiveArray.byteArray = bytes;
        primitiveArray.shortArray = shorts;
        primitiveArray.intArray = ints;
        primitiveArray.longArray = longs;
        primitiveArray.floatArray = floats;
        primitiveArray.doubleArray = doubles;

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(baos);
        primitiveArray.serialize(dos);

        DataInputStream dis = new DataInputStream(new ByteArrayInputStream(baos.toByteArray()));
        PrimitiveArray copy = new PrimitiveArray();
        copy.deserialize(dis);

        assertArrayEquals(copy.byteArray, bytes);
        assertArrayEquals(copy.shortArray, shorts);
        assertArrayEquals(copy.intArray, ints);
        assertArrayEquals(copy.longArray, longs);
        assertArrayEquals(copy.floatArray, floats, floats.length);
        assertArrayEquals(copy.doubleArray, doubles, doubles.length);


    }
}
