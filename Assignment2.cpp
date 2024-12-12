#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono> 

/* Implementation of various tree structures, including Binary Search Tree (BST), AVL Tree, 
   and other balanced tree variants. This program compares the execution times for 
   different operations (such as insertion, deletion, and search) across these tree types 
   to analyze their efficiency in different scenarios. */

using namespace std ; 
using namespace chrono;

class Table
{
    public:
    int ID ;
    string name ; 
    int age ;
    Table *leftChild ;
    Table *rightChild ; 
    int height ; 

    Table(int ID , string name , int age)
    {
        this->ID = ID ; 
        this->name = name ;
        this->age = age ; 
        leftChild = nullptr ;
        rightChild = nullptr ; 
        height = 1 ; 
    }

    //default constructor
    Table(){}
} ;

//Implementing table using binary search tree
class BST_TABLE
{
    Table *root ; 

    public:
    BST_TABLE()
    {
        root = nullptr ;
    }   

    void Insert(int ID , string name , int age)
    {
        Table *newtable = new Table(ID , name , age) ;

        //if tree is empty
        if(root == nullptr)
        {
            root = newtable ;
        }
        else
        {
            Table *current = root ; 
            Table *parent ; 

            while(true)
            {
                parent = current ; 
                if(ID < current->ID) //based on the id of the table
                {
                    current = current->leftChild ; //since smaller so traverse left
                    if(current == nullptr) //as soon as we find the empty space we insert
                    {
                        parent->leftChild = newtable ;
                        return ; //exit the function after inserting
                    }
                }
                else
                {
                    current = current->rightChild ; 
                    if(current == nullptr)
                    {
                        parent->rightChild = newtable ; 
                        return ; 
                    }
                }
            }

        }
    }

    Table *findmin(Table *table)
    {
        //we will find the min to the left side of the tree
        while(table->leftChild != nullptr)
        {
            table = table->leftChild ;
        }
        return table ; 
    }

    Table *deleteTable(Table *root , int ID)
    {
        if(root == nullptr)
        {
            return root ; 
        }
        else
        {
            //if table to delete is leaf node
            if(ID < root->ID) //if the table to be deleted is on the left subtree
            {
                root->leftChild = deleteTable(root->leftChild , ID) ;
            }
            else
            {
                if(ID > root->ID) //if the table to be deleted is on the right subtree
                {
                    root->rightChild = deleteTable(root->rightChild , ID) ;
                }
                else
                {
                    //if the table to be deleted has one child
                    if(root->leftChild == nullptr)
                    {
                        Table *temp = root->rightChild ; 
                        delete root ; 
                        return temp ; 
                    }
                    else
                    {
                        if(root->rightChild == nullptr)
                        {
                            Table *temp = root->leftChild ; 
                            delete root ; 
                            return temp ; 
                        }
                    }
                }

                //if the table that has to be deleted has two child
                Table *temp = findmin(root->rightChild) ; 
                root->ID = temp->ID ;
                root->rightChild = deleteTable(root->rightChild , temp->ID) ;
            }
        }
    }

    void deletetable(int ID)
    {
        root = deleteTable(root , ID);
    }

    Table *Search(Table *root , int id)
    {
        if(root == nullptr || root->ID == id)
        {
            return root ;
        }

        //if id less than root id
        if(root->ID > id)
        {
            //traverse left
            return Search(root->leftChild , id) ;
        }
        else
        {
            //otherwise traverse right
            return Search(root->rightChild , id);
        }
    }

    Table *Search(int id)
    {
        return Search(root , id) ; 
    }
} ;

//Implementing table using AVL tree
int getHeight(Table *N)
{
    if(N == nullptr)
    {
        return 0 ; 
    }

    return N->height ; 
}

int getMax(int a , int b)
{
    return (a>b)?a:b ; //if true then return a else b 
}

Table *newNode(int ID , string name , int age)
{
    Table *node = new Table(ID , name , age) ;
    node->leftChild = nullptr ;
    node->rightChild = nullptr ; 
    node->height = 1 ; 
    return node ; 
}

Table *rightRotate(Table *y)
{
    Table *x = y->leftChild ; //x represents left child of y
    Table *temp = x->rightChild ; //temp is the right child of x 

    //perform rotation (check by drawing tree)
    x->rightChild = y ; 
    y->leftChild = temp ;

    y->height = getMax(getHeight(y->leftChild) , getHeight(y->rightChild)) ; 
    x->height = getMax(getHeight(x->leftChild) , getHeight(x->rightChild)) ; 

    return x ; 
}

