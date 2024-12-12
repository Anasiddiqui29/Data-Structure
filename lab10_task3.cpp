#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <cstdlib>

using namespace std ;

class Node
{
    public:
    int data ; 
    int priority ; 
    Node *next ;

    Node(int data , int priority)
    {
        this->data = data ; 
        this->priority = priority ; 
        next = nullptr ; 
    }
} ;

class PriorityQueue
{
    Node *head ; //points to the highest priority node ;

    public:
    PriorityQueue()
    {
        head = nullptr ; 
    }

    // Function to check if the priority queue is empty
    bool isEmpty() 
    {
        return head == nullptr;
    }

    //function to peek at the head element(highest priority)
    int peek()
    {
        if(!isEmpty())
        {
            return head->data ; 
        }
        else
        {
            return -1 ; 
        }
    }

    void push(int data , int p)
    {
        Node *newNode = new Node(data , p) ;

        //if the queue is empty or newNode has the highest priority
        if(head == nullptr || newNode->priority > head->priority)
        {
            newNode->next = head ; 
            head = newNode ; 
        }
        else
        {
            //traverse list to find the right spot
            Node *start = head ; 

            while(start->next != nullptr && start->next->priority >= newNode->priority)
            {
                start = start->next ;
            }
            newNode->next = start->next ; 
            start->next = newNode ; 
        }
    }

    //func to pop the highest priority element
    void pop()
    {
        if(isEmpty())
        {
            cout << "Queue is empty" << endl ; 
            return ; 
        }
        else
        {
            cout << "Task " << head->data << endl ;  ;
            cout << "Priority " << head->priority << endl ;
            Node *temp = head ; 
            head = head->next ; 
            delete temp ; 
        }
    }

    // Destructor to clean up the memory
    ~PriorityQueue() 
    {
        while (!isEmpty()) 
        {
            pop();
        }
    }

} ;

int main()
{
    int n ; 
    cout << "Enter the number of tasks: " ;
    cin >> n ;

    PriorityQueue pq;

    srand(time(0)) ;
    for(int i=0 ; i<n ; i++)
    {
        //to generate prority randomly
        int random = (rand() % 10) +1 ;

        pq.push(i+1 , random) ; //here i+1 represents the task number and random represents priority

    }

    for(int i=0 ; i<n ; i++)
    {
        pq.pop() ;
    }
}