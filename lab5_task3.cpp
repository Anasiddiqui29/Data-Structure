#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std ;

class Node
{
    public:
    int data ; 
    Node * next ; 

    Node(int data)
    {
        this->data = data ; 
        next = nullptr ;
    }

} ;


class SinglyLinkedList
{
    public:
    Node * head ; 

    SinglyLinkedList()
    {
        head = nullptr ;
    }

    void insertAtbeg(int data)
    {
        Node * newNode = new Node(data) ; 

        if(head == nullptr) //if list is empty
        {
            head = newNode ; 
        }

        newNode->next = head ; 
        head = newNode ; 
    }

    int searchforVal(int data , Node *current)
    {
        //base case
        if(current == nullptr)
        {
            return 0 ; //if list is empty 
        } 

        if(current->data == data)
        {
            return 1 ; //if found then return 1
        }

        return searchforVal(data,current->next) ; //move to next node

    }

} ;

