package info.chenliang.tank;
import java.io.*;
import info.chenliang.talky.*;
public abstract class Client2ServerStub {
protected abstract DataOutputStream begin();
protected abstract void end();
public void fire(byte playerId) throws Exception{
DataOutputStream dos = begin();
dos.write(0);
dos.writeByte(playerId);
end();
}
public void useItem(byte seq) throws Exception{
DataOutputStream dos = begin();
dos.write(1);
dos.writeByte(seq);
end();
}
}
