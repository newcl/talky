using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
namespace info.chenliang.tank{
public abstract class Server2ClientProxy {
public abstract void onHit(sbyte attacker,Int16 damage);
public abstract void onSync(Player[] players);
}
}
