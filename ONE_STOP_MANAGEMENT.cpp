#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>

using namespace std ;

/*One-Stop Management System Using Linear Data Structures*/

// This program implements a simplified One-Stop system for managing service requests and support agents. 
// Key features include:
// 1. Service Request (Ticket) Management: Allows adding, removing, searching, and sorting of tickets by priority, 
//    creation time, or customer name, using a linked list to manage ticket data.
// 2. Agent Management: Supports adding agents, assigning tickets based on priority and workload, 
//    and marking agent availability. A dynamic array is used for agent data management.
// 3. Ticket Resolution Logs: Tracks ticket transactions using a stack for closed ticket logs and a queue 
//    for pending tickets, prioritizing urgent requests for agent assignment.
// 4. Reporting & Analytics: Generates reports on open tickets, sorted by priority or creation time, 
//    and displays ticket resolution logs to analyze response times and system performance.
//
// Data structures used include linked lists (for tickets), dynamic arrays (for agents), 
// and stacks and queues (for transaction logs).

string getSearchAlgorithm();
string getSortAlgorithm()  ; 

//Implementing Service Request (Ticket) Management using Linked list
class Ticket
{
    public: 
    int ticket_id ; 
    string name ; 
    int priority ; 
    string sr_description ;
    time_t creation_time ;
    bool status ; //true for open and false for closed
    time_t tk_closedTime ; 
    
    Ticket(int ticket_id , string name , int priority , string sr_description)
    {
        this->ticket_id = ticket_id ; 
        this->name = name ; 
        this->priority = priority ; 
        this->sr_description = sr_description ; 
        creation_time = time(nullptr) ; 
        status = true ; //initially every ticket will be opened
        tk_closedTime = 0 ; 
    }
    //default constructor
    Ticket(){}

    time_t gettk_closedTime()
    {
        return tk_closedTime ; 
    }
    
    friend class AgentManager ;

    friend class TicketResolution ; 
} ;

class Node
{
    public:
    Ticket ticket ;  
    Node *next ; 

    Node(Ticket ticket)
    {
        this->ticket = ticket ; 
        next = nullptr ; 
    }

} ;

class TicketLinkedlist
{
    public:
    Node *head ; 

    TicketLinkedlist()
    {
        this->head = nullptr ; 
    }

    void addTicket(Ticket ticket) //inserting ticket at the beginning
    {
        Node *newNode = new Node(ticket) ; 

        if(head == nullptr)
        {
            head = newNode ;
            return ; 
        }

        newNode->next = head ; 
        head = newNode ;  
    }

    void removeTicket(int id)
    {
        if(head == nullptr)
        {
            cout << "List is empty" << endl ; 
            return ; 
        }

        //delete at the start
        if(head->ticket.ticket_id == id)
        {
            Node *temp = head ; 
            head = head->next ; 
            delete temp ; 
            return ; 
            
        }

        Node *current = head ; 
        while(current->next != nullptr)
        {
            if(current->next->ticket.ticket_id == id)
            {
                Node *temp = current->next ; 
                current->next = current->next->next ; 
                delete temp ; 
                return ; 
            }
            current = current->next ; 
        }
    }

    int countNodes()
    {
        int count = 0 ;

        Node *current = head ;

        while(current != nullptr)
        {
            count++ ; 
            current = current->next ; 
        }

        return count ; 
    }

