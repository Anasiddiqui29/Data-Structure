#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

void shellSort(int arr[], int n)
{
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = arr[i];

            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp; 
        }
    }
}

int main()
{
    int employeeWeights[] = {78, 67, 92, 81, 59, 72, 95, 63};
    int size = sizeof(employeeWeights) / sizeof(employeeWeights[0]) ;

    cout << "Original Weight" << endl ; 
    for(int i=0 ; i<size ; i++)
    {
        cout << employeeWeights[i] << " " ;
    }
    cout << endl ; 

    shellSort(employeeWeights , size) ;

    cout << "Sorted Weight" << endl ; 
    for(int i=0 ; i<size ; i++)
    {
        cout << employeeWeights[i] << " " ;
    }
    cout << endl ;
}