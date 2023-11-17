package Rooms;
import Game.Adventure;
import Items.Item;
public class Cell extends Rooms.Room {
    private boolean locked_ = true;
    int hungerLevel = 0 ;
    public Cell() {
        super( "Cell", "A barren jail cell made of concrete." );
        Item table = new Item( "Bones", "The remains of the last person without a key..."); items_.add( table );
    }
    @Override
    public Room goThroughDoor(int doorNum) {
        if( locked_ ) {
            System.out.println( "The door is locked!" );
            return null;
        }
        else {
            return super.goThroughDoor( doorNum );
        }
    }
    @Override
    public void playerEntered() {
        if( locked_ ) {
            System.out.println( "You hear a clicking noise..." );
        }
    }
    @Override
    public boolean handleCommand( String[] subcommands ) {
        if( subcommands.length <= 1 ) {
            return false;
        }
        String cmd = subcommands[0];
        String attr = subcommands[1];
        // unlock, use
        if( cmd.equals( "unlock" ) && attr.equals( "door") ) {
            boolean hasKey = false;
            for( Item item : Adventure.inventory ) {
                if( item.getName().equals( "Key" ) ) {
                    hasKey = true;
                    break;
                }
            }
            if( hasKey ) {
                System.out.println( "You unlock the door.");
                locked_ = false;
            }
            else {
                System.out.println( "You need a key to unlock the door." );
            }
            return true;

        }
        else if(cmd.equals("eat")&& attr.equals("cookie")){
            System.out.println("You eat delicious cookie");
            hungerLevel-=2;
            return true;
        }
        return false;
    }
    @Override
    public void heartbeat(){
        if(Adventure.currentRoom == this){
            hungerLevel++;
            if(hungerLevel<2){
                System.out.println("You are feeling a little hungry....");
            }
            if(hungerLevel<4) {
                System.out.println("You are starving");
            }
            else {
                System.out.println("You have died of hungry");
                System.exit(-1);
            }
        }
    }
}