#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

class Node
{
    public:
    
    int data ;
    Node *next ; // pointer to store the address of next node
    Node *prev ; //pointer to store the address of previous node

    //default constructor
    Node()
    {
        data = 0 ; 
        next = nullptr ; 
        prev = nullptr ;
    }

    //parameterized parameter
    Node(int data)
    {
        this->data = data ; 
        next = nullptr ; 
        prev = nullptr ; 
    }

} ; 

class DoubleLinkedList
{
    public:
    Node *head ; 

    DoubleLinkedList()
    {
        head = nullptr ;
    }

    void insertAtstart(int data)
    {
        Node *newNode = new Node(data) ; 

        if(head == nullptr)
        {
            newNode->next = head ;
            newNode->prev = head ; 
            head = newNode ; 
        }
        else
        {
            head->prev = newNode ; 
            newNode->next = head ; 
            head = newNode ; 
        }
    }

    void insertAtend(int data)
    {
        Node *newNode = new Node(data) ; 

        if(head == nullptr)
        {
            newNode->next = head ;
            newNode->prev = head ; 
            head = newNode ; 
        }
        else
        {
            Node *current = head ; 

            while(current->next != nullptr)
            {
                current = current->next ; 
            }

            current->next = newNode ; 
            newNode->prev = current ; 
             
        }
    }

    void display()
    {
        if(head == nullptr)
        {
            cout << "List is empty" << endl ; 
        }

        Node *current = head ; 
        while(current != nullptr)
        {
            cout << current->data << "->" ;
            current = current->next ; 
        }
        cout << endl ; 

    }
} ;

void concatenateLists(DoubleLinkedList &L , DoubleLinkedList &M)
    {
        if(L.head == nullptr) //L is empty
        {
            L.head = M.head ; 
            L.head->prev = M.head->prev ;
        }
        else
        {
            if(M.head == nullptr)
            {
                //L remains
            }
            else
            {
                L.head->prev = M.head ; 
                M.head->prev = L.head->prev ; 
                L.head->prev = M.head ; 
            }
        }
        //Now L and M list is concatenated in single L list
    }

int main()
{
    DoubleLinkedList L  , M; 
    //taking input from the user
    int sizeL ; 
    cout << "Enter the size of the node L: "  ; 
    cin >> sizeL ;

    for(int i=0 ; i<sizeL ; i++)
    {
        int value ; 
        cout << "Enter the value " << i+1 << " : " ;
        cin >> value ;

        L.insertAtend(value) ; 
    }

    int sizeM ; 
    cout << "Enter the size of the node M: "  ; 
    cin >> sizeM ;

    for(int i=0 ; i<sizeM ; i++)
    {
        int value ; 
        cout << "Enter the value " << i+1 << " : " ;
        cin >> value ;

        M.insertAtend(value) ; 
    }

    concatenateLists(L , M) ;

    L.display() ; 

}