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

class Circular
{
    public:
    Node *head ; 
    Node *tail ; 

    Circular()
    {
        head = nullptr ;
        tail = nullptr ;
    }

    void insertAtEnd(int val)
    {
        Node *newNode = new Node(val) ;

        if(head == nullptr)
        {
            head = newNode ; 
            tail = newNode ; 
            tail->next = head ; 
        }
        else
        {
            tail->next = newNode ; 
            tail = newNode ;
            tail->next = head ; 
        }
    }

    void insertAtstart(int val)
    {
        Node *newNode = new Node(val) ;

        if(head == nullptr)
        {
            head = newNode ; 
            tail = newNode ;
            tail->next = head ; 
        }
        else
        {
            tail->next = newNode ;
            newNode->next = head ;  
            head = newNode ; 
        }
    }

    int size() 
    {
        if (head == nullptr) return 0;

        int count = 1;
        Node* current = head;
        while (current->next != head) {
            current = current->next;
            count++;
        }
        return count;
    }

    void insertAtanypos(int pos,int val)
    {
        Node * newNode = new Node(val) ; 

        //if list is empty
        if(head == nullptr)
        {
            head = newNode ; 
            tail = newNode ;
            tail->next = head ; 
        }
        else
        {
            if(pos == size()) //if to insert at the end
            {
                tail->next = newNode ; 
                tail = newNode ;
                tail->next = head ; 
            }
            else
            {
                Node *current = head ; 
                for(int i=1 ; i<pos ; i++)
                {
                    current = current->next ;
                }
                //after stopping just right before pos
                newNode->next = current->next ; 
                current->next = newNode ; 

            }
        }
    }

    void deleteNode(int val)
    {
        if(head == nullptr)
        {
            return ; 
        }

        Node *current = head ; 
        Node *prev = nullptr ; 

        while(current->next != head) //since circular so last wala head ko hi point kr raha houga
        {
            if(current->data == val)
            {
                if(prev == nullptr) //if the node that is to be deleted is head
                {
                    Node *temp = head ;
                    while(temp->next != head)
                    {
                        temp = temp->next ;
                    }
                    temp->next = head->next ; 
                    delete head ; 
                    head = temp->next ; 
                }
                else
                {
                    prev->next = current->next ; 
                    delete current ; 
                }
            }
            prev = current ;
            current = current->next ; 
        }

        //check if last node is to be deleted
        if(current->data == val)
        {
            if(prev == nullptr) //if this is the only node that is to be deleted
            {
                delete head ; 
                head = nullptr ; 
            }
            else
            {
                prev->next = head ; 
                delete current ; 
            }
        }
    }

    void display()
    {
        if(head == nullptr)
        {
            cout << "Empty list" << endl; 
        }
        
        Node *current = head ; 
        do
        {
            cout << current->data << "->" ;
            current = current->next ;
        }while(current != head) ;
         

        cout << "NULL" << endl ; 

    }

};

