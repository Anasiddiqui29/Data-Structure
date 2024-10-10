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
            if(arr[j] < arr[j+1]) //descending order
            {
                int temp = arr[j+1] ;
                arr[j+1] = arr[j] ; 
                arr[j] = temp ; 
            }
        }
    }
}


int main()
{
    int arr[10] = {5,1,3,6,2,9,7,4,8,10} ; 

    cout << "Unsorted Array" << endl ; 
    for(int i=0 ; i<10 ; i++)
    {
        cout << arr[i] << " " ;
    }
    cout << endl ; 

    bubblesort(arr , 10) ;
    cout << "Sorted Array" << endl ; 
    for(int i=0 ; i<10 ; i++)
    {
        cout << arr[i] << " " ;
    }

}