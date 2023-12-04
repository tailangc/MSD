package assignment07;

public class BadHashFunctor implements HashFunctor{
    /**
     * @param item
     * @return
     */
    @Override
    public int hash(String item) {
        return item.length();
    }
}
