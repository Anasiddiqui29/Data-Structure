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

    Node *reverselist(Node *head)
    {
        Node *prev = nullptr ; 
        Node *current = head ; 
        Node *next = nullptr ; 

        while(current != nullptr)
        {
            next = current->next ; //to store next
            current->next = prev ; //reverse current node's next pointer
            //move pointer one position ahead
            prev = current ; 
            current = next ; 
        }
        return prev ; 
    }

    bool checkPalindrome(int size)
    {
        if (head == nullptr || head->next == nullptr) 
        {
            return true;  // A list with 0 or 1 element is a palindrome
        }

        // Step 1: Find the middle of the linked list
        Node *slow = head;
        Node *fast = head;

        while (fast != nullptr && fast->next != nullptr) 
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        //Reverse the second half of the list
        Node* secondHalfHead = reverselist(slow);
        Node *firstHalfHead = head ; 

        Node *secondHalfCopy = secondHalfHead; // To restore the list later
        while (secondHalfHead != nullptr) 
        {
            if (firstHalfHead->data != secondHalfHead->data) 
            {
                return false;
            }
            //to move to the next pointer
            firstHalfHead = firstHalfHead->next;
            secondHalfHead = secondHalfHead->next;
        }

        //restore the second half list
        reverselist(secondHalfCopy) ; 

        return true ; 

        
    }


} ;

int main()
{
    SinglyLinkedlist list; 
    //taking input from the user
    int size ; 
    cout << "Enter the size of the node: "  ; 
    cin >> size ;

    for(int i=0 ; i<size ; i++)
    {
        int value ; 
        cout << "Enter the value " << i+1 << " : " ;
        cin >> value ;

        list.insertAtEnd(value) ; 
    }

    if(list.checkPalindrome(size))
    {
        cout << "Linked List is a Palindrome" << endl ; 
    }
    else
    {
        cout << "Linked List is not a Palindrome" << endl ;
    }

}