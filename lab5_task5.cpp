#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

#define N 5

using namespace std ;

bool solveMazeUntil(int maze[N][N] , int x , int y , int sol[N][N]) ; 

void printSol(int sol[N][N])
{
    for(int i=0 ; i<N ; i++)
    {
        for(int j=0 ; j<N ; j++)
        {
            cout << " " << sol[i][j] ;
        }
        cout << endl ; 
    }
}

//to check if there is any obstacle
bool isSafe(int maze[N][N] , int x , int y)
{
    if(x>=0 && x<N && y>=0 && y<N && maze[x][y] == 1)
    {
        return true ; 
    }
    else
    {
        return false ; 
    }
}

bool solveMaze(int maze[N][N])
{
    int sol[N][N] = {  {0 , 0 , 0 , 0 , 0} ,
                        {0 , 0 , 0 , 0 , 0} ,
                        {0 , 0 , 0 , 0 , 0} ,
                        {0 , 0 , 0 , 0 , 0} ,
                        {0 , 0 , 0 , 0 , 0}
                    } ; 
    
    if(solveMazeUntil(maze , 0 , 0 , sol) == false)
    {
        cout << "Solution doesnot exist" << endl ; 
        return false ; 
    }

    printSol(sol) ;
}

bool solveMazeUntil(int maze[N][N] , int x , int y , int sol[N][N])
{
    //base case
    if(x == N-1 && y == N-1 && maze[x][y]==1)
    {
        return true ; 
    }

    if(isSafe(maze , x , y) == true)
    {
        if(sol[x][y] == 1)
        {
            return false ; //true 
        }
        sol[x][y] = 1 ;
        
        if(solveMazeUntil(maze , x+1 , y , sol) == true) //move right
        {
            return true ; 
        }

        if(solveMazeUntil(maze , x-1 , y , sol) == true) //move left
        {
            return true ; 
        } 

        if(solveMazeUntil(maze , x , y+1 , sol) == true) //move down
        {
            return true ; 
        }

        if(solveMazeUntil(maze , x , y-1 , sol) == true) //move up
        {
            return true ; 
        }

        sol[x][y] = 0 ; //backtracking
        return false ; 
    }
    return false ; 
}


int main()
{
    int maze[N][N] = {  {1 , 0 , 1 , 0 , 1} ,
                        {1 , 1 , 1 , 1 , 1} ,
                        {0 , 1 , 0 , 1 , 1} ,
                        {1 , 0 , 0 , 1 , 1} ,
                        {1 , 1 , 1 , 0 , 1}
                    } ; 

    solveMaze(maze) ; 
}