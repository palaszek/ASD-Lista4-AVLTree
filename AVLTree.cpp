#include <iostream>
#include "AVLTree.h"
#include <string>
#include <cstring>
using namespace std;

Node::Node(string name, string second_name, string adress, int* phone_number)
{

    strcpy(this->name, name.c_str());
    strcpy(this->second_name, second_name.c_str());
    strcpy(this->adress, adress.c_str());
    for(int i = 0; i < 10; i++)
        this->phone_number[i] = phone_number[i];
}

Node::Node(Node *p)
{
    strcpy(this->name, p->name);
    strcpy(this->second_name, p->second_name);
    strcpy(this->adress, p->adress);
    for(int i = 0; i < 10; i++)
        this->phone_number[i] = p->phone_number[i];
}

Node::Node()
{
    strcpy(this->name, " ");
    strcpy(this->second_name, " ");
    strcpy(this->adress, " ");
    for(int i = 0; i < 10; i++)
        this->phone_number[i] = 0;
}
void Node::SayMyName()
{
    cout << name << " " << second_name << " " << adress << phone_number[0]<<endl;
}

AVL::AVL()
{

}

void AVL::BL1(Node *&p)
{
    Node *pr = p->right;
    p->right = pr->left;
    pr->left = p;
    p = pr;
}

void AVL::BR1(Node *&p)
{
    Node *pl = p->left;
    p->left = pl->right;
    pl->right=p;
    p=pl;
}


bool AVL::balanceIR(Node *&p)
{
    switch(p->w)
    {
    case 1:
    {
        if(p->left->w == 1)
        {
            BR1(p);
            p->right->w=0;
        }
        else
        {
            BL1(p->left);
            BR1(p);
            p->left->w=(p->w == -1)? 1 : 0;
            p->right->w =(p->w == 1)? -1 : 0;
        }
        p->w = 0;
        return true;
    }
    break;
    case 0:
        p->w = 1;
        break;
    case -1:
        p->w = 0;
        return true;
        break;
    }
    return false;
}
bool AVL::balanceIL(Node *&p)
{
    switch(p->w)
    {
    case -1:
    {
        if(p->right->w == -1)
        {
            BL1(p);
            p->left->w=0;
        }
        else
        {
            BR1(p->right);
            BL1(p);
            p->right->w=(p->w == 1)? -1 : 0;
            p->left->w =(p->w == -1)? 1 : 0;
        }
        p->w = 0;
        return true;
    }
    break;
    case 0:
        p->w = -1;
        break;
    case 1:
        p->w = 0;
        return true;
        break;
    }
    return false;
}



bool AVL::insert(Node q, Node *&p)
{
    if(p==NULL)
    {
        p = new Node(q);
        return false;
    }
    else if((strcmp(p->name,q.name)>0)
            || ((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) > 0))
            || (((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) == 0)) && strcmp(p->adress, q.adress)>0))
    {
        if(!insert(q,p->left))
        {
            return balanceIR(p);
        }
    }
    else if((strcmp(p->name,q.name)<0)
            || ((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) < 0))
            || (((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) == 0)) && strcmp(p->adress, q.adress)<0))
    {
        if(!insert(q,p->right))
        {
            return balanceIL(p);
        }
    }
    return true;
}
bool AVL::balanceDR(Node *&p)
{
    switch(p->w)
    {
    case 1:
        switch(p->left->w)
        {
        case 0:
            BR1(p);
            p->w = -1;
            p->right->w = 1;
            return true;
            break;
        case 1:
            BR1(p);
            p->w = 0;
            p->right->w = 0;
            break;
        case -1:
            BL1(p->left);
            BR1(p);
            p->left->w=(p->w == -1)?1:0;
            p->right->w=(p->w == 1)?-1:0;
            p->w = 0;
            break;
        }
        break;
    case 0:
        p->w = 1;
        return true;
        break;
    case -1:
        p->w = 0;
        break;
    }
    return false;
}
bool AVL::balanceDL(Node *&p)
{
    switch(p->w)
    {
    case 1:
        p->w = 0;
        break;
    case 0:
        p->w = -1;
        return true;
        break;
    case -1:
        switch(p->right->w)
        {
        case 0:
            BL1(p);
            p->w = 1;
            p->left->w = -1;
            return true;
            break;
        case 1:
            BL1(p->right);
            BR1(p);
            p->right->w=(p->w == 1)?-1:0;
            p->left->w=(p->w == -1)?1:0;
            p->w = 0;
            break;
        case -1:
            BL1(p);
            p->w = 0;
            p->left->w = 0;
            break;
        }
        break;
    }
    return false;
}

bool AVL::del(Node *&q, Node *p)
{
    if(q->right)
    {
        if(!del(q->right, p))
        {
            return balanceDR(q);
        }
    }
    else
    {
        strcpy(p->name, q->name);
        strcpy(p->second_name, q->second_name);
        strcpy(p->adress, q->adress);
        for(int i = 0 ; i < 10; i++)
            p->phone_number[i] = q->phone_number[i];
        Node* q1=q;
        q=q->left;
        delete q1;
        return false;
    }
    return true;
}

bool AVL::deleteItem(Node q, Node *&p)
{
    if(p)
    {
        if((strcmp(p->name,q.name)>0)
                || ((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) > 0))
                || (((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) == 0)) && strcmp(p->adress, q.adress)>0))
        {
            if(!deleteItem(q,p->left))
            {
                return balanceDL(p);
            }
        }
        else if((strcmp(p->name,q.name)<0)
                || ((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) < 0))
                || (((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) == 0)) && strcmp(p->adress, q.adress)<0))
        {
            if(!deleteItem(q,p->right))
            {
                return balanceDR(p);
            }
        }
        else if(strcmp(q.name,p->name) == 0)
        {
            Node* r = p;
            if(!r->left)
            {
                p = p->right;
                delete r;
                cout << "Usunieto abonamenta" << endl;
                return false;
            }
            else if(!r->right)
            {
                p = p->left;
                delete r;
                cout << "Usunieto abonamenta" << endl;
                return false;
            }
            else if(!del(r->left, p))
            {
                cout << "Usunieto abonamenta" << endl;
                return balanceDL(p);
            }
        }
        else
        {
            cout << "Brak abonamenta..." << endl;
        }
    }
    return true;
}

bool AVL::FindItem(Node q, Node *&p)
{
    if(!p) return false; // return false if the tree is empty
    if((strcmp(p->name,q.name)>0)
            || ((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) > 0))
            || (((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) == 0)) && strcmp(p->adress, q.adress)>0))
    {
        return FindItem(q,p->left);
    }
    else if((strcmp(p->name,q.name)<0)
            || ((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) < 0))
            || (((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) == 0)) && strcmp(p->adress, q.adress)<0))
    {
        return FindItem(q,p->right);
    }
    else if((strcmp(p->name,q.name)==0 )&& (strcmp(p->second_name, q.second_name) == 0) && (strcmp(p->adress, q.adress)==0))
    {
        cout << "ZNALEZIONO: " << endl;
        cout << p->name << endl;
        cout << p->second_name << endl;
        cout << p->adress <<endl;
        for(int i = 0; i<10; i++)
            if(p->phone_number[i] != 0)
                cout << p->phone_number[i] <<endl;
        return true;
    }
    return false;
}
