// hash_map.cpp
#include "hash_map.h"
#include <iostream>

HashMap::HashMap() :
    m_totalNumberOfSlotsInHashTable(10),
    m_numberOfItemsInHashTable(0),
    m_loadFactor(0),
    m_elems(m_totalNumberOfSlotsInHashTable, nullptr) {}

HashMap::HashMap(std::size_t totalNumberOfSlotsInHashTable) :
    m_totalNumberOfSlotsInHashTable(totalNumberOfSlotsInHashTable),
    m_numberOfItemsInHashTable(0),
    m_loadFactor(0),
    m_elems(m_totalNumberOfSlotsInHashTable, nullptr) {}

std::size_t HashMap::hash(const std::string& key) const
{
    std::size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

double HashMap::calculateLoadFactor()
{
    return static_cast<double>(m_numberOfItemsInHashTable) / m_totalNumberOfSlotsInHashTable;
}

void HashMap::rehash()
{
    std::vector<Node*> newElems(this->m_totalNumberOfSlotsInHashTable * 2, nullptr);
    std::size_t newTableSize = newElems.size();

    for (Node* node : this->m_elems)
    {
        while (node != nullptr)
        {
            std::size_t newIndex = this->hash(node->getKey()) % newTableSize;
            if (newElems[newIndex] == nullptr) {
                newElems[newIndex] = new Node(node->getKey(), node->getValue());
            } else {
                newElems[newIndex]->push(node->getKey(), node->getValue());
            }
            node = node->getNext();
        }
    }

    this->m_elems = std::move(newElems);
    this->m_totalNumberOfSlotsInHashTable = newTableSize;
    this->m_loadFactor = calculateLoadFactor();
}
void HashMap::remove(const std::string& key)
{
    std::size_t index = hash(key) % this->m_totalNumberOfSlotsInHashTable;
    Node* node = m_elems[index];
    Node* prev = nullptr;

    while (node != nullptr)
    {
        if (node->getKey() == key)
        {
            if (prev == nullptr) // node is the head of the list
            {
                m_elems[index] = node->getNext(); // update head of the list
            }
            else
            {
                prev->setNext(node->getNext()); // link previous node to next node
            }
            delete node;
            --this->m_numberOfItemsInHashTable;
            m_loadFactor = calculateLoadFactor();
            return; // exit function after deletion
        }
        prev = node;
        node = node->getNext();
    }
}

void HashMap::insert(const std::string& key, int value)
{
    if (this->m_loadFactor >= 0.7)
    {
        rehash();
    }

    std::size_t index = hash(key) % this->m_totalNumberOfSlotsInHashTable;

    if (m_elems[index] == nullptr)
    {
        // Create a new node if the bucket is empty
        m_elems[index] = new Node(key, value);
    }
    else
    {
        // If the bucket is not empty, push the new key-value pair
        Node* node = m_elems[index];
        while (node != nullptr)
        {
            if (node->getKey() == key)
            {
                node->setValue(value);  // Update the value if the key already exists
                return;
            }
            if (node->getNext() == nullptr)
            {
                node->push(key, value);
                break;
            }
            node = node->getNext();
        }
    }

    ++m_numberOfItemsInHashTable;
    m_loadFactor = calculateLoadFactor();
}

void HashMap::print() const
{
    for (const auto& node : this->m_elems)
    {
        Node* current = node;
        while (current != nullptr)
        {
            std::cout << current->getKey() << " " << current->getValue() << std::endl;
            current = current->getNext();
        }
    }
}

int HashMap::find(const std::string& key)
{
    std::size_t index = hash(key) % this->m_totalNumberOfSlotsInHashTable;
    Node* node = m_elems[index];
    while (node!= nullptr)
    {
        if (node->getKey() == key)
        {
            return node->getValue();
        }
        node = node->getNext();
    }
    return -1;
}