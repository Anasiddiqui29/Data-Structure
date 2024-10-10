#include <iostream>

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

class SinglyLinkedlist
{
    public:
    Node *head ; // pointer to the first node(head) of the list

    //default constructor
    SinglyLinkedlist()
    {
        head = nullptr ;
    }

    void insertAtEnd(int val)
    {
        Node *newNode = new Node(val) ;

        if(head == nullptr)
        {
            head = newNode ;
        }
        else
        {
            Node *current = head ;
            while(current->next != nullptr)
            {
                current = current->next ;
            }

            current->next = newNode ; 
        }
    }

    void extractandReversealternate()
    {
        if (head == nullptr || head->next == nullptr) 
        {
                return;
        }

            Node *odd = head;
            Node *even = head->next;
            Node *evenStart = even;

            while (odd != nullptr && even != nullptr) 
            {
                odd->next = even->next;
                odd = odd->next;
                if (odd != nullptr) 
                {
                    even->next = odd->next;
                    even = even->next;
                }
            }

            Node *prev = nullptr;
            Node *current = evenStart;
            Node *next = nullptr;

            while (current != nullptr) 
            {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            Node *tail = head;
            while (tail->next != nullptr) 
            {
                tail = tail->next;
            }

            tail->next = prev;
    }

    void display()
    {
        Node *current = head ; 

        while(current != nullptr) //jub tk kai last tk nhi phooch jata
        {
            cout << current->data << "->" ;
            current = current->next ; 
        }

        cout << "NULL" << endl;

    }
} ;

int main()
{
    SinglyLinkedlist list ; 
    int size ; 
    cout << "Enter the size of the list: "  ; 
    cin >> size ; 

    for(int i=0 ; i<size ; i++)
    {
        int value ; 
        cout << "Enter the element at " << i+1 << " : " ; 
        cin >> value ; 

        list.insertAtEnd(value) ; 
    }

    list.extractandReversealternate() ; 

    list.display() ; 

}