#ifndef HASHINTERFACE_H
#define HASHINTERFACE_H

template<typename Key, typename Value>
class HashInterface{
public:
	virtual Value* get(const Key& key) = 0;   	    	// returns null if not found
	virtual void   put(const Key& key, const Value& value) = 0;
	virtual int    getCollisions() = 0;
	virtual		   ~HashInterface() = default; // C++ only
};

#endif
