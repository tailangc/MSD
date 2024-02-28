package msd.benjones;

import java.util.HashMap;
import java.util.Set;

public class Router {

    private HashMap<Router, Integer> distances;
    private String name;
    public Router(String name) {
        this.distances = new HashMap<>();
        this.name = name;
    }

    public void onInit() throws InterruptedException {

		//TODO: IMPLEMENT ME
		//As soon as the network is online,
		//fill in your initial distance table and broadcast it to your neighbors
    }

    public void onDistanceMessage(Message message) throws InterruptedException {
		//update your distance table and broadcast it to your neighbors if it changed
    }


    public void dumpDistanceTable() {
        System.out.println("router: " + this);
        for(Router r : distances.keySet()){
            System.out.println("\t" + r + "\t" + distances.get(r));
        }
    }

    @Override
    public String toString(){
        return "Router: " + name;
    }
}
