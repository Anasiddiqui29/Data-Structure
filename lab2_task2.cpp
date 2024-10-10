#include <iostream>
#include <cstring>
#include <cstdlib>

#include "matrix_multiply.h"

using namespace std ;

int main()
{
    //taking matrix input from the user
    int size ; 
    cout << "Enter the size of the arrays: " << endl ; 
    cin >> size ; 

    //Dynamically allocating memory
    int **matrix1 = new int*[size] ;
    int **matrix2 = new int*[size] ;
    int **result = new int*[size] ;  

    for(int i=0 ; i<size ; i++)
    {
        matrix1[i] = new int[size] ; 
        matrix2[i] = new int[size] ; 
        result[i] = new int[size] ;
    }

    cout << "Enter the elements of first matrix" << endl ;
    for(int i=0 ; i<size ; i++)
    {
        for(int j=0 ; j<size ; j++)
        {
            cout << "[" << i << "]" << "[" << j << "] : " ; 
            cin >> matrix1[i][j] ; 
        }
    }

    cout << "--------------------------------" << endl ; 

    cout << "Enter the elements of second matrix" << endl ; 
    for(int i=0 ; i<size ; i++)
    {
        for(int j=0 ; j<size ; j++)
        {
            cout << "[" << i << "]" << "[" << j << "] : " ; 
            cin >> matrix2[i][j] ; 
        }
    }

    multiplymatrix(matrix1 , matrix2 , result , size) ;

    cout << "Resultant Matrix" << endl ; 
    for(int i=0 ; i<size ; i++)
    {
        for(int j=0 ; j<size ; j++)
        {
            cout << result[i][j] << " " ;
        }
        cout << endl ; 
    }

    //freeing dynamically allocated memory
    for(int i=0 ; i<size ; i++)
    {
        delete[] matrix1[i] ;
        delete[] matrix2[i] ; 
        delete[] result[i] ;
    }
    delete[] matrix1 ;
    delete[] matrix2 ;
    delete[] result ; 
}