Table *leftRotate(Table *x)
{
    Table *y = x->rightChild ; 
    Table *temp = y->leftChild ;  

    y->leftChild = x ; 
    x->rightChild = temp ; 
    
    y->height = getMax(getHeight(y->leftChild) , getHeight(y->rightChild)) ; 
    x->height = getMax(getHeight(x->leftChild) , getHeight(x->rightChild)) ; 

    return y ; 
}

int getBalance(Table *N)
{
    if(N==nullptr)
    {
        return 0 ; 
    }

    return getHeight(N->leftChild) - getHeight(N->rightChild) ; //Balance = height(leftsubtree) - height(rightsubtree)

}

Table *findmin(Table *node)
{
    while(node->leftChild != nullptr)
    {
        node = node->leftChild ;
    }

    return node ; 

}

class AVL_TABLE
{
    Table *root ;

    public:

    AVL_TABLE()
    {
        root = nullptr ; 
    }

    Table* InsertAvl(Table *node , int ID , string name , int age)
    {
        if(node == nullptr)
        {
            return newNode(ID , name , age) ; 
        }
        else
        {
            if(ID < node->ID) //insert left
            {
                node->leftChild = InsertAvl(node->leftChild , ID , name , age) ;
            }
            else
            {
                if(ID > node->ID) //insert to the right
                {
                    node->rightChild = InsertAvl(node->rightChild , ID , name , age) ; 
                }
                else
                {
                    return node ; 
                }
            }
        }
        //Now balancing
        node->height = 1+getMax(getHeight(node->leftChild) , getHeight(node->rightChild)) ; 

        int balance = getBalance(node) ; //if balance = 1 , 0 , -1 so no rotation required

        //left left subtree
        if(balance > 1 && ID < node->leftChild->ID)
        {
            return rightRotate(node) ;
        }

        //right right subtree
        if(balance < -1 && ID > node->rightChild->ID)
        {
            return leftRotate(node) ; 
        }

        //left right subtree
        if(balance > 1 && ID > node->leftChild->ID)
        {
            node->leftChild = leftRotate(node->leftChild) ;
            return rightRotate(node) ; 
        }

        //right left subtree
        if(balance < -1 && ID < node->rightChild->ID)
        {
            node->rightChild = rightRotate(node->rightChild) ;
            return leftRotate(node) ; 
        }

        return node ;
    }

    void insertAvl(int ID, string name, int age) 
    {
        root = InsertAvl(root, ID, name, age);
    }

    Table *deleteAvl(Table *root , int ID , string name , int age)
    {
        if(root == nullptr)
        {
            return root ; 
        }
        else
        {
            //if the node is the leaf node
            if(ID < root->ID)
            {
                root->leftChild = deleteAvl(root->leftChild , ID , name , age) ;
            }
            else
            {
                if(ID > root->ID)
                {
                    root->rightChild = deleteAvl(root->rightChild , ID , name , age) ;
                }
                else
                {
                    //if the node that has to be deleted has one child
                    if(root->leftChild == nullptr)
                    {
                        Table *temp = root->rightChild ; 
                        delete root ; 
                        return temp ; 
                    }
                    else
                    {
                        Table *temp = root->leftChild ; 
                        delete root ; 
                        return temp ; 
                    }
                }
                //if the node that has to be deleted has two childs
                Table  *temp = findmin(root->rightChild) ;
                root->ID = temp->ID ;
                root->rightChild = deleteAvl(root->rightChild , temp->ID , temp->name, temp->age) ;

            }
        }

        // Balancing
        root->height = 1 + getMax(getHeight(root->leftChild), getHeight(root->rightChild));

        int balance = getBalance(root);

        // Left Left Case
        if(balance > 1 && ID < root->leftChild->ID)
        {
            return rightRotate(root);
        }

        // Left Right Case
        if(balance > 1 && ID > root->leftChild->ID) 
        {
            root->leftChild = leftRotate(root->leftChild);
            return rightRotate(root);
        }

        // Right Right Case
        if(balance < -1 && ID > root->rightChild->ID)
        {
            return leftRotate(root);
        }
        // Right Left Case
        if(balance < -1 && ID < root->rightChild->ID) 
        {
            root->rightChild = rightRotate(root->rightChild);
            return leftRotate(root);
        }
        return root;
    }

