#include <iostream>
#include "Red_Black_Tree.h"
using namespace std;

class inventory_system
{
    RedBlackTree rbt;

public:
    void addItem(int id, string name, int stock, string &tree) // 1
    {
        rbt.insert(id, name, stock);
        rbt.display(rbt.getRoot(), tree);
        cout <<endl;
    }

    void buyItem(int productID, int quantity, string &tree) // 2
    {
        Node *reqNode = rbt.check(productID);
        if (reqNode != nullptr)
        {
            if (reqNode->stock > quantity)
            {
                reqNode->stock = reqNode->stock - quantity;
            }
            else
            {
                rbt.deleteNode(reqNode);
            }
        }
        rbt.display(rbt.getRoot(), tree);
        cout << endl;
    }

    void checkItem(int productID, string &msg) // 3
    {
        Node *reqNode = rbt.check(productID);
        if (reqNode != nullptr)
        {
            msg = "stock left: " + to_string(reqNode->stock) + "\n";
            cout << "stock left: " << reqNode->stock << endl;
        }
        else
        {
            msg = "Not available\n";
            cout << "Not available" << endl;
        }
    }

    bool clearInventory() // 4
    {
        if (rbt.getNodeCount() == 0)
        {
            cout << "unsuccessful" << endl;
            return false;
        }

        rbt.clearTree();
        cout << "successful" << endl;
        return true;
    }

    int InventorySize() // 5
    {
        return rbt.getNodeCount();
    }

    bool isEmpty() // 6
    {
        return (rbt.getNodeCount() == 0) ? true : false;
    }

    void listInventory(vector<string> &res) // 7
    {
        rbt.inOrder(rbt.getRoot(),res);
    }
};