#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

int main()
{
    //Jagged array must be used for this task
    
    //array to store departments and their respective core courses' gpa
    float **dep = new float*[4] ; //as there are 3 departments

    dep[0] = new float[3] {3.67 , 2.33 , 4.0} ; //SE
    dep[1] = new float[4] {2.67 , 3.0 , 3.33 , 4.0} ; //AI
    dep[2] = new float[2] {2.0 , 3.33} ; //CS
    dep[3] = new float[1] {4.0} ; //DS

    //displaying gpa of core courses of each department
    cout << "SE Department" << endl ; 
    for(int i=0 ; i<3 ; i++)
    {
        cout << "Core course " << i+1 << ": " << dep[0][i] << endl ; 
    }
    cout << "-------------------------" << endl ; 
    
    cout << "AI Department" << endl ; 
    for(int i=0 ; i<4 ; i++)
    {
        cout << "Core course " << i+1 << ": " << dep[1][i] << endl ; 
    }
    cout << "------------------------" << endl ; 

    cout << "CS Department" << endl ; 
    for(int i=0 ; i<2 ; i++)
    {
        cout << "Core course " << i+1 << ": " << dep[2][i] << endl ; 
    }
    cout << "------------------------" << endl ;

    cout << "DS Department" << endl ; 
    for(int i=0 ; i<1 ; i++)
    {
        cout << "Core course " << i+1 << ": " << dep[3][i] << endl ; 
    }
    cout << "------------------------" << endl ;

    for(int i=0 ; i<4 ; i++)
    {
        delete[] dep[i] ; 
    }
    delete[] dep ; //delete the array of pointers
}