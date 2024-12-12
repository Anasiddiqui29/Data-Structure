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

    Node* search(Node *root , int value)
    {
        if(root == nullptr || value == root->key)
        {
            return root ; 
        }
        if(value < root->key) //value lies to the left of the tree
        {
            return search(root->leftChild , value) ; 
        }
        else
        {
            return search(root->rightChild , value) ; //otherwise search right
        }
    }

    Node *search(int value)
    {
        return search(root , value) ; 
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

    void identifyLocation(Node * node)
    {
        if (node == nullptr) 
        {
            cout << "Node not found in the tree." << endl;
            return;
        }
        if (node == root) 
        {
            cout << "Location: Root" << endl;
            return ; 
        } 
        else
        {
            // Find the parent of the node to determine its position
            Node *current = root ;
            while(current != nullptr)
            {
                if(current->key > node->key)
                {
                    if(current->leftChild == node)
                    {
                        cout << "Location: Left Child" << endl ; 
                        return ;
                    }
                    current = current->leftChild ; //update current to the left child
                }
                else
                {
                    if(current->key < node->key)
                    {
                        if(current->rightChild == node)
                        {
                            cout << "Location: Right Child" << endl ; 
                            return ; 
                        }
                        current = current->rightChild ; 
                    }
                    else
                    {
                        break ; 
                    }
                }
            }
        }
    }
    


} ;

int main()
{
    BinaryTree tree ; 

    int arr[] = {97 , 55 , 2 , 44 , 87} ;    
    
    tree.addNode(arr[0] , "Node 1") ;
    tree.addNode(arr[1] , "Node 2") ;
    tree.addNode(arr[2] , "Node 3") ;
    tree.addNode(arr[3] , "Node 4") ;
    tree.addNode(arr[4] , "Node 5") ;

    int value ; 

    cout << "Enter the value you want to search in the tree: " ; 
    cin >> value ; 

    if(tree.search(value) != nullptr)
    {
        cout << "Value found" << endl ; 
    }
    else
    {
        cout << "Value not found" << endl ; 
        //Inserting
        tree.addNode(value , "Node 6") ;
    }

    Node *foundNode = tree.search(value) ; 

    tree.identifyLocation(foundNode) ; 
}