    bool binarySearch(int id)
    {
        if(head == nullptr)
        {
            cout << "List is empty" << endl ; 
            return false; 
        }

        int left = 0 ; 
        int right = countNodes() - 1 ; //right most index
        
        while(left <= right)
        {
            int mid = left +(right-left)/2 ; 

            Node *midNode = getNode(mid) ; 

            if(midNode->ticket.ticket_id == id)
            {
                cout << "Ticket found" << endl ; 
                cout << "Details of the ticket" << endl ; 

                cout << "Ticket Name: " << midNode->ticket.name << endl ;
                cout << "Ticket Description: " << midNode->ticket.sr_description << endl ;
                cout << "Ticket Creation time: " << ctime(&midNode->ticket.creation_time) << endl ;
                cout << "Ticket ID: " << midNode->ticket.ticket_id << endl ;

                return true ; 
            }
            else
            {
                if(midNode->ticket.ticket_id < id)
                {
                    left = mid +1 ; //search right
                }
                else
                {
                    right = mid - 1 ; //search left
                }
            }
        }
        cout << "Ticket not found." << endl; // Notify if not found
        return false; // Return false if the ticket is not found
    }

    bool interpolationSearch(int id)
    {
        int pos;
        int lo = 0 ; 
        int hi = countNodes() - 1 ; //right most index
        
        Node *minNode = getNode(lo) ; 
        Node *maxNode = getNode(hi) ; 

        while(lo <= hi && id >= minNode->ticket.ticket_id && id <= maxNode->ticket.ticket_id) {
 
            // Probing the position with keeping
            // uniform distribution in mind.
            pos = lo
                + (((double)(hi - lo) / (maxNode->ticket.ticket_id - minNode->ticket.ticket_id))
                    * (id - minNode->ticket.ticket_id));

            Node *posNode = getNode(pos) ; 

            // Condition of target found
            if (posNode->ticket.ticket_id == id)
                //return pos;
                cout << "ID found" << endl ;
                return true ;
 
            // If x is larger, x is in right sub array
            if (posNode->ticket.ticket_id < id)
                lo = pos+1 ;
 
            // If x is smaller, x is in left sub array
            if (posNode->ticket.ticket_id > id)
                hi = pos-1 ;
        }
        cout << "Ticket not found" << endl ; 
        return false ; 
    }


    void searchTicket(int id) 
    {
        string searchAlgo = getSearchAlgorithm();

        if(searchAlgo == "interpolationsearch") 
        {
            interpolationSearch(id);
        } else if(searchAlgo == "binarysearch") {
        binarySearch(id);
        } 
        else {
            // Default search
            binarySearch(id); // or any default searching logic
        }
    }


    //to get node at specific index
    Node *getNode(int index)
    {
        Node *current = head ; 

        for(int i=0 ; i<index && current!= nullptr ; i++)
        {
            current = current->next ; 
        }

        return current ; 

    }

    int countTicket()
    {
        Node *current = head ; 

        int count =0 ;
        while(current != nullptr)
        {
            current = current->next ; 
            count++ ;
        }
        return count ; 

    }

    void bubbleSort(int choice) 
    { 
        if (!head || !head->next) 
        {return;} // If list is empty or has only one node, do nothing

        bool swapped;
        if(choice == 1){
        do {
            swapped = false;
            Node *current = head;
            while (current->next != nullptr) {
                if (current->ticket.priority > current->next->ticket.priority) {
                    swap(current->ticket, current->next->ticket);
                    swapped = true;
                }
                current = current->next;
            }
        }while(swapped) ;  }
        else
        {
            if(choice == 2)
            {
                do{
                swapped = false;
                Node *current = head;
                while (current->next != nullptr) {
                    if (current->ticket.creation_time > current->next->ticket.creation_time) {
                        swap(current->ticket, current->next->ticket);
                        swapped = true;
                    }
                    current = current->next;
                    }
                } while(swapped) ;  
            }
        else
        {
            do{
        swapped = false;
        Node *current = head;
        while (current->next != nullptr) {
            if (current->ticket.name > current->next->ticket.name) {
                swap(current->ticket, current->next->ticket);
                swapped = true;
            }
            current = current->next;
            }
        } while(swapped) ;
        }
        }
    }


