#include<iostream>
#include <string>

using namespace std ;

#include<iostream>
#include <string>

using namespace std ;

class Node
{
    public:
    int key;
    string name ; 
    Node *leftChild ; 
    Node *rightChild ; 

    Node(string name , int key)
    {
        this->key = key ; 
        this->name = name ; 
        leftChild = nullptr ; 
        rightChild = nullptr ; 
    }

    string tostring()
    {
        return name + " has the key " + to_string(key) + "\n" ;
    }
} ;

class BinaryTree
{
    public:
    Node * root ; 

    BinaryTree()
    {
        this->root = nullptr ;
    }

    void addNode(int key , string name)
    {
        Node *newNode = new Node(name , key) ;

        if(root == nullptr)
        {
            root = newNode ; //if tree is empty then newNode will be the root
        }
        else
        {
            Node *current = root ; 
            Node *parent ; //to keep the track of the prev node

            while(true)
            {
                parent = current ; 
                if(key < current->key)
                {
                    current = current->leftChild ; //if key is smaller then traverse to the left side of the tree
                    if(current == nullptr) //jese hi khali jagah milay so insert the key
                    {
                        parent->leftChild = newNode ; 
                        return ; //to end the while loop
                    }

                }
                else
                {
                    current = current->rightChild ; 
                    if(current == nullptr)
                    {
                        parent->rightChild = newNode ; 
                        return ; 
                    }
                }
            }
        }
    }

    bool isFull(Node *current)
    {
        //base case
        if(current == nullptr) //if node is null then it is considered full
        {
            return true ; 
        }

        //if the node has exactly two children , then recursively check its subtree
        if(current->leftChild != nullptr && current->rightChild != nullptr)
        {
            return isFull(current->leftChild) && isFull(current->rightChild) ; 
        }

        //if the node is leaf(has no children) , it means it is full
        if(current->leftChild == nullptr && current->rightChild == nullptr)
        {
            return true ; 
        }

        return false ; 
    }

    bool isComplete(Node *current , int index , int totalnodes)
    {
         //base case
        if(current == nullptr) //if node is null then it is considered full
        {
            return true ; 
        }

        if(index >= totalnodes)
        {
            return false ; 
        }

        //recursively check right and left subtrees with updated indices
        return isComplete(current->leftChild , 2*index +1 , totalnodes) &&
               isComplete(current->rightChild , 2*index +2 , totalnodes) ;

       
    }

    void PrintTree(Node *node)
    {
        if(node !=nullptr)
        {
            PrintTree(node->leftChild) ;
            cout << node->tostring() ; 
            PrintTree(node->rightChild) ; 
        }
    }

    void PrintTree()
    {
        PrintTree(root) ; 

    }

} ;

int main()
{
    BinaryTree tree ; 

    int arr[] = {1 , 2 , 3 , 4 , 5} ;    

    tree.addNode(arr[0] , "Node 1") ;
    tree.addNode(arr[1] , "Node 2") ;
    tree.addNode(arr[2] , "Node 3") ;
    tree.addNode(arr[3] , "Node 4") ;
    tree.addNode(arr[4] , "Node 5") ;

    //inserting 6 7 and 8 as per demand by the question
    tree.addNode(6 , "Node 6") ;
    tree.addNode(7 , "Node 7") ;
    tree.addNode(8 , "Node 8") ;

    //printing tree
    tree.PrintTree() ;
    
}