#include <iostream>
#include <string>

using namespace std ;

const string order = "#$%&*@^~" ; 

int findorderIndex(char ch)
{
    for(int i = 0 ; i<order.length() ; i++)
    {
        if(order[i] == ch)
        {
            return i ; 
        }
    }
}

class HashTableEntry 
{
    public:
    int key;       
    char value;     
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

    bool SearchKey(int k , char &result) 
    {
        int i = 0;  
        int hash = HashFunc1(k);  

        while (table[hash] != nullptr) 
        {
            if (!table[hash]->deleted && table[hash]->key == k) 
            {
                result = table[hash]->value;
                return true ; 
            }
            i++;  
            hash = DoubleHashFunc(k, i);  
        }
        return false ;  
    }

    // Destructor: Table ke saare dynamically allocated memory ko free karta hai
    ~HashMapTable() 
    {
        for (int i = 0; i < TABLE_SIZE; ++i) 
        {
            if (table[i] != nullptr) {
                delete table[i];  // Har entry ko delete karo
            }
        }
        delete[] table;  // Array of pointers ko free karo
    }

} ;

void matchNutsAndBolts(char nuts[] , char bolts[] , int n)
{
    HashMapTable hashnuts ; 
    HashMapTable hashbolts ; 

    for(int i = 0 ; i<n ; i++)
    {
        int key = findorderIndex(nuts[i]);
        if(key != -1)
        {
            hashnuts.Insert(key , nuts[i]) ;
        }
    }

    //bolts
    for(int i=0 ; i<n ; i++)
    {
        int key = findorderIndex(bolts[i]) ;
        if(key != -1)
        {
            hashbolts.Insert(key , bolts[i]);
        }
    }

    cout << "Matched Nuts" << endl ; 
    for(int i=0 ; i<order.length() ; i++)
    {
        char nut , bolt ; 
        if(hashnuts.SearchKey(i , nut) && hashbolts.SearchKey(i , bolt))
        {
            cout << nut << " " ;
        }
    }
    cout << endl ; 

    cout << "Matched Bolts" << endl; 
    for(int i=0 ; i<order.length() ; i++)
    {
        char nut , bolt ; 
        if(hashbolts.SearchKey(i , bolt) && hashnuts.SearchKey(i , nut))
        {
            cout << bolt << " " ; 
        }
    }
    cout << endl ; 
}

int main()
{
    int N = 5 ; 
    char nuts[] = {'@', '%', '$', '#', '^'} ;
    char bolts[] = {'%', '@', '#', '$', '^'} ;

    matchNutsAndBolts(nuts , bolts , N) ; 

}