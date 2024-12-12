#include <iostream>
#include <string>

using namespace std ;

void swap(int &a , int &b)
{
    int temp = a ;
    a = b ; 
    b = temp ; 
    return ; 
}

void heapifyMax(int arr[] , int N , int i)
{
    int largest = i ; 
    //left and right child index formula
    int left = (2*i) + 1 ; 
    int right = (2*i) + 2 ; 

    if(left<N && arr[left]>arr[largest]) //if left child is greater than largest value that is set initially
    {
        largest = left ; 
    }

    if(right<N && arr[right]>arr[largest])
    {
        largest = right ;
    }

    if(largest != i) //if the largest is not the root
    {
        swap(arr[i] , arr[largest]) ; //swap them(make largest the root)
        heapifyMax(arr , N , largest) ; 
    }
}

void buildHeapMax(int arr[] , int N)
{
    int startIndex = (N/2) -1 ; 

    for(int i = startIndex ; i>=0 ; i--)
    {
        heapifyMax(arr , N , i) ;
    }
}

void heapifyMin(int arr[] , int N , int i)
{
    int smallest = i ; 
    int left = (2*i) +1 ; 
    int right = (2*i) +2 ;

    if(left<N && arr[left]<arr[smallest])
    {
        smallest = left ; 
    }

    if(right<N && arr[right]<arr[smallest])
    {
        smallest = right ; 
    }

    if(smallest != i)
    {
        swap(arr[i] , arr[smallest]) ;
        heapifyMin(arr , N , smallest) ;
    }
}

void buildHeapMin(int arr[] , int N)
{
    int startIndex = (N/2) -1 ; 

    for(int i = startIndex ; i>=0 ; i--)
    {
        heapifyMin(arr , N , i) ;
    }
}

//we always delete root
void deleteRoot(int arr[] , int N)
{
    //to get the last element
    int lastElement = arr[N-1] ;

    arr[0] = lastElement ; //replace it with the root

    //decrease the size of the heap
    N = N-1 ;

    heapifyMin(arr , N , 0) ;

}

void printHeap(int arr[], int N)
{
    for (int i = 0; i < N; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main()
{

    int arr[] = {35,33,42,10,14,19,27,44,26,31} ;
    int N = sizeof(arr) / sizeof(arr[0]) ; 

    cout << "Min heap" << endl ; 

    buildHeapMin(arr , N) ;
    printHeap(arr , N) ;

    cout << "Deleting its root node...." << endl ;

    deleteRoot(arr , N) ;

    buildHeapMax(arr , N) ;

    cout << "Max heap after deleting root" << endl ;

    printHeap(arr , N) ;

}