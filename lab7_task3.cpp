#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

void mergeAs(int arr[] , int l , int m , int r)
{
    //Create two temporary arrays
    int n1 = m-l+1 ; 
    int n2 = r-m ; 

    //Dynamically allocating size for arrays
    int *L = new int[n1] ;
    int *R = new int[n2] ; 

    //copy data to temporary arrays
    for(int i=0 ; i<n1 ; i++)
    {
        L[i] = arr[l+i] ; 
    }
    for(int j=0 ; j<n2 ; j++)
    {
        R[j] = arr[m+j+1] ; //since mid+1 sai copy ho raha hai
    }

    //Merge the temporary array back to original array
    int i = 0 ; //initial index for first subarray
    int j = 0 ; //initial index for second subarray
    int k = l ; //initial index for merged array

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i] ; 
            i++ ; 
        }
        else
        {
            if(L[i] > R[j])
            {
                arr[k] = R[j] ;
                j++ ;
            }
        }
        k++ ; 
    }

    //Copy the elements of left subarray if any
    while(i < n1)
    {
        arr[k] = L[i] ; 
        i++ ; 
        k++ ; 
    }
    while(j < n2)
    {
        arr[k] = R[j] ; 
        j++; 
        k++ ; 
    }

    delete[] L ; 
    delete[] R ; 

}

void mergesortAs(int arr[] , int l , int r)
{
    if(l<r)
    {
        //to find the middle index
        int m = l + (r-l)/2 ; 

        mergesortAs(arr , l , m) ; //sort the first half
        mergesortAs(arr , m+1 , r) ; //sort the second half
        //merge sorted halves
        mergeAs(arr , l ,m , r) ;
    }
}

void mergeDs(int arr[] , int l , int m , int r)
{
    //Create two temporary arrays
    int n1 = m-l+1 ; 
    int n2 = r-m ; 

    //Dynamically allocating size for arrays
    int *L = new int[n1] ;
    int *R = new int[n2] ; 

    //copy data to temporary arrays
    for(int i=0 ; i<n1 ; i++)
    {
        L[i] = arr[l+i] ; 
    }
    for(int j=0 ; j<n2 ; j++)
    {
        R[j] = arr[m+j+1] ; //since mid+1 sai copy ho raha hai
    }

    //Merge the temporary array back to original array
    int i = 0 ; //initial index for first subarray
    int j = 0 ; //initial index for second subarray
    int k = l ; //initial index for merged array

    while(i < n1 && j < n2)
    {
        if(L[i] >= R[j])
        {
            arr[k] = L[i] ; 
            i++ ; 
        }
        else
        {
            if(L[i] < R[j])
            {
                arr[k] = R[j] ;
                j++ ;
            }
        }
        k++ ; 
    }

    //Copy the elements of left subarray if any
    while(i < n1)
    {
        arr[k] = L[i] ; 
        i++ ; 
        k++ ; 
    }
    while(j < n2)
    {
        arr[k] = R[j] ; 
        j++; 
        k++ ; 
    }

    delete[] L ; 
    delete[] R ; 

}

void mergesortDs(int arr[] , int l , int r)
{
    if(l<r)
    {
        //to find the middle index
        int m = l + (r-l)/2 ; 

        mergesortDs(arr , l , m) ; //sort the first half
        mergesortDs(arr , m+1 , r) ; //sort the second half
        //merge sorted halves
        mergeDs(arr , l ,m , r) ;
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
    mergesortAs(arr , 0 , 9);
    printArray(arr , 10) ; 
    cout <<"--------------------------------------" << endl ; 
    cout << "Sorted Array in Descending order" << endl ; 
    mergesortDs(arr , 0 , 9) ;
    printArray(arr , 10) ; 
}