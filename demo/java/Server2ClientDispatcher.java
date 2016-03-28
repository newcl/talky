import java.io.*;

public class Server2ClientDispatcher {
    public static void dispatch(DataInputStream dis, Server2ClientProxy proxy) throws Exception {
        int fid = (int) (dis.read() & 0xFFFF);
        switch (fid) {
            case 0: {
                onHit(dis, proxy);
            }
            break;
            case 1: {
                onSync(dis, proxy);
            }
            break;
        }
    }

    protected static void onHit(DataInputStream dis, Server2ClientProxy proxy) throws Exception {
        byte attacker;
        short damage;
        attacker = dis.readByte();
        damage = dis.readShort();
        proxy.onHit(attacker, damage);
    }

    protected static void onSync(DataInputStream dis, Server2ClientProxy proxy) throws Exception {
        Player[] players;
        int __1__ = SerializeUtil.readVariableLength(dis);
        for (int i = 0; i < players.length; i++) {
            players[i].deserialize(dis);
        }
        proxy.onSync(players);
    }
}
}
