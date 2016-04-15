package info.chenliang.tank;
import java.io.*;
import info.chenliang.talky.*;
public abstract class Server2ClientProxy {
public abstract void onHit(byte attacker,short damage);
public abstract void onSync(Player[] players);
}
