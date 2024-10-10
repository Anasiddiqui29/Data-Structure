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

class DoubleCircularLinkedList
{
    public:
    Node *head ; 

    //Default constructor
    DoubleCircularLinkedList()
    {
        head = nullptr ;
    }

    void insertAtstart(int data)
    {
        Node *newNode = new Node(data) ; 

        if(head == nullptr) //there is no list at all
        {
            head = newNode ; //newNode will be the head
            head->next = head ; 
            head->prev = head ; //since circular
        }
        else
        {
            newNode->next = head ; 
            newNode->prev = head->prev ; 
            head->prev->next = newNode ; //last node ka next point karain head pr jo kai ab newNode hai
            head->prev = newNode ; 
            head = newNode ; 
        }
    }

    void insertAtend(int data)
    {
        Node *newNode = new Node(data) ; 

        if(head == nullptr) //there is no list at all
        {
            head = newNode ; //newNode will be the head
            head->next = head ; 
            head->prev = head ; //since circular
        }
        else
        {
            newNode->next = head ; 
            newNode->prev = head->prev ; 
            head->prev->next = newNode ; 
            head->prev = newNode ; 
        }
    }

    void swapNodes(int index1 , int index2)
    {
        Node *current1 = head ; 
        Node *current2 = head ;
        

        for(int i=0 ; i<index1-1 ; i++)
        {
            current1 = current1->next ; //index1 pai jo node tha wo current1 mai store hogaya hai
        }
         

        Node *swap2 ;

        for(int i=0 ; i<index2-1 ; i++)
        {
            current2 = current2->next ; 
        }
         //index2 pai jo node tha wo current2 mai store hogaya hai

        //Now swapping

        //if they are adjacent
        if(current1->next == current2)
        {
            current1->prev->next = current2 ; //node1 kai peechay walai ka next pointer  current2 pr point kr raha
            current1->next->prev = current2 ; //node1 kai agai walai ka peechay wala pointer current2 pr point kr raha
            current1->next = current2->next ;
            current2->prev = current1->prev ; 
            current1->prev = current2 ; 
            current2->next = current1 ; 
        }
        else
        {
            if(current2->next == current1)
            {
                current2->prev->next = current1 ; //node2 kai peechay walai ka next pointer  current1 pr point kr raha
                current2->next->prev = current1 ; //node2 kai agai walai ka peechay wala pointer current1 pr point kr raha
                current2->next = current1->next ;
                current1->prev = current2->prev ; 
                current2->prev = current1 ; 
                current1->next = current2 ;
            }
            else
            {
                 // Nodes are not adjacent
                Node* tempPrev = current1->prev;
                Node* tempNext = current1->next;

                current1->prev = current2->prev;
                current1->next = current2->next;
                current2->prev->next = current1; //current2 kai peechay walai ka agay wala pointer pehlai current2 pr kr raha tha laikin current1 pr
                current2->next->prev = current1;

                current2->prev = tempPrev;
                current2->next = tempNext;
                tempPrev->next = current2;
                tempNext->prev = current2;
            }
        } 
    }

    void display()
    {
        if(head == nullptr)
        {
            cout << "Empty list" << endl ; 
        }
        Node *current = head ; 

        do{
            cout << current->data << " " ;
            current = current->next ;
        }while(current != head) ; 

        cout << endl ;
    }


} ;

int main() 
{
    DoubleCircularLinkedList list;

    // Insert nodes at the end
    list.insertAtend(10);
    list.insertAtend(20);
    list.insertAtend(30);
    list.insertAtend(40);
    list.insertAtend(50);

    cout << "Original List: ";
    list.display();

    // Swap nodes at index 1 and 3
    list.swapNodes(2, 3);

    cout << "List after swapping nodes at index 1 and 3: ";
    list.display();
}