    void Selectionsort(int choice)
    {
        if(choice == 1) //user selected priority
        {
            //Selection sort
            for(Node *current = head ; current !=nullptr ; current = current->next) 
            {
                Node *minNode =  current ; 
                Node *temp = current->next ; 

                while(temp != nullptr)
                {
                    //find min
                    if(temp->ticket.priority < minNode->ticket.priority)
                    {
                        minNode = temp ; 
                    }
                    temp = temp->next ; 
                }

                //Now swapping nodes
                swapNodes(current , minNode) ; 
            }
        }
        
        if(choice == 2) //user selected creation time
        {
            //selection sort using creation time
            for(Node *current = head ; current !=nullptr ; current = current->next) 
            {
                Node *minNode =  current ; 
                Node *temp = current->next ; 

                while(temp != nullptr)
                {
                    //find min
                    if(temp->ticket.creation_time < minNode->ticket.creation_time)
                    {
                        minNode = temp ; 
                    }
                    temp = temp->next ; 
                }

                //Now swapping nodes
                swapNodes(current , minNode) ; 
            }
        }
        
        if(choice == 3) //User selected customer names
        {
             //selection sort using creation time
            for(Node *current = head ; current !=nullptr ; current = current->next) 
            {
                Node *minNode =  current ; 
                Node *temp = current->next ; 

                while(temp != nullptr)
                {
                    //find min
                    if(temp->ticket.name < minNode->ticket.name)
                    {
                        minNode = temp ; 
                    }
                    temp = temp->next ; 
                }

                //Now swapping nodes
                swapNodes(current , minNode) ; 
            }
        }
    }

    void insertionSort(int choice) 
    {
        if (!head || !head->next) return;

        Node* sorted = nullptr;

        Node* current = head;
        if(choice == 1){
            while (current) 
            {
                Node* next = current->next; // Store next node
                if (!sorted || sorted->ticket.priority >= current->ticket.priority) {
                    // Insert at the beginning
                    current->next = sorted;
                    sorted = current;
                } 
                else {
                    Node* temp = sorted;
                    while (temp->next && temp->next->ticket.priority < current->ticket.priority) 
                    {
                        temp = temp->next;
                    }
                    current->next = temp->next;
                    temp->next = current;
                }
                current = next;
            }
            head = sorted;
        }
        else
        {
            if(choice == 2)
            {
                while (current) 
                {
                    Node* next = current->next; // Store next node
                    if (!sorted ||sorted->ticket.creation_time >= current->ticket.creation_time) {
                        // Insert at the beginning
                        current->next = sorted;
                        sorted = current;
                    } 
                    else {
                        Node* temp = sorted;
                        while (temp->next && temp->next->ticket.creation_time < current->ticket.creation_time) 
                        {
                            temp = temp->next;
                        }
                        current->next = temp->next;
                        temp->next = current;
                    }
                    current = next;
                }
                head = sorted;
            }
            else
            {
                while (current) 
                {
                    Node* next = current->next; // Store next node
                    if (!sorted ||sorted->ticket.name >= current->ticket.name) {
                        // Insert at the beginning
                        current->next = sorted;
                        sorted = current;
                    } 
                    else {
                        Node* temp = sorted;
                        while (temp->next && temp->next->ticket.name < current->ticket.name) 
                        {
                            temp = temp->next;
                        }
                        current->next = temp->next;
                        temp->next = current;
                    }
                    current = next;
                }
                head = sorted;
            }
        }
    }

   
    //swapping nodes function
    void swapNodes(Node *node1 , Node *node2)
    {
        if(node1 == node2) //identical nodes
        {
            return ; 
        }

         Node *prev1 = nullptr, *prev2 = nullptr, *current = head;

        // Find previous nodes for node1 and node2
        while (current != nullptr) 
        {
            if (current->next == node1) 
            {
                prev1 = current;
            }
            else
            { 
                if (current->next == node2) 
                {
                    prev2 = current;
                }
            }
            current = current->next;
        }

        // If node1 or node2 is the head, update head pointer
        if (node1 == head)
        { 
            head = node2;
        }
        else
        { 
            if (node2 == head)
            { 
                head = node1;
            }
        }
        // Swap the previous node pointers
        if(prev1)
        {
            prev1->next = node2;
        }
        if(prev2)
        { 
            prev2->next = node1;
        }
        // Swap the next pointers of node1 and node2
        Node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }

