#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

int getMax(int arr[] , int n)
{
    int max = arr[0] ; 
    for(int i = 1 ; i<n ; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i] ; 
        }
    }
    return max ;
}  

void countSort(int arr[] , int n , int exp)
{
    int *output = new int[n] ; 
    int count[10] = {0} ;

    for(int i=0 ; i<n ; i++)
    {
        count[(arr[i] / exp)%10]++ ;
    }

    for(int i=0 ; i<10 ; i++)
    {
        count[i] += count[i-1] ; 
    }

    for(int i =n-1 ; i>=0 ; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i] ; 
    }

    for(int i=0 ; i<n ; i++)
    {
        arr[i] = output[i] ;
    }
}

// function to implement radix sort 
void radix_sort(int arr[], int n) 
{ 
    // maximum element from an array 
    int m = getMax(arr , n) ;

    for (int pos = 1; (m / pos) > 0; pos *= 10) 
    { 
        countSort(arr, n, pos); 
    } 
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
    radix_sort(arr , 10) ;
    printArray(arr , 10);
}