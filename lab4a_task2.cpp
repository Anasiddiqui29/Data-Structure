#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

class Date
{
    public:
    
    int date ; 
    int month ; 
    int year ; 

    Date(int date=0 , int month=0 , int year=0)
    {
        this->date = date ; 
        this->month = month ; 
        this->year = year ;
    }

    void inputData()
    {
        cout << "Enter the date: " ;
        cin >> date ;
        cout << "Enter the month: " ;
        cin >> month ; 
        cout << "Enter the year: " ;
        cin >> year ; 
    }

    void display()
    {
        cout << date << "/" << month << "/" << year << endl ; 
    }
    
} ;

void SelectionSort(Date *data ,int N)
{
    //Sorting based on year
    for(int i=0 ; i<N ; i++)
    {
        int min = i ;
        for(int j=i+1 ; j<N ; j++)
        {
            if(data[j].year < data[min].year)
            {
                min = j ;                 
            }
        }
        //Now Swapping
        int temp =data[min].year ;
        data[min].year = data[i].year ; 
        data[i].year = temp ; 
         

    }
}

int main()
{
    Date date[5] ; 
    //Now taking input from the user
    for(int i=0 ; i<5 ; i++)
    {
        cout << "Enter the details of Date " << i+1 << endl ;         
        date[i].inputData() ; 
    }
    cout << "Unsorted dates" << endl ; 
    for(int i=0 ; i<5 ; i++)
    {
        date[i].display() ; 
    }

    SelectionSort(date , 5) ;

    cout << "Sorted Dates" << endl ; 
    for(int i=0 ; i<5 ; i++)
    {
        date[i].display() ; 
    }

}