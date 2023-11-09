package assignment02;

import java.util.ArrayList;
import java.util.GregorianCalendar;

public class LibraryBook extends Book{
    String holder_;
    GregorianCalendar dueDate_;
    ArrayList<String> holderList;

    public LibraryBook(long isbn, String author, String title) {
        super(isbn, author, title);
    }

    public void checkIn(){
        holder_ = null;
        dueDate_ = null;
    }

    public void checkOut(String holder, int year, int month, int day) {
        holder_ = holder;
        dueDate_ = new GregorianCalendar(year, month, day);
    }

    public String getHolder(){
        return holder_;
    }
    public GregorianCalendar getDueDate(){
        return dueDate_;
    }
}
