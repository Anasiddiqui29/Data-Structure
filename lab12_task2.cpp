#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

using namespace std ;

class Solution 
{
    public:
    // Directions for possible directions
    int dx[8] = {-1, 0, 1, 0, 1, -1, -1, 1};
    int dy[8] = {0, -1, 0, 1, 1, 1, -1, -1};

    bool isValid(int x, int y, int n, int m) 
    {
        return (x >= 0 && x < n && y >= 0 && y < m);
    }

    int numIslands(int** grid, int n, int m) 
    {
        bool** vis = new bool*[n];
        for (int i = 0; i < n; i++) 
        {
            vis[i] = new bool[m];
        }

        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < m; j++) 
            {
                vis[i][j] = false;
            }
        }

        int maxSize = n * m;
        int* queueX = new int[maxSize];
        int* queueY = new int[maxSize];

        int ans = 0;

        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < m; j++) 
            {
                if (!vis[i][j] && grid[i][j] == 1) 
                {
                    ans++;
                    vis[i][j] = true;

                    int front = 0, rear = 0;
                    queueX[rear] = i;
                    queueY[rear] = j;
                    rear++;

                    while (front < rear) 
                    {
                        int x = queueX[front];
                        int y = queueY[front];
                        front++;

                        for (int k = 0; k < 8; k++) 
                        {
                            int newX = x + dx[k];
                            int newY = y + dy[k];

                            if (isValid(newX, newY, n, m) && !vis[newX][newY] && grid[newX][newY] == 1) 
                            {
                                queueX[rear] = newX;
                                queueY[rear] = newY;
                                rear++;
                                vis[newX][newY] = true;
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) 
        {
            delete[] vis[i];
        }
        delete[] vis;
        delete[] queueX;
        delete[] queueY;

        return ans;
    }
};

int main() 
{
    Solution solution;

    int n = 4, m = 5;
    int** grid = new int*[n];
    grid[0] = new int[m]{1, 1, 0, 0, 0};
    grid[1] = new int[m]{1, 1, 0, 0, 0};
    grid[2] = new int[m]{0, 0, 1, 0, 0};
    grid[3] = new int[m]{0, 0, 0, 1, 1};

    cout << "Number of islands: " << solution.numIslands(grid, n, m) << std::endl;

    // Free the dynamically allocated grid.
    for (int i = 0; i < n; i++) 
    {
        delete[] grid[i];
    }
    delete[] grid;

}