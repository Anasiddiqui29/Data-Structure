#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

void combSort(double arr[], int n , float shrink)
{
    // Initialize gap
    int gap = n;

    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap>1 || swapped == true)
    {
        // Find next gap
        gap = (int)(gap/shrink) ;
        if(gap<1)
        {
            gap=1 ;
        }
    

        swapped = false ; 

        //Perform a gap bubble sort
        for(int i=0 ; i+gap < n ; i++)
        {
            if(arr[i]>arr[i+gap])
            {
                //swapping
                int temp = arr[i] ;
                arr[i] = arr[i+gap] ; 
                arr[i+gap] = temp ; 
                swapped = true ; 
            }
        }
    }

}

int main() 
{
    double productPrices[] = {59.99, 29.95, 42.50, 19.99, 89.00, 55.75, 35.10};
    int n = sizeof(productPrices) / sizeof(productPrices[0]); // Get the number of elements

    cout << "Original prices: ";
    for (int i = 0; i < n; i++) {
        cout << productPrices[i] << " ";
    }
    cout << endl;

    // Perform Comb Sort with a custom shrink factor 
    double customShrinkFactor = 1.5;
    combSort(productPrices, n, customShrinkFactor);

    cout << "Sorted prices: ";
    for (int i = 0; i < n; i++) {
        cout << productPrices[i] << " ";
    }
    cout << endl;
}
