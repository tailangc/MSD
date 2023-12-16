package assignment07;

public class MediocreHashFunctor implements HashFunctor{
    /**
     * @param item
     * @return
     */
    @Override
    public int hash(String item) {
        //Return the sum of ASCII value of characters in the string
        int hash = 0;
        for (char c : item.toCharArray()) {
            hash += c;
        }
        return hash;
    }
}
