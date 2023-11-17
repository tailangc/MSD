package Game;
//yuyao tu - Lab 10 - Adventure Week5/Day21/Adventure
import Items.Item;
import Rooms.Cell;
import Rooms.MyRoom;
import Rooms.Room;
import java.util.ArrayList;
import java.util.Scanner;
public class Adventure {
    public static Room currentRoom;
    public static ArrayList<Item> inventory = new ArrayList<>();
    public static void main( String[] args ) {
        System.out.println( "Server running in directory: " +
                System.getProperty( "user.dir" ) );
        /////////////////////////////
        // Create the house...
        Room outside = new Room( "Outside","The front of a large mansion." );
        Room entrance = new Room( "Entrance", "A small dusty foyer." );
        Room hall = new Room( "Grand Hall", "A large hall made for dancing." );
        Room kitchen = new Room( "Kitchen", "An old fashioned kitchen." );
        Room stairs = new Room( "Stairs", "The main staircase." );
        Room bedroom = new Room( "Master Bedroom", "A large and ornate bedroom." );
        Room balcony = new Room( "Balcony", "A balcony overlooking lush gardens." );
        // Room telep = new Rooms.TeleportationChamber();
        Room bar = new Room("bar","A large drinking room");
        Room cemetery = new Room("cemetery","A place where ghost gather");
        Room cell = new Cell();
        Room darkforest = new MyRoom();

        entrance.addConnection( cell );
        entrance.addConnection( outside );
        entrance.addConnection( hall );
        hall.addConnection( kitchen );
        hall.addConnection( stairs );
        stairs.addConnection( bedroom );
        bedroom.addConnection( balcony );
        hall.addConnection(bar);//my room
        hall.addConnection(cemetery);
        hall.addConnection(darkforest);
        // bedroom.addConnection( telep );
        /////////////////////////////
        // Create Items in the house...
        Item key = new Item( "Key", "A shiny key" );
        entrance.addItem( key );
        Item cup = new Item("glass","red wine glass");
        bar.addItem(cup);
        Item gravestone = new Item("gravestone"," Find out How to turn back from a ghost into a player");
        cemetery.addItem(gravestone);
        Item cookie = new Item("cookie", "One Delicious cookies");
        entrance.addItem( cookie );
        //////////////////////////////////////////////////////////////
        // Start the game....
        currentRoom = entrance;
        System.out.println( "Welcome to Game.Adventure 2023" );
        System.out.println("Welcome to Tery's Game! Good Luck!");
        System.out.println( "What would you like to do?" );
        Scanner sc = new Scanner( System.in );
        boolean done = false;
        while( !done ) {
            String command = sc.nextLine();
            String [] subcommands = command.split( " ", 2 );
            if( command.equals("") || command.equals( "?" ) ||
                    command.equals( "help" ) ) {
                System.out.println( "Available commands:\n\n" +
                        " ?, help - get this help.\n" +
                        " l, look - look around.\n" +
                        " i, inventory - display inventory.\n" +
                        " get <item> - pick up an item.\n" );
            }
            else if( Character.isDigit( command.charAt(0) ) ){
                int doorNum = Integer.parseInt( command );
                Room newRoom = currentRoom.goThroughDoor( doorNum );
                if( newRoom != null ) {
                    currentRoom.playerLeft();
                    newRoom.playerEntered();
                    currentRoom = newRoom;
                }
            }
            else if( command.equals( "l" ) || command.equals( "look" )  ) {
                currentRoom.print();
            }
            else if( command.equals( "i" ) || command.equals( "inventory" ) ) {
                if( inventory.size() > 0 ) {
                    System.out.println( "You are carrying:" );
                    for( Item item : inventory ) {
                        System.out.println( " " + item );
                    }
                }
                else {
                    System.out.println( "You are not carrying anything." );
                }
            }
            // get key
            else if( subcommands.length >= 2 && subcommands[0].equals( "get") ) {
                String itemName = subcommands[1];
                Item item = currentRoom.getItem( itemName );
                if( item != null ) {
                    System.out.println( "You pick up the " + itemName );
                    inventory.add( item );
                    currentRoom.removeItem( item );
                }
                else {
                    System.out.println( "There is no " + itemName + " here." );
                }
            }
            else if( currentRoom.handleCommand( subcommands ) == true ){
            }
            else {
                System.out.println( "Don't know how to '" + command + "'" );
            }
        }
    }
    private static void showInventory(){
        for(Item item:inventory){
            System.out.println(" " + item.getName());
        }
    }
}