    //ADVANCE SORTING ALGORITHM
    //Quick Sort
    void quickSort(int choice) 
    {
        Node* tail = getTail(head);
        quickSortRecursive(head, tail , choice);
    }

    Node* getTail(Node* cur) {
        while (cur != nullptr && cur->next != nullptr) {
            cur = cur->next;
        }
        return cur;
    }

    Node* partition(Node* low, Node* high, Node** newLow, Node** newHigh , int choice) {
        Node* pivot = high; // Choose the last element as pivot
        Node* prev = nullptr;
        Node* cur = low;
        Node* tail = pivot;

        if(choice == 1)
        {
            while (cur != pivot) {
            
                if (cur->ticket.priority < pivot->ticket.priority) {
                if ((*newLow) == nullptr) {
                    (*newLow) = cur;
                }
                prev = cur;
                cur = cur->next;
            } 
            else {
                if (prev) {
                        prev->next = cur->next;
                    }
                    Node* tmp = cur->next;
                    cur->next = nullptr;
                    tail->next = cur;
                    tail = cur;
                    cur = tmp;
                }
            }
        }
        if(choice == 2)
        {
            while (cur != pivot) {
            
                if (cur->ticket.creation_time < pivot->ticket.creation_time) {
                if ((*newLow) == nullptr) {
                    (*newLow) = cur;
                }
                prev = cur;
                cur = cur->next;
            } 
            else {
                if (prev) {
                        prev->next = cur->next;
                    }
                    Node* tmp = cur->next;
                    cur->next = nullptr;
                    tail->next = cur;
                    tail = cur;
                    cur = tmp;
                }
            }
        }
        else
        {
            while (cur != pivot) {
            
                if (cur->ticket.name < pivot->ticket.name) {
                if ((*newLow) == nullptr) {
                    (*newLow) = cur;
                }
                prev = cur;
                cur = cur->next;
            } 
            else {
                if (prev) {
                        prev->next = cur->next;
                    }
                    Node* tmp = cur->next;
                    cur->next = nullptr;
                    tail->next = cur;
                    tail = cur;
                    cur = tmp;
                }
            }
        }

        if ((*newLow) == nullptr) {
            (*newLow) = pivot;
        }

        (*newHigh) = tail;

        return pivot;
    }

    Node* quickSortRecursive(Node* low, Node* high , int choice) {
        if (!low || low == high) {
            return low;
        }

        Node *newLow = nullptr, *newHigh = nullptr;
        Node* pivot = partition(low, high, &newLow, &newHigh  , choice);

        if (newLow != pivot) {
            Node* tmp = newLow;
            while (tmp->next != pivot) {
                tmp = tmp->next;
            }
            tmp->next = nullptr;

            newLow = quickSortRecursive(newLow, tmp , choice);

            tmp = getTail(newLow);
            tmp->next = pivot;
        }

        pivot->next = quickSortRecursive(pivot->next, newHigh , choice);

        return newLow;
    }

    //MERGE SORT
     Node* mergeSortedLists(Node* a, Node* b, int choice) 
     {
        if (!a) return b;
        if (!b) return a;

        Node* result = nullptr;

        // Sorting based on user choice
        if (choice == 1) { // Sort by priority
            if (a->ticket.priority <= b->ticket.priority) 
            {
                result = a;
                result->next = mergeSortedLists(a->next, b, choice);
            } 
            else 
            {
                result = b;
                result->next = mergeSortedLists(a, b->next, choice);
            }
            } else if (choice == 2) { // Sort by creation time
            if (a->ticket.creation_time <= b->ticket.creation_time)
            {
                result = a;
                result->next = mergeSortedLists(a->next, b, choice);
            } 
            else 
            {
                result = b;
                result->next = mergeSortedLists(a, b->next, choice);
            }
            } else if (choice == 3) { // Sort by customer name
            if (a->ticket.name <= b->ticket.name) 
            {
                result = a;
                result->next = mergeSortedLists(a->next, b, choice);
            } 
            else 
            {
                result = b;
                result->next = mergeSortedLists(a, b->next, choice);
            }
        }

        return result;
    }

