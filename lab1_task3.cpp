#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std ;

class Document
{
    char *text ; //dynamically allocating memory
    int num ; 

    public:
    Document(int num , const char *Text)
    {
        this->num = strlen(Text)+1 ; //calculating the length of the text and +1 for null terminator
        text = new char[this->num] ;
        strncpy(text , Text , this->num) ; //copy string with null terminator
    }

    //Destructor
    ~Document()
    {
        delete[] text ; 
    }

    //Copy constructor
    Document(const Document &doc)
    {
        num = doc.num ; 
        text = new char[num] ; //dynamically allocating memory
       strncpy(text , doc.text , num) ;
       
    }

    //Copy Assignment operator
    Document& operator=(const Document& doc1)
    {
        if(this == &doc1) //Self assignment handle i.e doc1=doc1
        {
            return *this ;
        }

        delete[] text ; //freeing the existing memory

        num = doc1.num ;
        text = new char[num] ;
       strncpy(text , doc1.text , num) ;

        return *this ; 
    }

    void modify(const char *Text)
    {
        delete[] text ; //to free previous memory

        num = strlen(Text) +1 ; 
        text = new char[num] ;
        strncpy(text , Text , num); //copying the modified text
    }

    void display() const
    {
        for(int i=0 ; i<num ; i++)
        {
            cout << text[i] ; 
        }
    }

} ;

int main()
{
    Document Doc1(100 , "This is Anas Siddiqui. Hello world. DS kinda fun\n") ;
    Doc1.display() ;

    //Copy constructor
    Document Doc2 = Doc1 ; 
    Doc2.display() ;

    //Copy Assignment operator
    Document Doc3(100 , "Hello guys. How you doin. Stop the madness\n") ;
    Doc3 = Doc1 ; 
    Doc3.display() ; 

    cout << "---------After Modification----------" << endl ; 

    Doc1.modify("This is modified text\n") ;
    Doc1.display() ;

    Doc2.display() ;
    Doc3.display() ; 

}