package info.chenliang.tank;
import java.io.*;
import info.chenliang.talky.*;
public class Server2ClientDispatcher {
public static void dispatch(DataInputStream dis, Server2ClientProxy proxy) throws Exception{
int fid = (int)(dis.read()&0xFFFF);
switch(fid)
{
case 0:
{
onHit(dis, proxy);
}
break;
case 1:
{
onSync(dis, proxy);
}
break;
}
}
protected static void onHit(DataInputStream dis, Server2ClientProxy proxy) throws Exception{
byte attacker;
short damage;
attacker = dis.readByte();
damage = dis.readShort();
proxy.onHit(attacker,damage);
}
protected static void onSync(DataInputStream dis, Server2ClientProxy proxy) throws Exception{
Player[] players;
int __1__ = SerializationUtil.readVariableLength(dis);
players = new Player[__1__];
for(int i=0; i < players.length;i++){
players[i] = new Player();
players[i].deserialize(dis);
}
proxy.onSync(players);
}
}
