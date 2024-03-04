#ifndef HASHINTERFACE_HPP
#define HASHINTERFACE_HPP

template <typename Key, typename Value>
class HashInterface {
public:
    virtual Value* get(const Key& key) override const = 0;
    virtual void put(const Key& key, const Value& value) override = 0;
    virtual int getCollisions() const override = 0;
    virtual void printTable() = 0;
    virtual ~HashInterface() {}
};

#endif // HASHINTERFACE_HPP
