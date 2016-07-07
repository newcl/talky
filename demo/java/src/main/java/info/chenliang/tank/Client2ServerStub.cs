namespace info.chenliang.tank{
using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
public abstract class Client2ServerStub {
protected abstract MemoryEndianBinaryWriter Begin();
protected abstract void End();
public void fire(sbyte playerId){
MemoryEndianBinaryWriter writer = Begin();
writer.WriteByte(0);
writer.WriteInt8(playerId);
End();
}
public void useItem(sbyte seq){
MemoryEndianBinaryWriter writer = Begin();
writer.WriteByte(1);
writer.WriteInt8(seq);
End();
}
}
}
