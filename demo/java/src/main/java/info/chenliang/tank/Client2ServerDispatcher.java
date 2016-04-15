package info.chenliang.tank;
import java.io.*;
import info.chenliang.talky.*;
public class Client2ServerDispatcher {
public static void dispatch(DataInputStream dis, Client2ServerProxy proxy) throws Exception{
int fid = (int)(dis.read()&0xFFFF);
switch(fid)
{
case 0:
{
fire(dis, proxy);
}
break;
case 1:
{
useItem(dis, proxy);
}
break;
}
}
protected static void fire(DataInputStream dis, Client2ServerProxy proxy) throws Exception{
byte playerId;
playerId = dis.readByte();
proxy.fire(playerId);
}
protected static void useItem(DataInputStream dis, Client2ServerProxy proxy) throws Exception{
byte seq;
seq = dis.readByte();
proxy.useItem(seq);
}
}
