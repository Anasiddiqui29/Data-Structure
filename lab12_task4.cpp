#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

using namespace std ;

char toLowerCase(char c) 
{
    if (c >= 'A' && c <= 'Z') 
    {
        return c + ('a' - 'A'); // Convert to lowercase
    }
    return c;
}


void constructLps(string &pat, int *lps) 
{
    int len = 0; 
    lps[0] = 0;  

    int i = 1;
    while (i < pat.length()) 
    {
        if (toLowerCase(pat[i]) == toLowerCase(pat[len])) 
        {
            len++;
            lps[i] = len;
            i++;
        } 
        else 
        {
            if (len != 0) 
            {
                len = lps[len - 1];
            } 
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int* search(string &pat, string &txt, int &count) 
{
    int n = txt.length();
    int m = pat.length();

    int* lps = new int[m];
    constructLps(pat, lps);

    int* res = new int[n]; 
    count = 0; 

    int i = 0; 
    int j = 0; 

    while (i < n) 
    {
        if (toLowerCase(txt[i]) == toLowerCase(pat[j])) 
        {
            i++;
            j++;

            if (j == m) 
            {
                res[count++] = i - j; 
                j = lps[j - 1];
            }
        } 
        else 
        {
            if (j != 0) 
            {
                j = lps[j - 1];
            } 
            else 
            {
                i++;
            }
        }
    }

    delete[] lps; 
    return res;   
}

int main() 
{
    string txt = "Data Structures";
    string pat = "data";
    int count = 0;
    
    int* result = search(pat, txt, count);

    // Print the results
    cout << "Number of matches: " << count << endl;
    for (int i = 0; i < count; i++) 
    {
        cout << "Pattern found at index: " << result[i] << endl;
    }

    delete[] result;
    return 0;
}