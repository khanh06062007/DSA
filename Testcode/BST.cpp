#include <iostream>
using namespace std;
struct node
{
    int key;
    node *left;
    node *right;
    node *parent;
    node(int val)
    {
        key = val;
        left = right = parent = nullptr;
    }
};
class BST
{
private:
    node *root;
    void findpos(node *u, node *v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v)
            v->parent = u->parent;
    }

public:
    BST() : root(nullptr) {};
    node *search(int key)
    {
        node *p = root;
        while (p)
        {
            if (p->key == key)
                return p;
            p = (key < p->key ? p->left : p->right);
        }
        return nullptr;
    }
    void insert(int key)
    {
        node *p = root;
        node *prev = nullptr;
        if (p == nullptr)
        {
            p = new node(key);
            return;
        }
        while (p)
        {
            prev = p;
            if (p->key == key)
                return;
            p = (key < p->key ? p->left : p->right);
        }
        p = new node(key);
        p->parent = prev;
        if (key < prev->key)
            prev->left = p;
        else
            prev->right = p;
        return;
    }
    void remove(int key)
    {
        node *z = search(key);
        if (z == nullptr)
            return;
        if (z->left == nullptr)
            findpos(z, z->right);
        else if (z->right == nullptr)
            findpos(z, z->left);
        else
        {
            node *y = z->right;
            while (y->left != nullptr)
                y = y->left;
            if (y->parent != z)
            {
                findpos(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            findpos(z, y);
            y->left = z->left;
            y->left->parent = y;
        }

        delete z;
    }
};
