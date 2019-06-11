#include <unordered_map>
#include <list>
#include <tuple>

using namespace std;
class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        unordered_map<int, list<tuple<int, int>>::iterator>::const_iterator it = lookupTable.find(key);
        if (it == lookupTable.end()) {
            return -1;
        } 
        // Put at front of list (Make LRU)
        tuple<int, int> node = *it->second;
        cache.erase(it->second);
        cache.push_front(node);
        lookupTable[key] = cache.begin();
        return std::get<1>(node);
    }
    
    void put(int key, int value) {
        unordered_map<int, list<tuple<int, int>>::iterator>::const_iterator it = lookupTable.find(key);
        if (it == lookupTable.end()) {
            // Check size and evict
            if (cache.size() == capacity) {
                list<tuple<int, int>>::iterator it = cache.end();
                advance(it, -1);
                tuple<int, int> node = *it;
                lookupTable.erase(std::get<0>(node));
                cache.erase(it);
            }
        } else {
            cache.erase(it->second);
        }
        cache.push_front(make_tuple(key,value));
        lookupTable[key] = cache.begin();
    }

private:
    int capacity;
    unordered_map<int, list<tuple<int, int>>::iterator> lookupTable;
    list<tuple<int, int>> cache;
};
