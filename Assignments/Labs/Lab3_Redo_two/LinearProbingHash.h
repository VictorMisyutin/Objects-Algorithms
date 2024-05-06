#ifndef LINEARPROBINGHASH_H
#define LINEARPROBINGHASH_H

#include <iostream>
#include <vector>
#include <utility>

template<typename Key, typename Value>
class LinearProbingHash {
public:
    // constructor
    LinearProbingHash(int table_size) : tableSize(table_size), collisionsCount(0) {
        data.resize(table_size); // Resize the vector to the specified size
    }

    // returns nullptr if not found
    virtual Value* get(const Key& key){
        for(const auto& p: data){
            if(p.first == key){
                return &(p.second);
            }
        }
        return nullptr;
    }
    virtual void put(const Key& key, const Value& value){
        int index = hash_function(key);
        index = index % data.size();
        int newCollisions = 0;
        while (data[index].first != nullptr) {
            index = (index + 1) % data.size();
            newCollisions++;
        }
        newCollisions *= 2;
        collisionsCount += newCollisions;
        data[index] = std::make_pair(key, value);
    }

    virtual int getCollisions() const {
        return collisionsCount;
    }

    virtual ~LinearProbingHash() {} // Destructor should be virtual and with correct syntax

private:
    std::vector<std::pair<Key, Value>> data;
    int collisionsCount;
    int tableSize;
    
    int hash_function(Key& key) {
        unsigned int result = (key >> 8) | ((key & 0xFF) << 16);
        return result;
    }
};

#endif // LINEARPROBINGHASH_H
