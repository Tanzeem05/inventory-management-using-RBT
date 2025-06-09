#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include "inventory_system.h"
using namespace std;

int main()
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Error opening input or output file." << endl;
        return 1;
    }

    inventory_system IS;
    string line;

    while (getline(inputFile, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string func;
        ss >> func;

        if (func == "AI")
        {
            int id, stock;
            string name, tempName;
            ss >> id;
            ss >> ws;
            if (ss.peek() == '"')
            {
                getline(ss, tempName, '"');
                getline(ss, name, '"');
            }
            else
            {
                ss >> name;
            }

            ss >> stock;
            string tree;
            IS.addItem(id, name, stock, tree);
            outputFile << tree << endl;
        }
        else if (func == "BI")
        {
            int productID, quantity;
            ss >> productID >> quantity;
            string tree;
            IS.buyItem(productID, quantity, tree);
            outputFile << tree << endl;
        }
        else if (func == "CI")
        {
            string msg;
            int productID;
            ss >> productID;
            IS.checkItem(productID, msg);
            outputFile << msg;
        }
        else if (func == "Clr")
        {
            bool status = IS.clearInventory();
            string msg;
            if (status)
            {
                msg = "successful";
            }
            else
            {
                msg = "unsuccessful";
            }
            outputFile << msg << endl;
        }
        else if (func == "S")
        {
            int size = IS.InventorySize();
            outputFile << to_string(size) << endl;
            cout << size << endl;
        }
        else if (func == "Em")
        {
            outputFile << (IS.isEmpty() ? "yes" : "no") << endl;
            cout << (IS.isEmpty() ? "yes" : "no") << endl;
        }
        else if (func == "Itr")
        {
            vector<string> treeStr;
            IS.listInventory(treeStr);
            for (const auto &it : treeStr) {
                outputFile << it << endl;
            }
        }
        else{
            outputFile << "Invalid command: " + func;
        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}