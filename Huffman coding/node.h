#pragma once
#include "set.h"
class Node
{
public:
    Node();
    Node(int _count, Node* _next = nullptr, Node* _left = nullptr, Node* _right = nullptr);
    Node* next;
    Node* left;
    Node* right;
    int count = 0;
    Set str;
};