    void splitList(Node* source, Node** front, Node** back) {
        Node* slow = source;
        Node* fast = source->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    Node* mergeSortRecursive(Node* node, int choice) 
    {
        if (node == nullptr || node->next == nullptr) 
        {
            return node;
        }

        Node* a;
        Node* b;

        splitList(node, &a, &b);

        a = mergeSortRecursive(a, choice);
        b = mergeSortRecursive(b, choice);

        return mergeSortedLists(a, b, choice);
    }

    void mergeSort(int choice) 
    {
        head = mergeSortRecursive(head, choice);
    }


    void sortTickets(int choice) 
    {
        string sortAlgo = getSortAlgorithm();

        if (sortAlgo == "bubblesort") 
        {
            bubbleSort(choice);
        } 
        else if(sortAlgo == "insertionsort")
        {
            insertionSort(choice) ; 
        }
        else if (sortAlgo == "quicksort") 
        {
            quickSort(choice);
        }
        else if(sortAlgo == "mergesort")
        {
            mergeSort(choice) ; 
        } 
        else 
        {
            // Default sort
            Selectionsort(choice); 
        }
}

    void display()
    {
        Node *current = head ; 
        if(head==nullptr)
        {
            cout << "List is empty" << endl ; 
            return ; 
        }

        while(current != nullptr)
        {
            cout << "Ticket ID: " << current->ticket.ticket_id << endl;
            cout << "Ticket Name: " << current->ticket.name << endl;
            cout << "Ticket Priority: " << current->ticket.priority << endl;
            cout << "Ticket Description: " << current->ticket.sr_description << endl;
            cout << "Creation Time: " << ctime(&current->ticket.creation_time); // Converts time_t to a readable format
            cout << "Status: " << (current->ticket.status ? "Open" : "Closed") << endl;
            cout << "-----------------------------------" << endl; 
            current = current->next; //update the current pointer
        }

    }

} ;

//Implemeting Agent Management 
class Agent
{
    public:
    int agent_id ; 
    string name ; 
    int *assigned_tickets ; //list of ticket ids
    bool availability ; 
    int num_assigned_tickets; // Track how many tickets are assigned 
    string status ; 

    Agent(int agent_id , string name)
    {
        this->agent_id = agent_id ; 
        this->name = name ; 
        availability = true ;
        assigned_tickets = new int[5] ; 
        num_assigned_tickets = 0 ;  
    }
    Agent(){}

};

class AgentManager
{
    Agent *agents ; 
    int capacity ; //current capacity of the array
    int size ; 

    public:

    friend class Ticket ; 

    AgentManager(int size)
    {
        agents = new Agent[size] ; //dynamically allocating memory for Agent array
        capacity = size ;  
        this->size = 0 ; 
    }

    void addAgent(Agent &agent)
    {
        if(capacity > size)
        {
            agents[size] = agent ; 
            size++ ;
        }
        else
        {
            cout << "Maximum capacity reached" << endl ; 
        }
    }
    
    void assignTicket(Ticket &ticket) 
    {
        int minTickets = 5; // Max capacity for an agent
        int bestAgentIndex = -1;
    
        // Find the agent with the least number of tickets who is also available
        for (int i = 0; i < size; ++i) 
        {
            if (agents[i].availability && agents[i].num_assigned_tickets < minTickets) {
                minTickets = agents[i].num_assigned_tickets;
                bestAgentIndex = i;
            }
        }
    
        // If a suitable agent was found, assign the ticket
        if (bestAgentIndex != -1) 
        {
            Agent &bestAgent = agents[bestAgentIndex];
            bestAgent.assigned_tickets[bestAgent.num_assigned_tickets] = ticket.ticket_id;
            bestAgent.num_assigned_tickets++;

            bestAgent.availability = (bestAgent.num_assigned_tickets < 5);
            bestAgent.status = bestAgent.availability ? "Available" : "Unavailable";
        
            cout << "Assigned Ticket " << ticket.ticket_id << " to Agent " << bestAgent.agent_id << std::endl;
        } 
        else 
        {
            cout << "No agents available to assign the ticket ID: " << ticket.ticket_id << std::endl;
        }
    }

