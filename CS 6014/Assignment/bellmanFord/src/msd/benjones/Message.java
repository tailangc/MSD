package msd.benjones;

import java.io.PrintStream;
import java.util.HashMap;
import java.util.Iterator;

public class Message {
    Router sender;
    Router receiver;
    HashMap<Router, Integer> distances;

    public Message(Router sender, Router receiver, HashMap<Router, Integer> distances) {
        this.sender = sender;
        this.receiver = receiver;
        this.distances = distances;
    }

    public void dump() {
        PrintStream var10000 = System.out;
        String var10001 = String.valueOf(this.sender);
        var10000.println("sender: " + var10001 + " receiver " + String.valueOf(this.receiver));
        Iterator var1 = this.distances.keySet().iterator();

        while(var1.hasNext()) {
            Router r = (Router)var1.next();
            var10000 = System.out;
            var10001 = String.valueOf(r);
            var10000.println("\t" + var10001 + "\t" + String.valueOf(this.distances.get(r)));
        }

    }
}
