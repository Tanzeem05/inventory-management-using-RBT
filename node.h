#include <iostream>
#include <string>
using namespace std;

// implementing red black tree
class Node
{
public:
    int id, stock;
    string name;
    bool color; // true = black, false = red
    Node *left, *right, *par;

    Node()
    {
        this->left = nullptr;
        this->right = nullptr;
        this->par = nullptr;
    }
    Node(int id, string name, int stock)
    {
        this->id = id;
        this->name = name;
        this->stock = stock;
        this->color = false; // new nodes are red by default
        this->left = nullptr;
        this->right = nullptr;
        this->par = nullptr;
    }
};