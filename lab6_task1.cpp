#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

class Stack
{
    string * arr ; //to store elements of the stack
    int top ; 
    int capacity ; 

    public:
    Stack(int size)
    {
        arr = new string[size] ; 
        capacity = size ; 
        top = -1 ;
    }

    bool isEmpty()
    {
        return (top == -1) ;
    }

    bool isFull()
    {
        return (top == capacity-1) ;
    }

    void push(string x)
    {
        if(isFull())
        {
            cout << "Stack Overflow" << endl ; 
        }
        else
        {
            cout << "Inserting " << x << endl ; 
            arr[++top] = x ; 
        }
    }

    string pop(string x)
    {
        if(isEmpty())
        {
            cout << "Stack is empty" << endl ; 
        }
        else
        {
            return arr[top--] ; //first it will return the element that has been deleted and then it will delete it since it is post decrement
        }
    }

    bool ispalindrome()
    {
        int mid = (capacity-1)/2 ; 
        for(int i=0 , j=capacity-1 ; i<mid ; i++ , j--)
        {
            
            if(arr[i]!=arr[j])
            {
                return false ; 
            }
            
        }
        return true ; 
    }

    void display()
    {
        for(int i=0 ; i<=top ; i++)
        {
            cout << arr[i] ;
        }
    }

};

int main()
{
    Stack stack(9) ; 
    stack.push("B") ;
    stack.push("O") ;
    stack.push("R") ;
    stack.push("R") ;
    stack.push("O") ;
    stack.push("W") ;
    stack.push("R") ;
    stack.push("O") ;
    stack.push("B") ;

    if(stack.ispalindrome())
    {
        cout << "It is palindrome" << endl  ;
    }
    else
    {
        cout << "It is not palindrome" << endl ; 
    }

    stack.display();

}