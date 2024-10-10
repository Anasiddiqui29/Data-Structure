#include <iostream>
#include <cstring>
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
    }
}; 

class PriorityQueue
{
    Node *head ; 

    public:
    PriorityQueue()
    {
        head = nullptr ; 
    }

    //Function to peek at the highest element
    int peek()
    {
        if(!isEmpty())
        {
            return head->data ;
        }
        else
        {
            cout << "Queue is empty" << endl ; 
        }
    }

    void enqueue(int data , int p) //push function
    {
        Node *newNode = new Node(data , p) ;

        //if the queue is empty or the node has the highest priority than head
        if(head == nullptr || head->priority > p)
        {
            newNode->next = head ; 
            head = newNode ; 
        }
        else
        {
            //traverse to find the right spot
            Node *current = head ; 
            while(current->next != nullptr && current->next->priority < p)
            {
                current = current->next ;      
            }
            newNode->next = current->next ;
            current->next = newNode ;
            
        }
    }

    void dequeue() //function to delete the highest priority element that is head (pop)
    {
        if(isEmpty())
        {
            cout << "Queue is empty" << endl ; 
        }  
        else
        {
            Node *temp = head ;
            head = head->next ; 
            delete temp ;
        }
    }

    bool isEmpty()
    {
        return (head == nullptr) ; 
    }

    ~PriorityQueue() 
    {
        while (!isEmpty()) 
        {
            dequeue();
        }
    }
};

int main()
{
    //for simplification we are assuming there are four tasks
    int CPU_req[4] , memory[4] , storage[4] , et[4] , priority[4] ;

    for(int i=0 ; i<4 ; i++)
    {
        cout << "Task " << i+1 << endl ;
        cout << "Execution Time: " ;
        cin >> et[i] ;
        cout << "CPU Usage: " ;
        cin >> CPU_req[i] ;
        cout << "Memory(MB): " ;
        cin >> memory[i] ; 
        cout << "Storage(GB): " ;
        cin >> storage[i] ;
        cout << "-----------------------------------"<< endl ;
        priority[i] = (CPU_req[i] + memory[i] + storage[i]) / et[i] ;//to calculate the priority value
    }

    PriorityQueue pq ;
    pq.enqueue(1 , priority[0]) ;
    pq.enqueue(2 , priority[1]) ;
    pq.enqueue(3 , priority[2]) ;
    pq.enqueue(4 , priority[3]) ;

    for(int i =0 ; i<4 ; i++)
    {
        cout << "Task " << pq.peek() << " executed" << endl ; 
        pq.dequeue() ; //After executing removing the element that has the highest priority 
    }

}