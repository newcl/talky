package test;

import info.chenliang.talky.FieldMark;
import org.junit.Test;

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

        assert (fm.readIndex == 0);
        assert (fm.writeIndex == 16);
        assert ((0xff&fm.data[0]) == 0b11001110);
        assert ((0xff&fm.data[1]) == 0b01100100);

        assert (fm.isMarked(0));
        assert (fm.isMarked(1));
        assert (!fm.isMarked(2));
        assert (!fm.isMarked(3));

        assert (fm.isMarked(4));
        assert (fm.isMarked(5));
        assert (fm.isMarked(6));
        assert (!fm.isMarked(7));

        assert (!fm.isMarked(8));
        assert (fm.isMarked(9));
        assert (fm.isMarked(10));
        assert (!fm.isMarked(11));

        assert (!fm.isMarked(12));
        assert (fm.isMarked(13));
        assert (!fm.isMarked(14));
        assert (!fm.isMarked(15));

    }


}
