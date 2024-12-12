#include <iostream>
#include <string>
#include <cmath>

using namespace std ;

void BruteForceSearch(string text , string pattern)
{
    int n = text.length() ; 
    int m = pattern.length() ;

    for(int i=0 ; i<= n-m ; i++)
    {
        int j=0 ; 
        while(j<m && text[i+j] == pattern[j])
        {
            j++ ; //move ahead to check other characters of the pattern
        }
        if(j==m)
        {
            cout << "Pattern found at the Index: " << i << endl ; 
        }
    } 
}

int main()
{
    string text = "ABABABA" ; 
    string pattern = "ABA" ;

    BruteForceSearch(text , pattern) ;  
}