using System;
using System.IO;
using MiscUtil;
using MiscUtil.IO;
using MiscUtil.Conversion;
using Talky;
namespace info.chenliang.tank{
public abstract class Client2ServerProxy {
public abstract void fire(sbyte playerId);
public abstract void useItem(sbyte seq);
}
}
