#include <iostream>
#include <string>

using namespace std ;

class Node
{
    public:
    int key ; 
    Node *right ; 
    Node *left ; 
    int height ; 

    Node(int key)
    {
        this->key = key ; 
        right = nullptr ; 
        left = nullptr ; 
        height = 1 ; 
    }
} ;

int getHeight(Node *N)
{
    if(N == nullptr)
    {
        return 0 ;
    }

    return N->height ; 
}

int getBalance(Node *N)
{
    if(N == nullptr)
    {
        return 0 ; 
    }

    return getHeight(N->left) - getHeight(N->right) ; //balance = height(left sub) - height(right sub)
}

int getmax(int a , int b)
{
    if(a>b)
    {
        return a ; 
    }
    else{
        return b ; 
    }
}

Node *rightRotate(Node *y)
{
    Node *x = y->left ; 
    Node *temp = x->right ; 

    //rotation
    x->right = y ; 
    y->left = temp ; 

    //update heights
    x->height = getmax(getHeight(x->left) , getHeight(x->right)) ;
    y->height = getmax(getHeight(y->left) , getHeight(y->right)) ; 

    return x ; 
}

Node *leftRotate(Node *x)
{
    Node *y = x->right ; 
    Node *temp = y->left ; 

    //rotation
    y->left = x ; 
    x->right = temp ; 

    //update heights
    x->height = getmax(getHeight(x->left) , getHeight(x->right)) ;
    y->height = getmax(getHeight(y->left) , getHeight(y->right)) ; 

    return y ; 
}

Node *insert(Node *node , int key)
{
    if(node == nullptr)
    {
        return new Node(key) ; 
    }

    if(key < node->key)
    {
        node->left = insert(node->left , key) ; 

    }
    else
    {
        if(key > node->key)
        {
            node->right = insert(node->right , key) ; 
        }
        else
        {
            return node ; 
        }
    }

    //update height
    node->height = 1+ getmax(getHeight(node->left) , getHeight(node->right)) ;

    //Now balancing
    //first calculate balance factor
    int balance = getBalance(node) ; 

    //left left subtree
    if(balance > 1 && key < node->left->key)
    {
        return rightRotate(node) ; 
    }

    //right right subtree
    if(balance < -1 && key > node->right->key)
    {
        return leftRotate(node) ; 
    }

    //left right subtree
    if(balance > 1 && key > node->left->key)
    {
        //double rotation
        node->left = leftRotate(node->left) ;
        return rightRotate(node) ; 
    }

    //right left subtree
    if(balance < -1 && key < node->right->key)
    {
        //double rotation
        node->right = rightRotate(node->right) ; 
        return leftRotate(node) ;
    }
    return node ; 
}

Node *findmin(Node *node)
{
    while(node->left !=nullptr) //since min will always be at the left side of the tree
    {
        node = node->left ; 
    }
    return node ; 
}

void search(Node *node,int key)
{
    bool found = false ; 
    if(node == nullptr)
    {
        cout << "Tree is empty" << endl ; 
        cout << "Inserting " << key << endl ; 
        node = insert(node , key) ;
        found = true ; 
    }

    if(node->key == key)
    {
        cout << key << " found" << endl ; 
        found = true ; 
    }
    else
    {
        if(node->key < key) //search right
        {
            search(node->right , key) ;
        }
        else
        {
            if(node->key > key) //search left
            {
                search(node->left , key) ;
            }
        }
    }

    if(found)
    {
       cout << key << " found" << endl ; 
    }
    else
    {
        insert(node , key) ; 
    }
}

void display(Node *node)
{
    if (node == nullptr)  // base case to stop recursion
    {
        return;
    }
    //preorder
    cout << node->key << "\t" ; 
    display(node->left) ; 
    display(node->right) ; 
}

int main()
{
    Node *root = nullptr ; 
    root = insert(root , 1) ; 
    root = insert(root , 2) ; 
    root = insert(root , 3) ; 
    root = insert(root , 4) ; 
    root = insert(root , 5) ; 
    root = insert(root , 6) ;
    root = insert(root , 7) ;

    search(root , 4) ;  
}