package Rooms;

import Game.Adventure;
import Items.Item;

import java.util.Random;

import static Game.Adventure.inventory;

public class MyRoom extends Room {

    private boolean isDay = false;
    private Random random = new Random();
    private boolean hasBurnedWood = false;
    Item wood;

    public MyRoom() {
        super("Dark Forest", "A dense and shadowy forest, where the tall trees block out most of the sunlight.");
        wood = new Item("Wood", "A dry piece of wood that seems like it could be lit on fire.");
        items_.add(wood);
    }

    @Override
    public Room goThroughDoor(int doorNum) {
        if (isDay || hasBurnedWood) {
            return super.goThroughDoor(doorNum);
        } else {
            System.out.println("The forest is too dark and dense to navigate through right now.");
            return null;
        }
    }

    @Override
    public void playerEntered() {
        System.out.println("The dense foliage above you blocks out most of the light, making it difficult to see.");
        if (isDay) {
            System.out.println("It's daytime, and a small amount of light is making its way through the trees.");
        }
    }

    @Override
    public void playerLeft() {
        System.out.println("You manage to find your way out of the dark forest.");
    }

    @Override
    public void heartbeat() {
        // Simulate the passing of time, changing between day and night
        if (random.nextInt(100) < 5) {
            isDay = !isDay;
            System.out.println(!isDay ? "The forest is now shrouded in darkness." : "The dawn has broken, and light filters through the trees.");
        }
    }

    @Override
    public boolean handleCommand(String[] subcommands) {
        if (subcommands.length <= 1) {
            return false;
        }
        String cmd = subcommands[0];
        String attr = subcommands[1];

        if (cmd.equals("light") && attr.equals("Wood")) {
            System.out.println("inventory: " + inventory);
//            Item Wood = new Item("Wood");
            if (inventory.contains(wood)) {
                System.out.println("You light the wood on fire, illuminating the forest around you.");
                hasBurnedWood = true;
                return true;
            } else {
                System.out.println("You don't have any wood to light.");
                return false;
            }
        }
        return false;
    }
}