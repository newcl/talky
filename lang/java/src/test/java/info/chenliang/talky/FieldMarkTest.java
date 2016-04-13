package info.chenliang.talky;

import org.junit.Test;

import static org.junit.Assert.assertTrue;

/**
 * Created by chenliang on 16/3/28.
 */
public class FieldMarkTest{

    @Test
    public void testfiledMark(){
        FieldMark fm = new FieldMark(2);
        fm.mark(true);
        fm.mark(true);
        fm.mark(false);
        fm.mark(false);

        fm.mark(true);
        fm.mark(true);
        fm.mark(true);
        fm.mark(false);

        fm.mark(false);
        fm.mark(true);
        fm.mark(true);
        fm.mark(false);

        fm.mark(false);
        fm.mark(true);
        fm.mark(false);
        fm.mark(false);

        assertTrue (fm.readIndex == 0);
        assertTrue (fm.writeIndex == 16);
        assertTrue ((0xff&fm.data[0]) == 0b11001110);
        assertTrue ((0xff&fm.data[1]) == 0b01100100);

        assertTrue (fm.isMarked(0));
        assertTrue (fm.isMarked(1));
        assertTrue (!fm.isMarked(2));
        assertTrue (!fm.isMarked(3));

        assertTrue (fm.isMarked(4));
        assertTrue (fm.isMarked(5));
        assertTrue (fm.isMarked(6));
        assertTrue (!fm.isMarked(7));

        assertTrue (!fm.isMarked(8));
        assertTrue (fm.isMarked(9));
        assertTrue (fm.isMarked(10));
        assertTrue (!fm.isMarked(11));

        assertTrue (!fm.isMarked(12));
        assertTrue (fm.isMarked(13));
        assertTrue (!fm.isMarked(14));
        assertTrue (!fm.isMarked(15));

    }


}