    void deleteNodeAvl(int ID, string name, int age) 
    {
        root = deleteAvl(root, ID, name, age);
    }

    Table *SearchAvl(Table *root , int id)
    {
        if(root == nullptr || root->ID == id)
        {
            return root ;
        }

        //if id less than root id
        if(root->ID > id)
        {
            //traverse left
            return SearchAvl(root->leftChild , id) ;
        }
        else
        {
            //otherwise traverse right
            return SearchAvl(root->rightChild , id);
        }
    }
    
    Table* searchNode(int id) 
    {
        return SearchAvl(root, id);
    }
};

//Implementation of table using 2-3 tree
class TreeNode 
{
    public:
    Table* data[2];         // Up to 2 tables in a node
    TreeNode* children[3];  // Up to 3 children
    int numKeys;            // Number of keys in this node
    bool isLeaf;

    TreeNode(bool isLeaf) 
    {
        this->isLeaf = isLeaf;
        numKeys = 0;
        for (int i = 0; i < 3; i++) 
        {
            children[i] = nullptr;
        }
    }
};

class TwoThreeTree 
{
    private:
    TreeNode* root;

    // Function to split a full child node
    void splitChild(TreeNode* parent, int index, TreeNode* child) {
        TreeNode* newNode = new TreeNode(child->isLeaf);
        newNode->numKeys = 1;
        newNode->data[0] = child->data[1];

        if (!child->isLeaf) {
            newNode->children[0] = child->children[1];
            newNode->children[1] = child->children[2];
        }
        child->numKeys = 1;

        for (int i = parent->numKeys; i > index; i--) {
            parent->children[i + 1] = parent->children[i];
            parent->data[i] = parent->data[i - 1];
        }
        parent->children[index + 1] = newNode;
        parent->data[index] = child->data[0];
        parent->numKeys++;
    }

    // Insert a table in a non-full node
    void insertNonFull(TreeNode* node, Table* table) {
        int i = node->numKeys - 1;
        if (node->isLeaf) {
            while (i >= 0 && node->data[i]->ID > table->ID) {
                node->data[i + 1] = node->data[i];
                i--;
            }
            node->data[i + 1] = table;
            node->numKeys++;
        } else {
            while (i >= 0 && node->data[i]->ID > table->ID) {
                i--;
            }
            i++;
            if (node->children[i]->numKeys == 2) {
                splitChild(node, i, node->children[i]);
                if (node->data[i]->ID < table->ID) {
                    i++;
                }
            }
            insertNonFull(node->children[i], table);
        }
    }

    public:
    TwoThreeTree() 
    {
        root = nullptr;
    }

    // Insert a new table into the 2-3 tree
    void insert(int ID, string name, int age) 
    {
        Table* newTable = new Table(ID, name, age);
        if (root == nullptr) 
        {
            root = new TreeNode(true);
            root->data[0] = newTable;
            root->numKeys = 1;
        } 
        else 
        {
            if (root->numKeys == 2) 
            {
                TreeNode* newRoot = new TreeNode(false);
                newRoot->children[0] = root;
                splitChild(newRoot, 0, root);
                int i = (newRoot->data[0]->ID < ID) ? 1 : 0;
                insertNonFull(newRoot->children[i], newTable);
                root = newRoot;
            } 
            else 
            {
                insertNonFull(root, newTable);
            }
        }
    }

    // Search for a table by ID
    Table* search(TreeNode* node, int ID) {
        int i = 0;
        while (i < node->numKeys && ID > node->data[i]->ID) {
            i++;
        }
        if (i < node->numKeys && node->data[i]->ID == ID) {
            return node->data[i];
        }
        if (node->isLeaf) {
            return nullptr;
        }
        return search(node->children[i], ID);
    }

    Table* search(int ID) 
    {
        return search(root, ID);
    }

    // Print the 2-3 tree in-order (for demonstration purposes)
    void inOrder(TreeNode* node) 
    {
        if (node != nullptr) 
        {
            int i;
            for (i = 0; i < node->numKeys; i++) 
            {
                if (!node->isLeaf) 
                {
                    inOrder(node->children[i]);
                }
                cout << "ID: " << node->data[i]->ID << ", Name: " << node->data[i]->name << ", Age: " << node->data[i]->age << endl;
            }
            if (!node->isLeaf) 
            {
                inOrder(node->children[i]);
            }
        }
    }