    void bubbleSort()
    {
        for(int i=0 ; i<size ; i++)
    {
        for(int j=0 ; j<size-1-i; j++) //the last element will be sorted so no need to compare that element
        {
            if(agents[j].num_assigned_tickets > agents[j+1].num_assigned_tickets)
            {
                //swapping
                int temp = agents[j].num_assigned_tickets ; 
                agents[j].num_assigned_tickets = agents[j+1].num_assigned_tickets ; 
                agents[j+1].num_assigned_tickets = temp ; 
            }
        }
    }
    }

    void insertionSort()
    {
        for(int i=1 ; i<size ; i++) //starting from 1 because we are considering first element as sorted one
        {
            Agent key = agents[i] ;
            int j = i-1 ; //till sorted part

            while(j>=0 && agents[j].num_assigned_tickets > key.num_assigned_tickets)
            {
                agents[j+1] = agents[j] ;
                j-- ;  //j--;
            }
            agents[j] = key ; 
        }
    }

    void selectionSort()
    {
        for(int i=0 ; i<size ; i++)
        {
        int min=i ; 
        for(int j=i+1 ; j<size ; j++) // j=i+1
        {
            if(agents[j].num_assigned_tickets < agents[min].num_assigned_tickets)
            {
                min = j ;
            }
        }
        int temp = agents[min].num_assigned_tickets ;
        agents[min].num_assigned_tickets = agents[i].num_assigned_tickets ; 
        agents[i].num_assigned_tickets = temp ; 
        }
    }

    //QUICK SORT
     int partition(int low, int high) {
        int pivot = agents[high].num_assigned_tickets;
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (agents[j].num_assigned_tickets < pivot) {
                i++;
                swap(agents[i], agents[j]);
            }
        }
        swap(agents[i + 1], agents[high]);
        return (i + 1);
    }

    void quickSortHelper(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);

            quickSortHelper(low, pi - 1);
            quickSortHelper(pi + 1, high);
        }
    }

    void quickSort() 
    {
        quickSortHelper(0, size - 1);
    }

    //MERGE SORT
     void merge(int left, int mid, int right) 
     {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Agent *leftArray = new Agent[n1];
        Agent *rightArray = new Agent[n2];

        // Copy data to temp arrays
        for (int i = 0; i < n1; i++)
        {
            leftArray[i] = agents[left + i];
        }
        for (int i = 0; i < n2; i++)
            rightArray[i] = agents[mid + 1 + i];

        // Merge the temp arrays back into agents[left...right]
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArray[i].num_assigned_tickets <= rightArray[j].num_assigned_tickets) {
                agents[k] = leftArray[i];
                i++;
            } else {
                agents[k] = rightArray[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements, if any
        while (i < n1) {
            agents[k] = leftArray[i];
            i++;
            k++;
        }
        while (j < n2) {
            agents[k] = rightArray[j];
            j++;
            k++;
        }

        // Free memory
        delete[] leftArray;
        delete[] rightArray;
    }

    void mergeSortHelper(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            // Recursively sort both halves
            mergeSortHelper(left, mid);
            mergeSortHelper(mid + 1, right);

            // Merge the sorted halves
            merge(left, mid, right);
        }
    }

    void mergeSort() 
    {
        mergeSortHelper(0, size - 1);
    }

    void sortAgents() 
    {
        string sortAlgo = getSortAlgorithm();

        if (sortAlgo == "bubblesort") 
        {
            bubbleSort();
        } else if (sortAlgo == "quicksort") 
        {
            quickSort();
        } else if (sortAlgo == "mergesort") 
        {
            mergeSort();
        } else {
            // Default sort
            insertionSort();
        }
    }


    void display()
    {
        cout << "List of agents and their assigned tickets" << endl ; 

        for(int i=0 ; i<size ; i++)
        {
            cout << "Agent " << i+1 << " details" << endl ;

            cout << "Agent name: " << agents[i].name << endl ; 
            cout << "Agent ID: " << agents[i].agent_id << endl ;
            cout << "Agent number of assigned tickets: " << agents[i].num_assigned_tickets << endl ;
            cout << "Agent Assigned tickets" << endl ; 
            for(int j=0 ; j<5 ; j++)
            {
                cout << agents[i].assigned_tickets[j] << endl ; 
            } 
            cout << "Agent Status: " << agents[i].status << endl ;
            cout << "------------------------" << endl ; 
        }
        

    }

    ~AgentManager() 
    {
        delete[] agents; // Free allocated memory
    }

} ; 

