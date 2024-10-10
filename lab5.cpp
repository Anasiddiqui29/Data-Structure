#include <iostream>

using namespace std ; 

int generatesequence(int n)
{
	if(n==1)
	{
		return 1 ; 
	}
	else
	{
		return n + generatesequence(n-1) ; 
	}
}

int Generatesequence(int n)
{

	if(n<=1)
	{
		return n ; 
	}
	else
	{
		return Generatesequence(n-1)+Generatesequence(n-2) ;
	}
	
}

//indirect approach
int fibonacci(int n)
{
	if(n==1)
	{
		return 1 ; 
	}
	else
	{
		return generateSequence(n-1)+fibonacci(n-1)
	}
}

int main()
{
	
	for(int i=0 ; i<5 ; i++)
	{
		cout << Generatesequence(i) << " , "; 
	}
}

