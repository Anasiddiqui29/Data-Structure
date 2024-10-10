#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

class Node
{
    public:
    int data ; // to store the value
    Node *next ; // to store the pointer of the next node

    Node()
    {
        data = 0 ;
        next = nullptr ; 
    }

    //parameterized constructor
    Node(int data)
    {
        this->data = data ; 
        next = nullptr ;
    }


} ;

class SinglyLinkedlist
{
    public:
    Node *head ; // pointer to the first node(head) of the list

    //default constructor
    SinglyLinkedlist()
    {
        head = nullptr ;
    }

    void insertAtEnd(int val)
    {
        Node *newNode = new Node(val) ;

        if(head == nullptr)
        {
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
        }
    }

    void display()
    {
        Node *current = head ; 

        while(current != nullptr) //jub tk kai last tk nhi phooch jata
        {
            cout << current->data << "->" ;
            current = current->next ; 
        }

        cout << "NULL" << endl;

    }

    void modifylist()
    {
        SinglyLinkedlist evenlist ;
        SinglyLinkedlist oddlist ; 

        Node *current = head ; 

        while(current != nullptr)
        {
            if(current->data % 2 == 0)
            {
                //Even node
                evenlist.insertAtEnd(current->data) ;
            }
            else
            {
                //odd node
                oddlist.insertAtEnd(current->data) ;  
            }
         
            current = current->next;   
        }

        //Now concatenating the list
        if(evenlist.head != nullptr)
        {
            current = evenlist.head ; 
            while(current->next != nullptr)
            {
                current = current->next ; 
            }
            current->next = oddlist.head ; //as soon as evenlist ends the head of odd list is assigned to even tail pointer
            head = evenlist.head ; 
        }
        else
        {
            head = oddlist.head ;
        }

        cout << "Displaying Modified list" << endl ; 
        display() ; 
    }

} ;

int main()
{
    SinglyLinkedlist list; 
    //taking input from the user
    int size ; 
    cout << "Enter the size of the node: "  ; 
    cin >> size ;

    for(int i=0 ; i<size ; i++)
    {
        int value ; 
        cout << "Enter the value " << i+1 << " : " ;
        cin >> value ;

        list.insertAtEnd(value) ; 
    }
    cout << "Unsorted List" << endl ;
    list.display() ;
    list.modifylist() ;


}