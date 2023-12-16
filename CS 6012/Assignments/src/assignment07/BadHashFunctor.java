package assignment07;

public class BadHashFunctor implements HashFunctor{
    /**
     * @param item
     * @return
     */
    @Override
    public int hash(String item) {
        // A bad hash function that uses the first character's ASCII value
        return 40;
    }
}
