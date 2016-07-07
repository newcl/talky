namespace info.chenliang.tank{
using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
public class Server2ClientDispatcher {
public static void Dispatch(MemoryEndianBinaryReader reader, Server2ClientProxy proxy) {
int fid = reader.ReadByte();
switch(fid)
{
case 0:
{
onHit(reader, proxy);
}
break;
case 1:
{
onSync(reader, proxy);
}
break;
}
}
protected static void onHit(MemoryEndianBinaryReader reader, Server2ClientProxy proxy) throws Exception{
sbyte attacker;
Int16 damage;
attacker = reader.ReadByte();
damage = reader.ReadInt16();
proxy.onHit(attacker,damage);
}
protected static void onSync(MemoryEndianBinaryReader reader, Server2ClientProxy proxy) throws Exception{
Player[] players;
int __7__ = SerializationUtil.ReadVariableLength(reader);
players = new Player[__7__];
for(int i=0; i < players.Length;i++){
players[i] = new Player();
players[i].Deserialize(reader);
}
proxy.onSync(players);
}
}
}
