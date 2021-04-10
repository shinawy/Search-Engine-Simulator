#pragma once
#include <iostream>
#include <vector>
using namespace std;

/* 
 
 some of those functions are not required in the second problem but I added some of them either to test something or 
 to solve problem 1 that uses the same class.
 
 */

struct  edge{
	int source;
	int destination;

};

class Graph
{
private:
	int** adjmat;
	int numofvert;
    void DFSRec(int vertex, vector<bool>& visited);

public:
    Graph(int size);
    ~Graph();
    void addEdge(int source, int destination);
    void addEdge(edge myedge);
    void addWeightedEdge(int source, int destination, int weight); // those are for the sake of testing
    void addWeightedEdge(edge myedge, int weight);  // those are for the sake of testing
    void deleteEdge(int source, int destination);
    void deleteEdge(edge myedge);
    int sumOfLags();
    int getweight(int source,int destination);
    int getweight(edge myedge);

    int getNumberOfIncomingEdges(int vertex);
    int getNumberOfOutgoingEdges(int vertex);
    vector<int> getIncomingNodes(int vertex);
    int* getIncomingNodesarr(int vertex,int& size);
    bool checkAndDelete(int source, int destination, int weight);
    bool isAllconnected();
    bool isConnected(int vertex);
    void DFS();
    void BFS();
    void print();
    void printWithWeights();
};

