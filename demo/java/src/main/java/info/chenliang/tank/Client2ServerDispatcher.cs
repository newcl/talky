namespace info.chenliang.tank{
using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
public class Client2ServerDispatcher {
public static void Dispatch(MemoryEndianBinaryReader reader, Client2ServerProxy proxy) {
int fid = reader.ReadByte();
switch(fid)
{
case 0:
{
fire(reader, proxy);
}
break;
case 1:
{
useItem(reader, proxy);
}
break;
}
}
protected static void fire(MemoryEndianBinaryReader reader, Client2ServerProxy proxy) throws Exception{
sbyte playerId;
playerId = reader.ReadByte();
proxy.fire(playerId);
}
protected static void useItem(MemoryEndianBinaryReader reader, Client2ServerProxy proxy) throws Exception{
sbyte seq;
seq = reader.ReadByte();
proxy.useItem(seq);
}
}
}
