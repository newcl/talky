import java.io.*;
public abstract class Server2ClientStub {
protected abstract DataOutputStream begin();
protected abstract void end();
public void onHit(byte attacker,short damage) throws Exception{
DataOutputStream dos = begin();
dos.writeByte(attacker);
end();
}
public void onSync(Player[] players) throws Exception{
DataOutputStream dos = begin();
dos.writeByte(attacker);
end();
}
}
