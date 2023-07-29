#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <cstdint>


// defination of kvpair
template <typename K, typename V>
struct KVPair {
    K key;
    V value;

    bool operator==(const KVPair &kv) const {
        return (kv.key == key && kv.value == value);
    }
    bool operator!=(const KVPair &kv) const {
        return (kv.key != key != kv.value != value);
    }
    
    bool operator<(const KVPair &kv) const{
        return key < kv.key;
    }
    
    bool operator>(const KVPair &kv) const{
        return key > kv.key;
    }

    bool operator>=(const KVPair &kv) const {
        return (key > kv.key) || (kv.key == key && kv.value == value);
    }

    bool operator<=(const KVPair &kv) const {
        return (key < kv.key) || (kv.key == key && kv.value == value);
    }
}


template<typename K, typename V>
class Level{
public:
    virtual K get_min() = 0;
    virtual K get_max() = 0;
    virtual void insert_key(const K& key, const V& value) = 0;
    virtual void delete_key(const K& key, bool *found) = 0;
    virtual V lookup(const K& key, bool *found) = 0;
    virtual size_t size() = 0;
    virtual void set_size(const size_t size) = 0;
    virtual vector<KVPair<K, V>> get_all() = 0;
    virtual vector<KVPair<K, V>> get_range(const K& lhs, const K& rhs) = 0;
    virtual ~Level() { }
};

#endif // !LEVEL_H