//Implementing Tickets Resolution logs(Transaction log)STACK
class TicketResolution
{
    Ticket *log ; //dynamic array to maintain the closed ticket
    int top ; 
    int capacity ; 

    public:
    TicketResolution(int size) //User can decide the size of the stack
    {
        log = new Ticket[size] ; 
        capacity = size ; 
        top == -1 ; 

    }

    bool isFull()
    {
        return top == capacity -1 ; 
    }

    void push(Ticket &ticket)
    {
        if(isFull())
        {
            cout << "Log is currently full" << endl ; 
            return ; 
        }
        
        if(ticket.tk_closedTime != 0 && ticket.status == false) //ticket is closed and has closed time
        {   
            log[++top] = ticket ; 

            cout << "Ticket ID: " << ticket.ticket_id << " has been logged" << endl ; 
            return ; 
        }
        else
        {
            cout << "Ticket is not closed so cannot log" << endl ; 
            return ; 
        }
    }

    //Display the most recent ticket resolution logs
    void print()
    {
        if(top == -1)
        {
            cout << "No logs to display." << endl;
            return;
        }

        cout << "Displaying the most recent logs" << endl ; 

        for(int i=0 ; i<=top ; i++)
        {
            cout << "Ticket Name: " << log[i].name << endl ; 
            cout << "Ticket ID: " << log[i].ticket_id << endl ;
            cout << "Ticket Description" << log[i].sr_description << endl ;
            cout << "Ticket Creation time: " << ctime(&log[i].creation_time) << endl ;
            cout << "Ticket Closed time: "<< ctime(&log[i].tk_closedTime) << endl ;
            cout << "Staus : Closed" << endl ; 
        }
        cout << endl ; 


    } 

} ;

class PendingQueue
{
    Node *front ;
    Node *rear ; 

    TicketResolution *tr ; 

    public:
    PendingQueue(TicketResolution *tr)
    {
        front = nullptr ; 
        rear = nullptr ; 
        this->tr = tr ; 
    }

    bool isEmpty()
    {
        return front == nullptr ; 
    }

    void enqueue(Ticket &ticket)
    {
        Node *newNode = new Node(ticket) ; 

        if(isEmpty())
        {
            front = newNode ; 
            rear = newNode ; 
        }

        Node *current = front ; 
        Node *prev = nullptr ;

        //finding the correct position based on priority and creation time
        while(current != nullptr && 
        current->ticket.priority > ticket.priority ||
        current->ticket.priority == ticket.priority && current->ticket.creation_time < ticket.creation_time)
        {
            prev = current ; 
            current = current->next ; 
        }

        //inserting the ticket
        if(prev == nullptr) //means that the ticket has the highest priority hence must be queued at the front
        {
            newNode->next = front ; 
            front = newNode ; 
        }
        else
        {
            newNode->next = current ;
            prev->next = newNode ; 
            if(current == nullptr) //means that we have reached at the end (newNode has the lowest priority)
            {
                rear->next = newNode ; 
                rear = newNode ; 
            } 
        }
    }
    
