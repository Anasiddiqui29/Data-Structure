#include <iostream>
#include <string>
#include <cstdlib>

using namespace std ;

class Exam
{
    string *stdname ; 
    string date ; 
    float *score ;
    int num ;  

    public:
    //parameterized constructor
    Exam() {}
    Exam(int size , const string *names , const float *scores , string date) : num(size)
    {
        stdname = new string[num] ; //Dynamically allocating memory
        for(int i=0 ; i<num ; i++)
        {
            stdname[i] = names[i] ; 
        }

        this->date = date ; 

        score = new float[num] ;
        for(int i=0 ; i<num ; i++)
        {
            score[i] = scores[i] ;
        }   
    }

    ~Exam()
    {
        delete[] stdname ;
        delete[] score ; 
    }

    void display()
    {
        for(int i=0 ; i<num ; i++)
        {
            cout << "Name: " << stdname[i] << endl ; 
            cout << "Date: " << date << endl ; 
            cout << "Score: " << score[i] << endl ; 
        }

    }

} ;

int main()
{
    string Names[] = {"John Doe", "Jane Smith", "Alice Brown"}; 
    float Score[] = {35 , 87 , 90} ;

    Exam exam1(3 , Names , Score , "24-Aug-2023") ;
    
    cout << "Details of Exam 1 are as follows: " << endl ; 
    
    exam1.display() ; 

    //Shallow copy of exam1 to exam2
    Exam exam2 = exam1 ; 

    cout << "Details of Exam 2 are as follows: " << endl ; 

    exam2.display() ;

    /*Potential problem
    When you run the code, the shallow copy occurs when exam1 is copied to exam2. Because no custom copy constructor or 
    copy assignment operator is defined, the default ones are used. 
    These default versions perform a shallow copy, which means that the pointers in exam1 and exam2 will point to the same memory locations.
    So when the second object(exam2) tries to free the same memory , it can lead to double deletion, causing unexpected behaviour
    */

}