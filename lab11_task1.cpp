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

    void Remove(int k)
    {
        int hash = hashfunc(k) ; 
        //jb tk entry nhi milti , use linear probing
        while(table[hash] != nullptr)
        {
            if(table[hash]->key == k)
            {
                delete table[hash] ; 
                table[hash] = nullptr ;
                return ; 
            }
            hash = (hash + 1) % TABLE_SIZE ;
        }
    }

    void PrintTable() 
    {
        for (int i = 0; i < TABLE_SIZE; ++i) 
        {
            if (table[i] != NULL) 
            {
                cout << "Index " << i << ": Key=" << table[i]->key << ", Value=" << table[i]->value << endl;
            } 
            else 
            {
                cout << "Index " << i << ": Empty" << endl;
            }
        }
    }

    // Destructor
    ~HashMapTable() 
    {
        for (int i = 0; i < TABLE_SIZE; ++i) 
        {
            if (table[i] != NULL) 
            {
                delete table[i]; 
            }
        }
        delete[] table; 
    }

} ;

int main()
{
    HashMapTable hashtable ; 

    hashtable.Insert(20 , 5);
    hashtable.Insert(34 , 10);
    hashtable.Insert(45 , 15);
    hashtable.Insert(70 , 23);
    hashtable.Insert(56 , 21);

    cout << "Hash table after insertion" << endl ; 
    hashtable.PrintTable() ; 

    int value = hashtable.Searchkey(34); 
    if (value != -1) {
        cout << "Value for key 34: " << value << endl; 
    } 
    else 
    {
        cout << "Key 34 not found." << endl; 
    }

    hashtable.Remove(45) ; 

    cout << "Hash table after removal" << endl ; 

    hashtable.PrintTable() ; 

}

