#ifndef LINEARPROBINGHASH_HPP
#define LINEARPROBINGHASH_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include "HashInterface.hpp"

template <typename Key, typename Value>
class LinearProbingHash : public HashInterface<Key, Value> {
private:
    class Record {
    public:
        Key key;
        Value value;

        Record(const Key& key1, const Value& value1) : key(key1), value(value1) {}
    };

    std::vector<Record*> table;
    int collisions;

    static int hash(const Key& key) {
        return (key >> 8) | ((key & 0xff) << 16);
    }

    int hashIndex(const Key& key) const {
        const int index = hash(key);
        return index % table.size();
    }

    int lookUp(const Key& key);

public:
    LinearProbingHash(int initialSize = 191);

    Value* get(const Key& key);

    virtual void put(const Key& key, const Value& value);

    virtual int getCollisions() const;

    virtual void printTable();

    virtual ~LinearProbingHash();
};

#include "LinearProbingHash.cpp"

#endif // LINEARPROBINGHASH_HPP
