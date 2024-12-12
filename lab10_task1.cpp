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

    int arr[] = {7,1,6,2,5,9,10,2} ;
    int N = sizeof(arr) / sizeof(arr[0]) ; 

    cout << "Max heap" << endl ; 

    buildHeapMax(arr , N);
    printHeap(arr , N) ;

    cout << "Min heap" << endl ; 

    buildHeapMin(arr , N) ; 
    printHeap(arr , N) ;
}