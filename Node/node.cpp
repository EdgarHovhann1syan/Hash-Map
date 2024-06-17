// node.cpp
#include "node.h"

Node::Node(const std::string& key, int value, Node* next) : m_key(key), m_value(value), m_next(next) {}

Node::Node() : m_key(""), m_value(0), m_next(nullptr) {}

std::string& Node::getKey() 
{
    return m_key;
}

int Node::getValue() const 
{
    return m_value;
}

void Node::setValue(int value)
{
    m_value = value;
}

Node* Node::getNext() const
{
    return m_next;
}

void Node::push(const std::string& key, int value)
{
    Node* newNode = new Node(key, value, m_next);
    m_next = newNode;
}

void Node::setNext(Node* next)
{
    this->m_next = next;
}