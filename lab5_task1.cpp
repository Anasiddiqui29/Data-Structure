#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std ;

int generateNum()
{
    srand(time(0)) ;
    int randnum = rand()%100 + 1 ; //generate random number between 1 and 100
    return randnum ; 
}

void guessNum(int tn , int sp)
{
    cout << "Guess the number: " ;
    int gn ;
    cin >> gn ; 

    if(tn == gn)
    {
        cout << "Player " << sp << " guess the number correctly" ; 
    }
    else
    {
        if(gn > tn)
        {
            cout << "Too high" << endl ;  ; 
            if(sp == 1)
            {
                guessNum(tn ,2) ;
            }
            else
            {
                guessNum(tn , 1) ;
            }
        }
        else
        {
            cout << "Too low" << endl ;  ; 
            if(sp == 1)
            {
                guessNum(tn , 2) ;
            }
            else
            {
                guessNum(tn , 1) ;
            }
        }
    }

}



int main()
{
    int startingPlayer = 1 ; 

    int targetnum = generateNum() ; 

    guessNum(targetnum , startingPlayer) ; 

}