#include <iostream>
#include <string>

using namespace std ;

//linear probing
class HashTableEntry
{
    public:
    int key ; 
    int value ; 

    HashTableEntry(int key , int value)
    {
        this->key = key ; 
        this->value = value ; 
    }
} ;

class HashMapTable
{
    static const int TABLE_SIZE = 10; //fixed table size
    HashTableEntry **table;

    public:
    HashMapTable()
    {
        table = new HashTableEntry*[TABLE_SIZE]() ; //initially nullptr
    }

    int hashfunc(int k)
    {
        return k % TABLE_SIZE ;
    }

    void Insert(int k , int v)
    {
        int hash = hashfunc(k) ; //to calculate the index

        //jb tk khaali jagah nhi mil jati aur collison resolve nhi hota tb tk linear probing
        while(table[hash] != nullptr && table[hash]->key != k)
        {
            hash = (hash + 1) % TABLE_SIZE; //linear probing
        }

        //if there is entry for the existing key already , so delete it
        if(table[hash] != nullptr)
        {
            delete table[hash] ; 
        }

        //create new entry and enter data
        table[hash] = new HashTableEntry(k , v) ;
    }

    int Searchkey(int k)
    {
        int hash = hashfunc(k) ; 

        while(table[hash] != nullptr && table[hash]->key != k)
        {
            hash = (hash + 1) % TABLE_SIZE ; 
        }

        if(table[hash] == nullptr)
        {
            return -1 ; 
        }
        else
        {
            return table[hash]->value ; 
        }
    }

    int Countpairs(int arr[] , int N , int k)
    {
        int count = 0 ;
        
        for(int i=0 ; i<N ; i++)
        {
            Insert(arr[i] , 1) ;
        }

        for(int i=0 ; i<N ; i++)
        {
            int target = k - arr[i] ; 
        
            int targetCount = Searchkey(target) ;
            if(targetCount != -1)
            {
                count++ ; 
            }
        }
        return count/2 ; 
    }

    // Destructor jo dynamically allocated memory ko free karta hai.
    ~HashMapTable() 
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            if (table[i] != NULL) 
            {
                delete table[i]; // Har non-NULL entry ko free karte hain.
            }
        }
        delete[] table; // Table array ko free karte hain.
    }
} ;

int main() 
{   
    HashMapTable hash ; 
    hash.Insert(1 , 10) ;
    hash.Insert(5 , 20) ;
    hash.Insert(7 , 30) ;
    hash.Insert(1 , 40) ;

    int arr[] = {1, 5, 7, 1};
    int N = 4;
    int K = 6;
    cout << "Number of pairs: " << hash.Countpairs(arr, N, K) << endl;
}