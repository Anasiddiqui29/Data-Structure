#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

class Queue
{
    int *arr ; //array to store customer ID
    int rear = -1 ; //index at the end
    int front = -1 ; //index at the start
    int capacity ; 

    public:
    Queue(int size)
    {
        arr = new int[size] ;
        capacity = size ;
    }

    bool isFull()
    {
        return (rear == capacity-1) ; //rear has reached the last position in the array
    }

    bool isEmpty()
    {
        return (front==-1 || front > rear) ;
    }

    void enqueue(int x) // adding the element at the end(rear)
    {
        if(isFull())
        {
            cout << "Queue is full" << endl ; 
        }
        else
        {
            if(front == -1) //queue is empty
            {
                front = 0 ;
            }
            arr[++rear] = x ;
        }
    }

    void dequeue()
    {
        if(isEmpty())
        {
            cout << "Queue is empty" << endl ; 
        }
        else
        {
            if(front == rear) //only front element is left
            {
                front = -1 ; 
                rear = -1 ;
            }
            else
            {
                front++ ; 
            }
        }
    }

    void dislpay()
    {
        if(isEmpty())
        {
            cout << "Queue is empty" << endl ; 
        }
        else
        {
            for(int i=front ; i<=rear ; i++)
            {
                cout << arr[i] << endl ;
            } 
        }

    }

} ;

int main()
{
    Queue queue(7) ;

    queue.enqueue(13) ;
    queue.enqueue(7) ;
    queue.enqueue(4) ;
    queue.enqueue(1) ;
    queue.enqueue(6) ;
    queue.enqueue(8) ;
    queue.enqueue(10) ;

    cout << "Customers IDs are as follows: " << endl ; 
    queue.dislpay() ;
    
    //dequeue few customers
    queue.dequeue() ;
    queue.dequeue() ; 

    cout << "Queue after checkout" << endl ; 
    queue.dislpay() ;
}