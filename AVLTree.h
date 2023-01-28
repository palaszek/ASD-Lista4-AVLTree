#include <iostream>

using namespace std;
#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED


class Node
{
public:
    int w = 0;
    Node * left = NULL;
    Node * right = NULL;
    Node(string name, string second_name, string adress, int* phone_number);
    Node(Node *p);
    Node();
    char name[30];
    char second_name[30];
    char adress[100];
    int phone_number[10]= {0};
    void SayMyName();
};

class AVL
{
public:
    AVL();
    void BR1(Node *&p);
    void BL1(Node *&p);
    bool balanceIR(Node *&p);
    bool balanceIL(Node *&p);
    bool insert(Node q, Node *&p);
    bool balanceDR(Node *&p);
    bool balanceDL(Node *&p);
    bool del(Node *&q, Node *p);
    bool deleteItem(Node q, Node *&p);
    bool FindItem(Node q, Node *&p);
};

#endif // AVLTREE_H_INCLUDED
