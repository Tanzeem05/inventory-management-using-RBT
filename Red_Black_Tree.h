#include "color.hpp"
#include <iostream>
#include <string>
#include "node.h"
using namespace std;

// implementing red black tree

class RedBlackTree
{
    Node *root;
    Node *T_NIL;
    int nodeCount;

public:
    RedBlackTree()
    {
        T_NIL = new Node();
        T_NIL->color = true;
        T_NIL->left = T_NIL->right = T_NIL->par = nullptr;
        root = T_NIL;

        nodeCount = 0;
    }

    Node *getRoot()
    {
        return root;
    }

    int getNodeCount()
    {
        return nodeCount;
    }

    void leftRotate(Node *refRoot)
    {
        Node *newRoot = refRoot->right;
        refRoot->right = newRoot->left;

        if (newRoot->left != T_NIL)
        {
            newRoot->left->par = refRoot;
        }

        newRoot->par = refRoot->par;
        if (refRoot->par == nullptr)
        {
            root = newRoot;
        }
        else
        {
            if (refRoot->par->left == refRoot)
            {
                refRoot->par->left = newRoot;
            }
            else
            {
                refRoot->par->right = newRoot;
            }
        }
        newRoot->left = refRoot;
        refRoot->par = newRoot;
    }

    void rightRotate(Node *refRoot)
    {
        Node *newRoot = refRoot->left;
        refRoot->left = newRoot->right;

        if (newRoot->right != T_NIL)
        {
            newRoot->right->par = refRoot;
        }

        newRoot->par = refRoot->par;

        if (refRoot->par == nullptr)
        {
            root = newRoot;
        }
        else
        {
            if (refRoot->par->left == refRoot)
            {
                refRoot->par->left = newRoot;
            }
            else
            {
                refRoot->par->right = newRoot;
            }
        }
        newRoot->right = refRoot;
        refRoot->par = newRoot;
    }

    void insert(int id, string name, int stock)
    {
        Node *newNode = new Node(id, name, stock);
        newNode->left = T_NIL;
        newNode->right = T_NIL;

        if (root == T_NIL)
        {
            root = newNode;
            root->par = nullptr;
            insertFix(newNode);
            nodeCount++;
            return;
        }

        Node *curr = root;

        while (curr != T_NIL)
        {
            if (id < curr->id)
            {
                if (curr->left == T_NIL)
                {
                    curr->left = newNode;
                    newNode->par = curr;
                    break;
                }
                curr = curr->left;
            }
            else if (id > curr->id)
            {
                if (curr->right == T_NIL)
                {
                    curr->right = newNode;
                    newNode->par = curr;
                    break;
                }
                curr = curr->right;
            }
            else
            {
                if (curr->name == name)
                {
                    curr->stock += stock;
                }
                else
                {
                    curr->name = name;
                    curr->stock = stock;
                }

                delete newNode;
                return;
            }
        }

        insertFix(newNode);

        nodeCount++;
    }

    void insertFix(Node *&node)
    {
        if (node == root)
        {
            node->color = true; // root node is black by default
            return;
        }

        if (node == nullptr || node->par == nullptr)
            return;

        if (node->par->color == true)
            return;

        Node *grandPar = node->par->par;
        Node *uncle;
        if (grandPar->left == node->par)
        {
            uncle = grandPar->right;
            if (uncle->color == false)
            {
                uncle->color = true;
                node->par->color = true;
                grandPar->color = false;
                insertFix(grandPar);
            }
            else if (uncle->color == true)
            {
                if (node->par->right == node)
                {
                    node = node->par;
                    leftRotate(node);
                }
                node->par->color = true;
                grandPar->color = false;
                rightRotate(grandPar);
                return;
            }
        }
        else if (grandPar->right == node->par)
        {
            uncle = grandPar->left;
            if (uncle->color == false)
            {
                uncle->color = true;
                node->par->color = true;
                grandPar->color = false;
                insertFix(grandPar);
            }
            else if (uncle->color == true)
            {
                if (node->par->left == node)
                {
                    node = node->par;
                    rightRotate(node);
                }
                node->par->color = true;
                grandPar->color = false;
                leftRotate(grandPar);
                return;
            }
        }
    }

    // deletion starts

    // transplant a node with a subtree
    void transplant(Node *target, Node *newNode)
    {
        if (target->par == nullptr)
        {
            root = newNode;
        }
        else if (target->par->left == target)
        {
            target->par->left = newNode;
        }
        else
        {
            target->par->right = newNode;
        }
        newNode->par = target->par;
    }

    // find the minimum of a subtree
    Node *MaximumTreeNode(Node *n)
    {
        while (n->right != T_NIL)
        {
            n = n->right;
        }
        return n;
    }