    void inOrder() 
    {
        inOrder(root);
    }

    void deleteNode(TreeNode* node, int ID) {
    int idx = 0;
    while (idx < node->numKeys && node->data[idx]->ID < ID) {
        idx++;
    }

    if (idx < node->numKeys && node->data[idx]->ID == ID) {
        // Case 1: Node is a leaf
        if (node->isLeaf) {
            for (int i = idx; i < node->numKeys - 1; ++i) {
                node->data[i] = node->data[i + 1];
            }
            node->numKeys--;
            return;
        } 
        // Case 2: Node is an internal node
        else {
            if (node->children[idx]->numKeys > 1) {
                Table* predecessor = getPredecessor(node, idx);
                node->data[idx] = predecessor;
                deleteNode(node->children[idx], predecessor->ID);
            } else if (node->children[idx + 1]->numKeys > 1) {
                Table* successor = getSuccessor(node, idx);
                node->data[idx] = successor;
                deleteNode(node->children[idx + 1], successor->ID);
            } else {
                mergeNodes(node, idx);
                deleteNode(node->children[idx], ID);
            }
        }
    } else {
        // Case 3: Key is not found in node and we need to recurse
        if (node->isLeaf) {
            cout << "The key " << ID << " does not exist in the tree." << endl;
            return;
        }

        bool flag = ((idx == node->numKeys) ? true : false);
        if (node->children[idx]->numKeys == 1) {
            fillNode(node, idx);
        }

        if (flag && idx > node->numKeys) {
            deleteNode(node->children[idx - 1], ID);
        } else {
            deleteNode(node->children[idx], ID);
        }
    }
}

// Helper functions for delete operation

Table* getPredecessor(TreeNode* node, int idx) {
    TreeNode* current = node->children[idx];
    while (!current->isLeaf) {
        current = current->children[current->numKeys];
    }
    return current->data[current->numKeys - 1];
}

Table* getSuccessor(TreeNode* node, int idx) {
    TreeNode* current = node->children[idx + 1];
    while (!current->isLeaf) {
        current = current->children[0];
    }
    return current->data[0];
}

void mergeNodes(TreeNode* node, int idx) {
    TreeNode* child = node->children[idx];
    TreeNode* sibling = node->children[idx + 1];

    child->data[1] = node->data[idx];
    child->data[2] = sibling->data[0];

    if (!child->isLeaf) {
        child->children[1] = sibling->children[0];
        child->children[2] = sibling->children[1];
    }

    for (int i = idx + 1; i < node->numKeys; ++i) {
        node->data[i - 1] = node->data[i];
    }

    for (int i = idx + 2; i <= node->numKeys; ++i) {
        node->children[i - 1] = node->children[i];
    }

    child->numKeys += sibling->numKeys + 1;
    node->numKeys--;
    delete(sibling);
}

void fillNode(TreeNode* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->numKeys > 1) {
        borrowFromPrev(node, idx);
    } else if (idx != node->numKeys && node->children[idx + 1]->numKeys > 1) {
        borrowFromNext(node, idx);
    } else {
        if (idx != node->numKeys) {
            mergeNodes(node, idx);
        } else {
            mergeNodes(node, idx - 1);
        }
    }
}

void borrowFromPrev(TreeNode* node, int idx) {
    TreeNode* child = node->children[idx];
    TreeNode* sibling = node->children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; --i) {
        child->data[i + 1] = child->data[i];
    }

    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->data[0] = node->data[idx - 1];
    if (!child->isLeaf) {
        child->children[0] = sibling->children[sibling->numKeys];
    }

    node->data[idx - 1] = sibling->data[sibling->numKeys - 1];
    child->numKeys += 1;
    sibling->numKeys -= 1;
}

void borrowFromNext(TreeNode* node, int idx) {
    TreeNode* child = node->children[idx];
    TreeNode* sibling = node->children[idx + 1];

    child->data[child->numKeys] = node->data[idx];
    if (!child->isLeaf) {
        child->children[child->numKeys + 1] = sibling->children[0];
    }

    node->data[idx] = sibling->data[0];
    for (int i = 1; i < sibling->numKeys; ++i) {
        sibling->data[i - 1] = sibling->data[i];
    }

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

// Delete function exposed to the user
    void deleteTable(int ID) 
    {
        if (root == nullptr) {
            cout << "The tree is empty." << endl;
            return;
        }
        deleteNode(root, ID);

        if (root->numKeys == 0) 
        {
            TreeNode* temp = root;
            if(root->isLeaf) 
            {
                root = nullptr;
            } 
            else 
            {
                root = root->children[0];
            }
            delete temp;
        }
    }
};

