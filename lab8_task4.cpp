#include<iostream>
#include <string>

using namespace std ;

class Node
{
    public:
    int key ; 
    string name ; 
    Node *leftChild ; 
    Node *rightChild ; 

    Node(int key , string name)
    {
        this->key = key ; 
        this->name = name ; 
        rightChild = nullptr ; 
        leftChild = nullptr ; 
    }

    void tostring()
    {
        cout << name << " has the key " << key << endl ; 
    }


} ;

class BianryTree
{
    public:
    Node *root ; 

    BianryTree()
    {
        root = nullptr ;
    }
    
    void addNode(int key , string name)
    {
        Node *newNode = new Node(key , name) ;

        if(root == nullptr) //if tree is empty
        {
            root = newNode ; 
        } 
        else
        {
            Node *current = root ; 
            Node *parent ; 
            while(true)
            {
                parent = current ; 
                if(current->key > key)
                {
                    current = current->leftChild ; //traverse left
                    if(current == nullptr)
                    {
                        parent->leftChild = newNode ; //insert to the left
                        return ; //break the loop
                    }

                }
                else
                {
                    if(current->key < key)
                    {
                        current = current->rightChild ;
                        if(current == nullptr)
                        {
                            parent->rightChild = newNode ; //insert to the right
                            return ; 
                        }
                    }
                }
            }
        }
    }

    int ceilfloor(int x , int choice)
    {
        Node *current = root ; 
        bool found = false ; 
        int count = 0 ;
        if(choice == 1) //ceil the value
        {
            x = x+1 ; 

        }
        else
        {
            x = x-1 ;
        }
             
        while(current != nullptr)
        {
            if(current->key == x)
            {
                cout << "Found key: " << current->key << " at node with name: " << current->name << endl;
                count++ ;  
                found = true ; 
            }

            if(x < current->key) //traverse left
            {
                current = current->leftChild ; 
            }
            else
            {
                current = current->rightChild ; 
            }
        }
        if(!found)
        {
            cout << "No matching node found for " << (choice == 1 ? "ceil" : "floor") << " value " << x << endl;
            return -1;
        }
        return count;  
    }


    void PrintTree(Node *node)
    {
        if(node != nullptr)
        {
            PrintTree(node->leftChild) ; 
            node->tostring() ;
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
    BianryTree tree ;

    tree.addNode(10 , "Node 1") ;
    tree.addNode(5 , "Node 2") ;
    tree.addNode(11 , "Node 3") ;
    tree.addNode(4 , "Node 4") ;
    tree.addNode(7 , "Node 5") ;
    tree.addNode(8 , "Node 6") ;

    tree.PrintTree() ; 

    int x ; 
    cout << "Enter the value: " ;
    cin >> x ; 

    int choice;
    cout << "Press 1 to ceil the value \nPress 2 to floor the value" << endl ;
    cout << "Enter your choice: " ; 
    cin >> choice ; 

    int res = tree.ceilfloor(x , choice) ; 

    cout << "Number of occurence: " << res ; 

}