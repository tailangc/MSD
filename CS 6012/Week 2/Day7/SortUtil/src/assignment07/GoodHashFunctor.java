package assignment07;

public class GoodHashFunctor implements HashFunctor{
    /**
     * @param item
     * @return
     */
    @Override
    public int hash(String item) {
        // A good hash function that uses a simple polynomial rolling hash algorithm
        int hash = 0;
        for (int i = 0; i < item.length(); i++) {
            hash = (hash * 31) + item.charAt(i);
        }
        return hash;
    }
}
