struct DataArray<T> {
    void init(int count); // allocs items (max 64k), then Clear()
    void dispose();       // frees items
    void clear();         // resets data members, (runs destructors* on outstanding items, *optional)

    T &alloc();           // alloc (memclear* and/or construct*, *optional) an item from freeList or items[maxUsed++], sets id to (nextKey++ << 16) | index
    void free(T&);        // puts entry on free list (uses id to store next)

    int get_id(T&);       // accessor to the id part if Item

    T &get(id)            // return item[id & 0xFFFF];
    T *try_get(id);       // validates id, then returns item, returns null if invalid.  for cases like AI references and others where 'the thing might have been deleted out from under me'

    bool next(T *&);      // return next item where id & 0xFFFF0000 != 0 (ie items not on free list)

    struct Item {
        T item;
        int id;           // (key << 16 | index) for alloced entries, (0 | nextFreeIndex) for free list entries
    };

    Item *items;
    int max_size;         // total size
    int max_used;         // highest index ever alloced
    int count;            // num alloced items
    int next_key;         // [1..2^16] (don't let == 0)
    int free_head;        // index of first free entry
};