    void deleteNode(Node *target)
    {
        Node *newNode = target;
        bool clr = newNode->color;
        Node *x;

        if (target->left == T_NIL)
        {
            x = target->right;
            transplant(target, x);
        }
        else if (target->right == T_NIL)
        {
            x = target->left;
            transplant(target, x);
        }
        else
        {
            newNode = MaximumTreeNode(target->left);
            clr = newNode->color;
            x = newNode->left;

            if (newNode != target->left)
            {
                transplant(newNode, newNode->left);
                newNode->left = target->left;
                newNode->left->par = newNode;
            }
            else
            {
                x->par = newNode;
            }

            transplant(target, newNode);
            newNode->right = target->right;
            newNode->right->par = newNode;
            newNode->color = target->color;
        }
        if (clr == true)
        {
            deleteFix(x);
        }

        delete target;
        nodeCount--;
    }

    // fixes the RBT after deleting initially
    void deleteFix(Node *x)
    {
        while (x != root && x->color == true)
        {
            if (x->par->left == x)
            {
                Node *sibling = x->par->right;
                if (sibling->color == false) // sibling is red , case 1
                {
                    sibling->color = true;
                    x->par->color = false;
                    leftRotate(x->par);
                    sibling = x->par->right;
                }

                if (sibling->left->color == true && sibling->right->color == true) // case 2
                {
                    sibling->color = false;
                    x = x->par;
                }

                else
                {
                    if (sibling->right->color == true)
                    { // case 3
                        sibling->color = false;
                        sibling->left->color = true;
                        rightRotate(sibling);
                        sibling = x->par->right;
                    }

                    sibling->color = x->par->color;
                    x->par->color = true;
                    sibling->right->color = true;
                    leftRotate(x->par);
                    x = root;
                }
            }

            else
            {
                Node *sibling = x->par->left;
                if (sibling->color == false)
                {
                    sibling->color = true;
                    x->par->color = false;
                    rightRotate(x->par);
                    sibling = x->par->left;
                }

                if (sibling->left->color == true && sibling->right->color == true)
                {
                    sibling->color = false;
                    x = x->par;
                }

                else
                {
                    if (sibling->left->color == true)
                    {
                        sibling->right->color = true;
                        sibling->color = false;
                        leftRotate(sibling);
                        sibling = x->par->left;
                    }
                    sibling->color = x->par->color;
                    x->par->color = true;
                    sibling->left->color = true;
                    rightRotate(x->par);
                    x = root;
                }
            }
        }
        x->color = true;
    }

    // delete all nodes
    void deleteAll(Node *node)
    {
        if (node == T_NIL)
            return;
        deleteAll(node->left);
        deleteAll(node->right);
        deleteNode(node);
        nodeCount--;
    }
    void clearTree()
    {
        deleteAll(root);
        root = T_NIL;
        nodeCount = 0;
    }

    // check for an element
    Node *check(int givenID)
    {
        Node *temp = root;
        while (temp != T_NIL)
        {
            if (givenID < temp->id)
            {
                temp = temp->left;
            }
            else if (givenID > temp->id)
            {
                temp = temp->right;
            }
            else
            {
                return temp;
            }
        }

        return nullptr;
    }

    // display the RBT
    void display(Node *node, string &tree)
    {
        if (node == T_NIL)
            return;

        if (node->color == true)
        {
            tree = tree + to_string(node->id) + "_" + node->name;
            cout << dye::black(to_string(node->id) + "_" + node->name);
        }
        else
        {
            tree = tree + to_string(node->id) + "_" + node->name;
            cout << dye::red(to_string(node->id) + "_" + node->name);
        }

        if (node->left == T_NIL && node->right == T_NIL)
        {
            return;
        }

        tree = tree + "(";
        cout << "(";

        if (node->left != T_NIL)
        {
            display(node->left, tree);
        }

        tree = tree + ",";
        cout << ",";

        if (node->right != T_NIL)
        {
            display(node->right, tree);
        }

        tree = tree + ")";
        cout << ")";
    }

    // inorder traversal for list inventory
    void inOrder(Node *node, vector<string> &res)
    {
        if (node == T_NIL)
        {
            return;
        }
        inOrder(node->left, res);
        ostringstream oss;
        oss << node->id << " => " << node->name << " (" << node->stock << ")";
        res.push_back(oss.str());
        if (node->color == true)
        {
            cout << dye::black(node->id) << " => " << dye::black(node->name) << dye::black(" (") << dye::black(node->stock) << dye::black(")") << endl;
        }
        else
        {
            cout << dye::red(node->id) << " => " << dye::red(node->name) << dye::red(" (") << dye::red(node->stock) << dye::red(")") << endl;
        }

        inOrder(node->right, res);
    }
};