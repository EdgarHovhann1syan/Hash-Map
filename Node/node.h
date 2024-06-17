// node.h
#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    Node(const std::string& key, int value, Node* next = nullptr);
    Node();
    std::string& getKey();
    int getValue() const;
    void setValue(int value);
    Node* getNext() const;
    void setNext(Node* next);
    void push(const std::string& key, int value);

private:
    std::string m_key;
    int m_value;
    Node* m_next;
};

#endif // NODE_H
