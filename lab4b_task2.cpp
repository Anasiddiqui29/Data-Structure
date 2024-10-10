#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

void SelectionSort(int arr[] , int N)
{
    for(int i=0 ; i<N ; i++)
    {
        int min = i ;
        for(int j= i+1 ; j<N ; j++)
        {
            if(arr[j]<arr[min])
            {
                min = j ; 
            }
        }
        //Now Swapping
        int temp = arr[min] ;
        arr[min] = arr[i] ; 
        arr[i] = temp ;   
    }
}

bool isUniformlyDistributed(int arr[] , int N)
{
    int diff = arr[1] - arr[0] ;
    for(int i = 2 ; i<N ; i++)
    {
        if(arr[i] - arr[i-1] != diff)
        {
            return false ; 
        }
    }
    return true ; 
}

int interpolationSearch(int arr[], int lo, int hi, int x)
{
    int pos;
 
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) 
    {
        pos = lo
              + (((double)(hi - lo) / (arr[hi] - arr[lo]))
                 * (x - arr[lo]));
 
        // Condition of target found
        if (arr[pos] == x)
        {
            return pos;
        }
        
        // If x is larger, x is in right sub array
        if (arr[pos] < x)
        {
            return interpolationSearch(arr, pos + 1, hi, x);
        }
        
        // If x is smaller, x is in left sub array
        if (arr[pos] > x)
        {
            return interpolationSearch(arr, lo, pos - 1, x);
        }
    }
    return -1;
}


int main()
{
    int size ; 
    cout << "Enter the size of data set: " ;
    cin >> size ; 

    int *database = new int[size] ;

    for(int i=0 ; i<size ; i++)
    {
        cout << "Enter the data " << i+1 << " : " ;
        cin >> database[i] ; 
    }

    int target ; 
    cout << "Enter the target value: " ;
    cin >> target ; 

    //Assuming data set is not sorted 
    SelectionSort(database , size) ; 

    int estimate ; 

    if(isUniformlyDistributed(database , size))
    {
        estimate = interpolationSearch(database , 0 , size-1 , target) ;
    }
    else
    {
        cout << "Error! Data is not uniformly distributed" << endl ; 
        delete[] database ; 
    }

    cout << "Target found at: " << estimate << endl ; 
     
}