package assignment05;

import java.net.URL;
import java.util.NoSuchElementException;

public class WebBrowser {

    LinkedListStack<URL> forward;

    LinkedListStack<URL> back;

    URL current;
    /**
     * This constructor creates a new web browser with no previously-visited webpages and no webpages to visit next.
     */
    public WebBrowser(){
        back = new LinkedListStack<>();
        forward = new LinkedListStack<>();
        current = null;
    }

    /**
     * This constructor creates a new web browser with a preloaded history of visited webpages,
     * given as a list of URLLinks to an external site. objects.
     * The first webpage in the list is the "current" webpage visited,
     * and the remaining webpages are ordered from most recently visited to least recently visited.
     * @param history
     */
    public WebBrowser(SinglyLinkedList<URL> history){
        SinglyLinkedList<URL> temp = new SinglyLinkedList<>();
        forward = new LinkedListStack<>();
        back = new LinkedListStack<>();
        int size = history.size();
        for (int i = 0; i < size; i++){
            temp.insertFirst(history.getFirst());
            history.deleteFirst();
        }
        for (int i = 0; i < size; i++){
            back.push(temp.getFirst());
            temp.deleteFirst();
        }
        if(size > 0) {
            current = back.pop();
        }
    }

    /**
     * This method simulates visiting a webpage, given as a URL.
     * Note that calling this method should clear the forward button stack, since there is no URL to visit next.
     * @param webpage
     */
    public void visit(URL webpage){
        forward.clear();
        if (current != null){
            back.push(current);
        }
        current = webpage;
    }

    /**
     * his method simulates using the back button, returning the URL visited.
     * oSuchElementExceptionLinks to an external site. is thrown if there is no previously-visited URL.
     * @return
     * @throws NoSuchElementException
     */
    public URL back() throws NoSuchElementException{

        if (!back.isEmpty()){
            forward.push(current);
            current = back.pop();
            return current;
        }
        else{
            throw new NoSuchElementException();
        }
    }

    /**
     * This method simulates using the forward button, returning the URL visited.
     * NoSuchElementException is thrown if there is no URL to visit next.
     * @return
     * @throws NoSuchElementException
     */
    public URL forward() throws NoSuchElementException{
        if(!forward.isEmpty()){
            back.push(current);
            current = forward.pop();
            return current;
        }
        else{
            throw new NoSuchElementException();
        }
    }
    /**
     * This method generates a history of URLs visited,
     * as a list of URL objects ordered from most recently visited
     * to least recently visited (including the "current" webpage visited),
     * without altering subsequent behavior of this web browser.
     * @return
     */
    public SinglyLinkedList<URL> history(){
        SinglyLinkedList<URL> temp = new SinglyLinkedList<>();
        SinglyLinkedList history = new SinglyLinkedList();
        int size = back.size();
        for (int i = 0; i < size; i++){
            temp.insertFirst(back.pop());
        }
        for (int i = 0; i < size; i++){
            history.insertFirst(temp.getFirst());
            back.push(temp.getFirst());
            temp.deleteFirst();
        }

        history.insertFirst(current);
        return history;
    }

}
