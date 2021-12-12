#ifndef GRAPHSTRUCTURE_H
#define GRAPHSTRUCTURE_H

#include <iostream>
#include <vector>
#include <string.h>
#include <unordered_set>
#include <stack>
#include <climits>
using namespace std;

class Vertex{
public:
    string Value;
    bool Visited;
    Vertex(): Value("None"), Visited(false){} // <- default constructor, used in creating 2d array, otherwise we always have to assign value when construct this class.
    Vertex(string name)
    {
        Value = name;
        Visited = false;
    }
};

class Graph{
private:
    int MaxNumberOfVertex;
public:
    int NumberOfVertex = 0;
    vector<Vertex> Vertices;
    int **adjMatrix;
    Graph(int maxValue);
    void addVertex(string);
    void addEdge(int,int,int);
    void showVertex(int);
    void printMatrix();
    int valueToIndex(string);
};

Graph::Graph(int maxValue)
{
    MaxNumberOfVertex = maxValue;
    // create a list that will store our vertices
    
    // here, exhibit two ways to store dynamic data
    // one is using vector
    // another one is using pointer
    Vertices = vector<Vertex>(); // <- we don't need to give any value, it's dynamic data structure
    adjMatrix = new int* [MaxNumberOfVertex]; // <- first layer, tell you how many row
    
    // initialize value in adjMatrix to zero
    for (int i = 0; i < MaxNumberOfVertex; i++)
    {
        adjMatrix[i] = new int[MaxNumberOfVertex]; // <- second layer, tell you how many columns in one row
        
        // set all value in this row to zero
        fill_n(adjMatrix[i], MaxNumberOfVertex, 0);

    }
}
void Graph::addVertex(string name)
{
    // avoid repeated value
    for (int i = 0; i < Vertices.size(); i++)
    {
        if (Vertices[i].Value == name)
            return;
    }
    Vertices.push_back(Vertex(name));
    NumberOfVertex++;
}
void Graph::addEdge(int start, int end, int weight)
{
    adjMatrix[start][end] = weight;
    adjMatrix[end][start] = weight; // undirected map
}
void Graph::showVertex(int index)
{
    cout << Vertices[index].Value << endl;
}
void Graph::printMatrix()
{
    for (int i = 0; i < NumberOfVertex; i++)
    {
        for (int j = 0; j < NumberOfVertex; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
        
}
int Graph::valueToIndex(string name)
{
    for (int i = 0; i < Vertices.size(); i++)
    {
        if (Vertices[i].Value == name)
            return i;
    }
    return -1;
}

class Dijkstra
{
private:
    unordered_set<int> UnvisitedListVertices;
    int getNextVertex();
    int starter;
public:
    Dijkstra(int **adjMatrix, int NumberOfVertex, int starter);
    int *ShortestDistances;
    int *PreviousVertex;
    void showPath(int end);
    stack<int> getPath(int end);
};

Dijkstra::Dijkstra(int ** adjMatrix, int NumberOfVertex, int starter)
{
    this->starter = starter;
    // first set the array for distance and set all to infinity
    ShortestDistances = new int [NumberOfVertex];
    fill_n(ShortestDistances, NumberOfVertex, INT_MAX);
    // however, set the starter to 0
    ShortestDistances[starter] = 0;
    // set the array for previous vertex
    PreviousVertex = new int [NumberOfVertex];
    // add all available vertex in UnvisitedListVertices
    for (int i = 0; i < NumberOfVertex; i++)
    {
        UnvisitedListVertices.insert(i);
    }
    
    // generate shortest distance and path information
    while(UnvisitedListVertices.size() > 0)
    {
        // pick one that is currently shortest distance in the unvisited list
        int currentVertex = getNextVertex();
        
        for (int i = 0; i < NumberOfVertex; i++)
        {
            // if find connected edge, then compare its distance with ShortestDistances info
            if (adjMatrix[currentVertex][i] > 0)
            {
                if (ShortestDistances[i] > (ShortestDistances[currentVertex] + adjMatrix[currentVertex][i]))
                {
                    // update ShortestDistances info, since we found a shorter one
                    ShortestDistances[i] = ShortestDistances[currentVertex] + adjMatrix[currentVertex][i];
                    // update previous vertex info
                    PreviousVertex[i] = currentVertex;
                }
            }
        }
    }
    
}
int Dijkstra::getNextVertex()
{
    int distance_buffer = __INT_MAX__;
    int vertex_index = -1;
    // loop the unvisited List set to find the return value
    for (unordered_set<int>::iterator it = UnvisitedListVertices.begin(); it != UnvisitedListVertices.end(); it++)
    {
        int index = *it;
        if (ShortestDistances[index] < distance_buffer)
        {
            distance_buffer = ShortestDistances[index];
            vertex_index = index;
        }
    }
    UnvisitedListVertices.erase(vertex_index);
    return vertex_index;
}
void Dijkstra::showPath(int end)
{
    stack<int> path;
    int d = ShortestDistances[end];
    while(end != starter)
    {
        path.push(end);
        end = PreviousVertex[end];
    }
    // print info
    cout << end;
    while(path.size() != 0)
    {
        cout << " -> " << path.top();
        path.pop();
    }
    cout << endl;
    cout << "Total length is " << d << endl;
}

stack<int> Dijkstra::getPath(int end)
{
    stack<int> path;
    while(end != starter)
    {
        path.push(end);
        end = PreviousVertex[end];
    }
    path.push(end);
    return path;
}

#endif
