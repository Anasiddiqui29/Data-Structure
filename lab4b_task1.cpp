#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

void bubblesort(int arr[] , int N)
{
    for(int i=0 ; i<N ; i++)
    {
        for(int j=0 ; j<N-i-1 ; j++) //last element is sorted so no need to compare that
        {
            if(arr[j] > arr[j+1]) //ascending order
            {
                int temp = arr[j+1] ;
                arr[j+1] = arr[j] ; 
                arr[j] = temp ; 
            }
        }
    }
}

int binarySearch(int arr[], int low , int high , int x)
{
    while(low <= high)
    {
        int mid = low + (high-low) / 2 ; 

        if(x == arr[mid])
        {
            return mid ; 
        }
        if(x > mid)
        {
            low = mid+1 ; 
        }
        else
        {
            high = mid-1 ; 
        }
    }
    return -1 ; 
}

int main()
{
    int emp_id[] = {11 , 10 , 44 , 24 , 45, 65} ;
    int size = sizeof(emp_id) / sizeof(emp_id[0]) ;
    
    //for binary search , array must be sorted
    bubblesort(emp_id , size) ; 

    int roll_no = 230575 ; // 23k-0575 

    //Extracting last two digits of the roll number
    int last_twodigit = roll_no % 100 ;  

    int index = binarySearch(emp_id , 0 , size-1 , last_twodigit) ;

    for(int i=0 ; i<size ; i++)
    {
        cout << emp_id[i] << " " ;
    }

    cout << "Employee ID: " << roll_no << " found at index " << index  << endl ;

}