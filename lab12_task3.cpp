#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

using namespace std ;

class DirectedGraph 
{
    int vertices;
    int** adjacencyList;
    int* listSizes; 

    public:
    DirectedGraph(int v) : vertices(v) 
    {
        adjacencyList = new int*[vertices];
        listSizes = new int[vertices];

        for (int i = 0; i < vertices; i++) 
        {
            listSizes[i] = 0;
            adjacencyList[i] = new int[vertices];
        }
    }

    ~DirectedGraph() 
    {
        for (int i = 0; i < vertices; i++) 
        {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
        delete[] listSizes;
    }

    void addEdge(int from, int to) 
    {
        adjacencyList[from][listSizes[from]++] = to;
    }

    void printGraph() 
    {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < vertices; ++i) 
        {
            cout << i << ": ";
            for (int j = 0; j < listSizes[i]; j++) 
            {
                cout << adjacencyList[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() 
{
    int vertices = 5;

    
    DirectedGraph graph(vertices);

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(4, 1);
    graph.addEdge(4, 3);
    graph.addEdge(1, 3);
    graph.addEdge(1, 2);
    graph.addEdge(3, 2);

    graph.printGraph();

    return 0;
}


