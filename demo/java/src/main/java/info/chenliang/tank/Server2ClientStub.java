package info.chenliang.tank;
import java.io.*;
import info.chenliang.talky.*;
public abstract class Server2ClientStub {
protected abstract DataOutputStream begin();
protected abstract void end();
public void onHit(byte attacker,short damage) throws Exception{
DataOutputStream dos = begin();
dos.write(0);
dos.writeByte(attacker);
dos.writeShort(damage);
end();
}
public void onSync(Player[] players) throws Exception{
DataOutputStream dos = begin();
dos.write(1);
SerializationUtil.writeVariableLength(dos, players.length);
for(int i=0; i < players.length;i++){
players[i].serialize(dos);
}
end();
}
}
