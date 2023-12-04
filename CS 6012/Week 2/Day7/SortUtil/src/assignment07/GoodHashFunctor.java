package assignment07;

public class GoodHashFunctor implements HashFunctor{
    /**
     * @param item
     * @return
     */
    @Override
    public int hash(String item) {
        //Jenkins One-at-a-Time hash function
        int hash = 0;
        for (char c : item.toCharArray()) {
            hash += c;
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash;
    }
}
