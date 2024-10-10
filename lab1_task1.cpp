#include <iostream>
#include <string>
#include <cstdlib>

using namespace std ;

class BankAccount
{
    int balance = 100 ; 

    public:
    //Default constructor
    BankAccount()
    {
        cout << "Your Account balance is: $" << balance << endl ; 
    }

    //Parameterized constructor
    BankAccount(int balance)
    {
        this->balance = balance ; 
        cout << "Your Account balance is: $" << balance << endl ;
    }

    //Copy constructor
    BankAccount(const BankAccount &account)
    {
        this->balance = account.balance - 200 ; 
        cout << "Your Account balance is: $" << balance << endl ; 
    }

} ;

int main()
{
    BankAccount account1 ; 

    BankAccount account2(1000) ;

    BankAccount account3(account2) ;
}
