// g++ -std=c++11 hash-map.cpp -o hash-map
//
// implementation of a hash table
// imcomplete / buggy
//
#include <iostream>
#include <string>

template <typename K, typename V> struct HashItem
{
    K key;
    V value;
    struct HashItem* next;

    struct HashItem* find(K key)
    {
        HashItem* item = this;
        while (item && item->key != key) {
            item = item->next;
        }
        return item;
    }

    struct HashItem* append(K key, V value)
    {
        HashItem* item = this;
        while (item->next) {
            item = item->next;
        }
        item->next = new HashItem;
        item = item->next;
        item->key = key;
        item->value = value;
        return item;
    }

    struct HashItem* insert(K key, V value)
    {
        HashItem* item = this;
        if (item->key != key) {
            while (item->next && item->next->key != key) {
                item = item->next;
            }
            HashItem* next = item->next;  // could be NULL
            item->next = new HashItem;
            item = item->next;
            item->next = next;
            item->key = key;
        }
        item->value = value;
        return item;
    }

    HashItem() : next(0) {}
};

template <typename K, typename V> class HashMap
{
protected:
    size_t _size;
    HashItem<K, V>** _table;

public:
    HashMap(size_t size=10) : _size(size)
    {
        _table = new HashItem<K, V>*[size];
        for (auto ii = 0; ii < size; ++ii) {
            _table[ii] = 0;  // initialise pointer to zero
        }
    }

    ~HashMap()
    {
        delete [] _table;
    }

    size_t size() { return _size; }

    void insert(K key, V value)
    {
        size_t hash = key.size();  // assumes type K has a size() method
        size_t index = hash % _size;
        std::cout << "insert hash index " << index << " " << key << " " << value << std::endl;
        if (!_table[index]) {
            _table[index] = new HashItem<K, V>;
            return;
        }
        auto found = _table[index]->find(key);
        if (found) {
            std::cout << "key  " << key << " found in hash map " << index << std::endl;
        }
        else {
            std::cout << "key  " << key << " NOT found in hash map " << index << std::endl;
        }

        auto item = _table[index]->insert(key, value);
        std::cout << "item " << key << " " << value << " " << item << std::endl;
        
    }
};


int main()
{
    auto map = HashMap<std::string, int>();

    std::cout << "size " << map.size() << std::endl;

    map.insert("hash", 0);
    map.insert("map",  1);
    map.insert("book", 2);
    map.insert("cab",  3);

    map.insert("hash", 10);
    map.insert("map",  11);
    map.insert("book", 12);
    map.insert("cab",  13);

    return 0;
}
