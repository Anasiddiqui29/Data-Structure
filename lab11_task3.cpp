#include <iostream>
#include <string>

using namespace std ;

class HashTableEntry 
{
    public:
    int key;       
    int value;     
    bool deleted;  

    HashTableEntry(int k, int v)
    {
        key = k ; 
        value = v ; 
        deleted = false ; 
    }
};

class HashMapTable 
{
    static const int TABLE_SIZE = 11;   
    HashTableEntry** table;            

    int HashFunc1(int k) 
    {
        return (k % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE; ////to ensure that it always returns positive value 
    }

    //secondary hash function which is used for double hashing
    int HashFunc2(int k) 
    {
        return (7 - (k % 7) + 7) % 7; //to ensure that it always returns positive value 
    }

    public:
    HashMapTable() 
    {
        table = new HashTableEntry*[TABLE_SIZE]();
    }

    // Double hashing function
    int DoubleHashFunc(int k, int i) 
    {
        return (HashFunc1(k) + i * HashFunc2(k)) % TABLE_SIZE;
    }

    void Insert(int k, int v) 
    {
        int i = 0;  
        int hash = HashFunc1(k);

        while (table[hash] != nullptr && !table[hash]->deleted) 
        {
            i++;  
            hash = DoubleHashFunc(k, i); 
        }

        table[hash] = new HashTableEntry(k, v);
    }

    int SearchKey(int k) 
    {
        int i = 0;  
        int hash = HashFunc1(k);  

        while (table[hash] != nullptr) 
        {
            if (!table[hash]->deleted && table[hash]->key == k) 
            {
                return table[hash]->value;
            }
            i++;  
            hash = DoubleHashFunc(k, i);  
        }
        return -1;  
    }

    int triplet(int arr[] , int N)
    {   
        for(int i=0 ; i<N ; i++)
        {
            Insert(arr[i] , 1) ;
        }

        int target = 0 ;

        for(int i=0 ; i<N ; i++)
        {
            for(int j = i+1 ; j<N ; j++)
            {
                int target = -(arr[i] + arr[j]) ; //reverse the sign of the value which will be our third value

                if(SearchKey(target) != -1 && arr[i] != target && arr[j] != target)
                {
                    return 1 ; 
                }
            }
        }
        return 0 ; 

    }

    ~HashMapTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) 
        {
            if (table[i] != nullptr) 
            {
                delete table[i];  
            }
        }
        delete[] table; 
    }
};

int main()
{
    HashMapTable hashtable ;
    int n = 5; 
    int arr[] = {0, -1, 2, -3, 1} ; 

    int result = hashtable.triplet(arr , n) ;

    cout << "Result : " << result << endl ; 

}