    void dequeue()
    {
        if(isEmpty())
        {
            cout << "No tickets to entertain" << endl ; 
        }

        Node *temp = front ; 
        
        Ticket ticket = front->ticket ; //storing all the info of ticket that has to be deleted

        front = front->next ; //node(ticket) dequeued

        if(front == nullptr) //if queue is empty
        {
            rear = nullptr ; 
        }

        delete temp ; 

        ticket.status = false ; //ticket is closed 
        tr->push(ticket) ; //pushing the removed node into the stack resolution

        return ;
    }
} ; 



map<string,string> config;

void readConfig() 
{
    ifstream file("config.txt");
    string line;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        string key, value;
        if (getline(iss, key, '=') && getline(iss, value)) 
        {
            config[key] = value;
        }
    }
}

string getSortAlgorithm() 
{
    return config["sorting_algorithm"];
}

string getSearchAlgorithm() 
{
    return config["searching_algorithm"];
}

//Reporting and Analytics
int main()
{
    readConfig() ; 
    TicketLinkedlist ticketList; 

    Ticket ticket1(1, "Customer A", 5, "Issue with login");
    Ticket ticket2(2, "Customer B", 2, "Issue with Course Selection");
    Ticket ticket3(3, "Customer C", 1, "Issue with Timetable");
    Ticket ticket4(4, "Customer D", 3, "Class clash");
    Ticket ticket5(5, "Customer E", 4, "Too much University");

    // Adding the ticket to the linked list
    ticketList.addTicket(ticket1);
    ticketList.addTicket(ticket2); 
    ticketList.addTicket(ticket3);
    ticketList.addTicket(ticket4);
    ticketList.addTicket(ticket5);

    int choice ; 
    cout << "Press 1 for sorting list by Priority Number \nPress 2 for sorting list by Creation Time \nPress 3 for sorting list by Customer Name" << endl ; 
    cout << "Enter your Choice: " ;
    cin >> choice ; 

    ticketList.sortTickets(choice) ; 

    ticketList.display() ; 

    int t_id ; 
    cout << "Enter the ticket id you want to search: " ;
    cin >> t_id ; 
    //Performing binary search on sorted list
    ticketList.searchTicket(t_id) ; 

    //Agent Manager
    AgentManager agentManager(10) ; //Stack with a capacity of 10 agents

    Agent agent1(1 , "Agent A") ; 
    Agent agent2(2 , "Agent B") ; 
    Agent agent3(3 , "Agent C") ; 

    agentManager.addAgent(agent1) ; 
    agentManager.addAgent(agent2) ;
    agentManager.addAgent(agent3) ;

    //Assigning tickets to agents
    agentManager.assignTicket(ticket1) ; 
    agentManager.assignTicket(ticket2) ;
    agentManager.assignTicket(ticket3) ;
    agentManager.assignTicket(ticket4) ;
    agentManager.assignTicket(ticket5) ;

    cout << "------------------------------------" << endl ; 
    cout << "Displaying the details of Agents and their details" << endl ;

    //Displaying the agents and their details
    agentManager.display() ; 

    //Sorting based on assigned tickets
    agentManager.sortAgents() ; 

    //Resolution log 
    TicketResolution ticketRes(10) ; 

    PendingQueue pq(&ticketRes) ; 

    pq.enqueue(ticket1) ; 
    pq.enqueue(ticket2) ;
    pq.enqueue(ticket3) ;
    pq.enqueue(ticket4) ;
    pq.enqueue(ticket5) ;

    pq.dequeue() ;
    pq.dequeue() ; 
    pq.dequeue() ;

    //Showing the recent ticket resolution
    ticketRes.print() ;

}
