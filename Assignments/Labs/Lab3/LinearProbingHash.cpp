#include "LinearProbingHash.hpp"

template <typename Key, typename Value>
int LinearProbingHash<Key, Value>::lookUp(const Key& key) {
    const int startIndex = hashIndex(key);
    int index = startIndex;

    while (true) {
        Record* p = table[index];
        if (p == nullptr || p->key == key)
            return index;

        collisions++;
        index++;
        index %= table.size();

        if (index == startIndex)
            return table.size() + 1;
    }
}

template <typename Key, typename Value>
LinearProbingHash<Key, Value>::LinearProbingHash(int initialSize) : table(initialSize), collisions(0) {}

template <typename Key, typename Value>
Value* LinearProbingHash<Key, Value>::get(const Key& key) {
    const int index = lookUp(key);
    if (index > table.size())
        return nullptr;

    Record* p = table[index];
    return p ? &p->value : nullptr;
}

template <typename Key, typename Value>
void LinearProbingHash<Key, Value>::put(const Key& key, const Value& value){
    const int index = lookUp(key);
    if (index > table.size())
        throw std::runtime_error("Table is full");

    Record* p = table[index];
    if (p == nullptr)
        table[index] = new Record(key, value);
    else
        p->value = value;
}

template <typename Key, typename Value>
int LinearProbingHash<Key, Value>::getCollisions() const{
    return collisions;
}

template <typename Key, typename Value>
void LinearProbingHash<Key, Value>::printTable() {
    std::cout << "Printing Hash Table:" << std::endl;
    for (const Record* p : table) {
        if (p != nullptr) {
            std::cout << "Key: " << p->key << ", Value: " << p->value << std::endl;
        }
    }
}

template <typename Key, typename Value>
LinearProbingHash<Key, Value>::~LinearProbingHash() {
    for (Record* p : table) {
        delete p;
    }
}
