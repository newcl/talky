import java.io.*;
public abstract class Client2ServerStub {
protected abstract DataOutputStream begin();
protected abstract void end();
public void fire(byte playerId) throws Exception{
DataOutputStream dos = begin();
dos.writeByte(playerId);
end();
}
public void useItem(byte seq) throws Exception{
DataOutputStream dos = begin();
dos.writeByte(playerId);
end();
}
}
