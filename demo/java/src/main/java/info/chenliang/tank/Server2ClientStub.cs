namespace info.chenliang.tank{
using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
public abstract class Server2ClientStub {
protected abstract MemoryEndianBinaryWriter Begin();
protected abstract void End();
public void onHit(sbyte attacker,Int16 damage){
MemoryEndianBinaryWriter writer = Begin();
writer.WriteByte(0);
writer.WriteInt8(attacker);
writer.WriteInt16(damage);
End();
}
public void onSync(Player[] players){
MemoryEndianBinaryWriter writer = Begin();
writer.WriteByte(1);
SerializationUtil.WriteVariableLength(writer, players.Length);
for(int i=0; i < players.Length;i++){
players[i].Serialize(writer);
}
End();
}
}
}
