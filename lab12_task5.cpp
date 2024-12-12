#include <iostream>
#include <string>
#include <cstring> 

#define NO_OF_CHARS 256

using namespace std;

void badCharHeuristic(const string &str, int size, int* badchar)
{
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++)
    {
        badchar[(int)str[i]] = i;
    }
}

void searchMultiplePatterns(const string &txt, const string patterns[], int patternsCount)
{
    int n = txt.size();

    int** badChars = new int*[patternsCount];
    for (int i = 0; i < patternsCount; i++)
    {
        badChars[i] = new int[NO_OF_CHARS]; 
        badCharHeuristic(patterns[i], patterns[i].size(), badChars[i]);
    }

    for (int i = 0; i < patternsCount; i++)
    {
        string pat = patterns[i];
        int m = pat.size();
        int s = 0; 

        while (s <= (n - m))
        {
            int j = m - 1;

            while (j >= 0 && pat[j] == txt[s + j])
            {
                j--;
            }
            if (j < 0)
            {
                cout << "Pattern \"" << pat << "\" occurs at shift = " << s << endl;
                s += (s + m < n) ? m - badChars[i][txt[s + m]] : 1;
            }
            else
            {
                s += max(1, j - badChars[i][txt[s + j]]);
            }
        }
    }

    for (int i = 0; i < patternsCount; i++)
    {
        delete[] badChars[i];
    }
    delete[] badChars;
}

int main()
{
    string text = "ABAAABCDABCABCDBABACBCABABC";
    string patterns[] = {"ABC", "ABCABC", "BABC"};
    int patternsCount = sizeof(patterns) / sizeof(patterns[0]);

    searchMultiplePatterns(text, patterns, patternsCount);

    return 0;
}