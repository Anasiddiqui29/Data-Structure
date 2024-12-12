#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

using namespace std ;

int calculateHash(const string &str, int base, int length) 
{
    int hash = 0;
    for (int i = 0; i < length; i++) {
        hash = (hash + str[i] - '0') * pow(base, length - i - 1);
    }
    return hash;
}

bool isPalindrome(const string &str) 
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++) 
    {
        if (str[i] != str[n - i - 1]) 
        {
            return false;
        }
    }
    return true;
}

void rabinkarp(const string &str, int base) 
{
    int n = str.length();

    for (int length = 1; length <= n; length++) 
    {
        for (int i = 0; i <= n - length; i++) 
        {
            string substring = str.substr(i, length);

            if (isPalindrome(substring)) 
            {
                cout << "Palindrome found: " << substring << " at index " << i << endl;
            }
        }
    }
}

int main() 
{
    string text = "ABCBAB";
    int base = 256; 

    rabinkarp(text, base);

    return 0;
}
