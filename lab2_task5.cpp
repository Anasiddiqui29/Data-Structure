#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

int main()
{
    //assuming there are 10 rows in the hall
    string **rows = new string*[10] ; 
    int size[10] ; 

    for(int i=0 ; i<10 ; i++)
    {
        cout << "Enter size of row "<< i+1 << " : " ;
        cin >> size[i] ;
        rows[i] = new string[size[i]] ; 
    }
    
    //taking names of attendees as input
    for(int i=0 ; i<10 ; i++)
    {
        for(int j=0 ; j<size[i] ; j++)
        {
            cout << "Enter name of row " << i+1 << " attendee " << j+1 << " : " ;
            cin >> *(*(rows+i)+j) ;
        }
    }

    //printing
    for(int i=0 ; i<10 ; i++)
    {
        for(int j=0 ; j<size[i] ; j++)
        {
            cout << "Row " << i+1 << endl ;
            cout << "Name " << j+1 << " : " <<rows[i][j] << endl ; 
        }
    }

    //delete
    for(int i=0 ; i<10 ; i++)
    {
        delete[] rows[i] ;
    }
    delete[] rows ; 
}

//sum of jagged arrays
void Sum(int *arr[] , int size[] , int rows)
{
    
    for(int i=0 ; i<rows ; i++)
    {
        int sum=0 ; 
        for(int j=0; j<size[i] ; j++)
        {
            sum += arr[i][j] ; 
        }

        cout << "ROw " << i+1 << " sum: " << sum ; 
    }
     

}