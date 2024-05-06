#ifndef LINEARPROBINGHASH_H
#define LINEARPROBINGHASH_H

#include "HashInterface.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

template<typename Key, typename Value>
class LinearProbingHash: public HashInterface<Key, Value> {
public:
    // constructor
    LinearProbingHash(int table_size) : tableSize(table_size), collisionsCount(0) {
        data.resize(table_size);
    }


    int lookUp(const Key& key) {
        const int startIndex = hash_function(key) % tableSize;

        int index = startIndex;

        while (true) {
            const std::pair<Key, Value> p = data[index];
            if (p.first == Key()|| p.first == key)
                return index;

            collisionsCount ++;
            index ++;
            index %= data.size();

            if (index == startIndex)
                return data.size() + 1;
        }

    }

    virtual Value* get(const Key& key) override {
         int index = lookUp(key);
        if (index >= data.size()) return nullptr;

        // Return a pointer to the value associated with the key
        return const_cast<Value*>(&data[index].second);
    }

    virtual void put(const Key& key, const Value& value) override{
        const int index = lookUp(key);
        if (index > data.size())         
            throw std::runtime_error("value mismatch");

        std::pair<Key, Value> p = data[index];
        if (p.first == Key())
            data[index] = std::make_pair(key, value);
        else
            p.second = value;

    }


    virtual int getCollisions() override{
        return collisionsCount;
    }

    void printTable(std::ofstream& fout) {
        fout << "print table.size()=" << data.size() << std::endl;
        for (int i = 0; i < data.size(); i++) {
            if (data[i].first != Key()) {
                fout << "index=" << i << " key=" << data[i].first << " value=" << data[i].second << std::endl;
            }
        }
        fout << "\nLinear probing " << collisionsCount << " collisions\n" << std::endl;
    }

    virtual ~LinearProbingHash() override{} // data vector should automatically delete

private:
    std::vector<std::pair<Key, Value>> data;
    int collisionsCount;
    int tableSize;

    int hash_function(const Key& key) {
        unsigned int result = (key >> 8) | ((key & 0xFF) << 16);
        return result;
    }
};

#endif // LINEARPROBINGHASH_H
