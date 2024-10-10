#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

//since we cannot compare string for sorting so we will assign priority numbers
int getPriority(string jobTitle)
{
    if(jobTitle == "CEO")
    {
        return 6 ; 
    }
    if(jobTitle == "CTO")
    {
        return 5 ; 
    }
    if(jobTitle == "CFO")
    {
        return 4 ; 
    }
    if(jobTitle == "VP") 
    {
        return 3 ;
    }
    if(jobTitle == "MGR")
    {
        return 2 ; 
    }
    if(jobTitle == "EMP")
    {
        return 1 ; 
    }
}

void InsertionSort(string arr[] , int N)
{
    for(int i=1 ; i<N ; i++)
    {
        string key = arr[i] ; 
        int j = i-1 ; 

        while(j>=0 && getPriority(arr[j])<getPriority(key))
        {
            arr[j+1] = arr[j] ; //swapping
            j = j-1 ; //updating the j
        }
        arr[j+1] = key ; 
    }

}

int main()
{
    string desk[] = {"EMP" , "CFO" , "MGR" , "EMP" , "VP",  "CTO" , "MGR" , "CEO"} ;

    int size = sizeof(desk) / sizeof(desk[0]) ;

    cout << "Initial Arrangements" << endl ;

    for(int i=0 ; i<size ; i++)
    {
        cout << desk[i] << endl ; 
    } 

    cout << "After sorting" << endl ;
    InsertionSort(desk , size) ;

    
    for(int i=0 ; i<size ; i++)
    {
        cout << desk[i] << endl ; 
    }

}