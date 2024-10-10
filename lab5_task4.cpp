#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std ;

int recursiveArraySum(int *arr[] , int size[] , int dim)
{
    //base case
    if(dim ==0)
    {
        int sum=0 ; 
        for(int i=0 ; i<size[0] ; i++)
        {
            sum = sum + *arr[i] ; 
        }
        return sum ; 
    }

    //recursively calling
    int totalsum =0  ;
    for(int i=0 ; i<size[dim] ; i++)
    {
        totalsum = totalsum + recursiveArraySum(&arr[i] , size + 1 , dim -1) ;  // after reaching base case , totalsum = 0 +sum 
    }
    return totalsum ; 
}

