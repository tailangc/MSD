import java.util.ArrayList;

public class Chats {
    static ArrayList<Chats> rooms = new ArrayList<>();
    ArrayList<String> clients = new ArrayList<>();
    String roomName;

    Chats(String roomName){
        this.roomName = roomName;
    }

    public Chats getRoom(String roomName){
        for(Chats chat: rooms){
            if(chat.roomName.equals(roomName)){
                return chat;
            }
        }
        Chats c1 = new Chats(roomName);
        rooms.add(c1);
        return c1;
    }

//    public Chats getName();

    public boolean addClient(String clientName){
        return clients.add(clientName);
    }

    public boolean removeClient(String clientName){
        return clients.remove(clientName);
    }

    //TODO 1. showlist funcion

}
