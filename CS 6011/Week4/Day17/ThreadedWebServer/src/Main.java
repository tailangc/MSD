// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        // Press Opt+Enter with your caret at the highlighted text to see how
        // IntelliJ IDEA suggests fixing it.

            Chats chats1 = new Chats("Room 1");
            Chats chats2 = new Chats("Room 2");
        Chats chats3 = new Chats("Room 2");
            chats1.getRoom("Room 2");
        chats1.getRoom("Room 1");
        chats2.getRoom("Room 2");
        chats3.getRoom("Room 2");
        for(Chats r1: Chats.rooms){
            System.out.println(r1.roomName);
        }
        System.out.println("Done");
    }

}