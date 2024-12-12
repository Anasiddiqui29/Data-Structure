#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

int partition(int arr[] , int start ,  int end)
{
    int m = start + (end - start)/2 ; 

    int pivot = arr[m] ;
    int count = 0 ; 
    for(int i=start ; i<end ; i++)
    {
        if(arr[i] < pivot)
        {
            count++ ;
        }
    }

    //giving the pivot element its correct position
    int pivotIndex = start + count ; 
    //swapping
    int temp = arr[m] ; 
    arr[m] = arr[pivotIndex] ; 
    arr[pivotIndex] = temp ; 

    int i=start , j = end ; 
    while(i < pivotIndex && j > pivotIndex)
    {
        if(arr[i] <= pivot)
        {
            i++ ; 
        }
        if(arr[j] > pivot)
        {
            j-- ; 
        }
        //swapping
        int temp = arr[i] ; 
        arr[i] = arr[j] ; 
        arr[j] = temp ; 
    }
    return pivotIndex ; 
}

void quicksort(int arr[] , int start , int end)
{
    //base case
    if(start >= end)
    {
        return ; 
    }

    int p = partition(arr , start , end) ;
    //sort the left part
    quicksort(arr , start , p) ;
    //sort the right part
    quicksort(arr , p+1 , end) ; 

}

void printArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{   
    int arr[10] ; 

    for(int i=0 ; i<10 ; i++)
    {
        cout << "Enter element " << i+1 << " : " ;
        cin >> arr[i] ;
    }

    cout << "Unsorted Array" << endl ; 
    printArray(arr , 10) ;
    cout << "------------------------------------" << endl ; 
    cout << "Sorted Array in Ascending Order" << endl ; 
    quicksort(arr , 0 , 9);
    printArray(arr , 10) ; 
}