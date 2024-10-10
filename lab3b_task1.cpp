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

    void insertAtanypos(int data , int pos)
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
            

        }


    }

    void deleteNode(int data)
    {
        if (head == nullptr)
            return;

        Node* current = head;
        do{
            if (current->data == data) 
            {
                if (current == head) 
                { // If the node to be deleted is the head
                    if (head->next == head) 
                    { // If head is the only node
                        delete head;
                        head = nullptr;
                        return;
                    } 
                    else 
                    {
                        head->prev->next = head->next;
                        head->next->prev = head->prev;
                        Node* temp = head;
                        head = head->next; //head kai next walai ko head bana diya since we are deleting head
                        delete temp;
                        return;
                    }
                } 
                else 
                { // If the node to be deleted is not the head
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    return;
                }
            }
            current = current->next;
        } while (current != head);
    }

    void insertAtanypos(int data , int pos)
    {
        Node* newNode = new Node(data);

        if (head == nullptr) 
        { // Case 1: No list at all, create a new one
            head = newNode; // newNode will be the head
            head->next = head; 
            head->prev = head; // since circular
        } 
        else 
        {
            Node* temp = head;
            int count = 1;

            // Traverse the list to find the position and that node jis ke peechai insert karna hai node
            while (count < pos && temp->next != head) 
            {
                temp = temp->next;
                count++;
            }

            if (pos == 1) 
            { // Insertion at the beginning
                newNode->next = head;
                newNode->prev = head->prev;
                head->prev->next = newNode;
                head->prev = newNode;
                head = newNode; // Update head to the new node
            } 
            else if (temp->next == head && count < pos) 
            { // Insertion at the end
                newNode->next = head;
                newNode->prev = temp;
                temp->next = newNode;
                head->prev = newNode;
            } 
            else 
            { // Insertion in the middle
                newNode->next = temp;
                newNode->prev = temp->prev;
                temp->prev->next = newNode;
                temp->prev = newNode;
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