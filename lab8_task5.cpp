#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    int key;
    string name;
    Node* leftChild;
    Node* rightChild;

    Node(int key, string name) {
        this->key = key;
        this->name = name;
        rightChild = nullptr;
        leftChild = nullptr;
    }

    void tostring() {
        cout << name << " has the key " << key << endl;
    }
};

class BianryTree {
public:
    Node* root;

    BianryTree() {
        root = nullptr;
    }

    void addNode(int key, string name) 
    {
        Node* newNode = new Node(key, name);

        if (root == nullptr) 
        { // if tree is empty
            root = newNode;
        } 
        else 
        {
            Node* current = root;
            Node* parent;
            while (true) 
            {
                parent = current;
                if (current->key > key) 
                {
                    current = current->leftChild; // traverse left
                    if (current == nullptr) 
                    {
                        parent->leftChild = newNode; // insert to the left
                        return; // break the loop
                    }
                } 
                else 
                {
                    current = current->rightChild; // traverse right
                    if (current == nullptr) 
                    {
                        parent->rightChild = newNode; // insert to the right
                        return;
                    }
                }
            }
        }
    }

    void PrintTree(Node* node) 
    {
        if (node != nullptr) 
        {
            PrintTree(node->leftChild);
            node->tostring();
            PrintTree(node->rightChild);
        }
    }

    void PrintTree() 
    {
        PrintTree(root);
    }

    void merge(Node* node) 
    {
        if (node != nullptr) 
        {
            addNode(node->key, node->name); // Add current node to the tree
            merge(node->leftChild);  // Recur for left subtree to add left nodes
            merge(node->rightChild); // Recur for right subtree to add right nodes
        }
    }

    void Merge(BianryTree& tree) 
    {
        merge(tree.root);
    }

};

int main() 
{
    BianryTree tree1;

    tree1.addNode(5, "Node 1");
    tree1.addNode(3, "Node 2");
    tree1.addNode(6, "Node 3");
    tree1.addNode(2, "Node 4");
    tree1.addNode(4, "Node 5");

    cout << "Tree 1:" << endl;
    tree1.PrintTree();
    cout << "--------------------------------" << endl;

    BianryTree tree2;

    tree2.addNode(2, "Node 1");
    tree2.addNode(1, "Node 2");
    tree2.addNode(3, "Node 3");
    tree2.addNode(7, "Node 4");
    tree2.addNode(6, "Node 5");

    cout << "Tree 2:" << endl;
    tree2.PrintTree();
    cout << "--------------------------------" << endl;

    // Merging them
    tree2.Merge(tree1);

    cout << "Merged Tree:" << endl;
    tree2.PrintTree();
}
