// hash_map.h
#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "Node/node.h"
#include <vector>
#include <string>

class HashMap {
public:
    HashMap();
    HashMap(std::size_t totalNumberOfSlotsInHashTable);
    void insert(const std::string& key, int value);
    void print() const;
    int find(const std::string& key);
    void remove(const std::string& key);
private:
    std::size_t hash(const std::string& key) const;
    double calculateLoadFactor();
    void rehash();

    std::size_t m_totalNumberOfSlotsInHashTable;
    std::vector<Node*> m_elems;
    std::size_t m_numberOfItemsInHashTable;
    double m_loadFactor;
};

#endif // HASH_MAP_H