//Performance analysis
void generateDummyData(int size, int* dataID, string* dataName, int* dataAge) 
{
    srand(time(0)); // Seed the random number generator with the current time

    for (int i = 0; i < size; ++i) 
    {
        dataID[i] = rand() % 100000;           // Random ID from 0 to 99999
        dataName[i] = "Name_" + to_string(rand() % 10000);  // Random name like "Name_1234"
        dataAge[i] = 20 + (rand() % 30);       // Random age between 20 and 49
    }
}

// Measure insertion time
void measureInsertionTime(int size, int* IDs, string* names, int* ages, AVL_TABLE& avl, TwoThreeTree& twoThree, BST_TABLE& bst) 
{
    clock_t start, end;

    // Measure AVL insertion
    start = clock();
    for (int i = 0; i < size; ++i) {
        avl.insertAvl(IDs[i], names[i], ages[i]);
    }
    end = clock();
    cout << "AVL Tree Insertion Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure 2-3 Tree insertion
    start = clock();
    for (int i = 0; i < size; ++i) 
    {
        twoThree.insert(IDs[i], names[i], ages[i]);
    }
    end = clock();
    cout << "2-3 Tree Insertion Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure BST insertion
    start = clock();
    for (int i = 0; i < size; ++i) {
        bst.Insert(IDs[i], names[i], ages[i]);
    }
    end = clock();
    cout << "Binary Search Tree Insertion Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}

// Measure deletion time
void measureDeletionTime(int size, int* IDs,string *names,int *ages, AVL_TABLE& avl, TwoThreeTree& twoThree, BST_TABLE& bst) 
{
    clock_t start, end;

    // Measure AVL deletion
    start = clock();
    for (int i = 0; i < size; ++i)
     {
        avl.deleteNodeAvl(IDs[i] , names[i] , ages[i]);
    }
    end = clock();
    cout << "AVL Tree Deletion Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure 2-3 Tree deletion
    start = clock();
    for (int i = 0; i < size; ++i) 
    {
        twoThree.deleteTable(IDs[i]);
    }
    end = clock();
    cout << "2-3 Tree Deletion Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure BST deletion
    start = clock();
    for (int i = 0; i < size; ++i) 
    {
        bst.deletetable(IDs[i]);
    }
    end = clock();
    cout << "Binary Search Tree Deletion Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}

// Measure search time
void measureSearchTime(int size, int* IDs, AVL_TABLE& avl, TwoThreeTree& twoThree, BST_TABLE& bst) 
{
    clock_t start, end;

    // Measure AVL search
    start = clock();
    for (int i = 0; i < size; ++i) {
        avl.searchNode(IDs[i]);
    }
    end = clock();
    cout << "AVL Tree Search Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure 2-3 Tree search
    start = clock();
    for (int i = 0; i < size; ++i) {
        twoThree.search(IDs[i]);
    }
    end = clock();
    cout << "2-3 Tree Search Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // Measure BST search
    start = clock();
    for (int i = 0; i < size; ++i) {
        bst.Search(IDs[i]);
    }
    end = clock();
    cout << "Binary Search Tree Search Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}

int main() 
{
    srand(time(0));  // Seed for random data

    int sizes[] = {1000, 10000, 50000};  // Array of dataset sizes

    AVL_TABLE avl;
    TwoThreeTree twoThree;
    BST_TABLE bst;

    for(int size : sizes) 
    {
        cout << "Testing with " << size << " records:" << endl;

        int* IDs = new int[size];
        string* names = new string[size];
        int* ages = new int[size];
        
        generateDummyData(size, IDs, names, ages);

        cout << "Insertion Times:" << endl;
        measureInsertionTime(size, IDs, names, ages, avl, twoThree, bst);

        cout << "Search Times:" << endl;
        measureSearchTime(size, IDs, avl, twoThree, bst);

        cout << "Deletion Times:" << endl;
        measureDeletionTime(size, IDs,names, ages,avl, twoThree, bst);

        delete[] IDs;
        delete[] names;
        delete[] ages;
        
        cout << endl;
    }

    return 0;
}
