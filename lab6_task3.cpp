#include <iostream>
#include <cstdlib>
#include <string>

using namespace std ;

class Node
{
    public:
    string data ; 
    Node *next ; 

    Node(string data)
    {
        this->data = data ;
        this->next = next ;
    }
}; 

//Implementing stack with Singly Linked List
class Stack
{
    Node *head ; 

    public:
    Stack()
    {
        head = nullptr ;
    }

    bool isEmpty()
    {
        return (head == nullptr) ;
    }
    
    void push(string data) //insert in the beginning
    {
        Node *newNode = new Node(data) ; 

        //to check if the memory allocation for newNode failed
        if(!newNode)
        {
            cout << "Stack Overflow" << endl ; 
        }

        newNode->next = head ; 
        head = newNode ; 
    }

    void pop()
    {
        if(isEmpty())
        {
            cout << "Stack Underflow" << endl ; 
        }
        else
        {
            Node *temp = head ;
            head = head->next ; 
            delete temp ;
        } 
    }

    void printStack()
    {
        if(isEmpty())
        {
            cout << "Stack is empty" << endl ; 
        }
        else
        {
            Node * current = head ; 
            while(current != nullptr)
            {
                cout << current->data << " " ;
                current = current->next ; 
            }
        }
    }
};

int main()
{
    Stack stack ;

    stack.push("x") ; 
    stack.push("=") ; 
    stack.push("12") ;
    stack.push("+") ;
    stack.push("13") ;
    stack.push("-") ;
    stack.push("5(0.5+0.5)") ;
    stack.push("+") ;
    stack.push("1") ;

    int result = 12 + 13 - 5 + 1 ;

    stack.push(to_string(result)) ;

    stack.printStack() ; 

}