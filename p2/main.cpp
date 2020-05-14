/*
Miguel Baptista - 86481
Mariana Chinopa - 92518
*/

#include <stdio.h>
#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

class Node {
    int _nodeId;
    int _currentCapacity;
    int _maxCapacity;
    int _parent;
    vector<int> _adjacencies; //node ids (2-5 node ids (exceptions mega source and mega target))

    public:
        Node(int nodeId, int currentCapacity, int maxCapacity, int parent){
            _nodeId = nodeId;
            _currentCapacity = currentCapacity;
            _maxCapacity = maxCapacity;
            _parent = parent;
        }

        int getNodeId() { return _nodeId; }

        void setNodeId(int nodeId) { _nodeId = nodeId; } 

        int getCurrentCapacity() { return _currentCapacity; }

        void setCurrentCapacity(int currentCapacity) { _currentCapacity = currentCapacity; } 

        int getMaxCapacity() { return _maxCapacity; }

        void setMaxCapacity(int maxCapacity) { _maxCapacity = maxCapacity; } 

        int getParent() { return _parent; }

        void setParent(int parent) { _parent = parent; } 

        vector<int> getAdjacencies() { return _adjacencies; }

        void setAdjacencies(vector<int> adjacencies) { _adjacencies = adjacencies; }

        void addAdjacency(int adj) { _adjacencies.push_back(adj); }

        bool isFull() { return (_currentCapacity == _maxCapacity); }
};

void makeGraph();
void makeNormalNodes(int numNodes);
void makeTargetNode();
void makeSourceNode();
void makeAdjNode(Node* node, int avenue, int street);
void parseInput();
int edmondsKarp(int startNodeId, int endNodeId);
int bfs(int startNodeId, int endNodeId);


map<int, Node*> graph;
int m, n, s, c;
vector<int> adjNode, adjSource, adjTarget;

int main() {

    scanf("%d %d", &m, &n);
    scanf("%d %d", &s, &c);

    if (m < 1 || n < 1 || s < 1 || c < 1) {
        printf("error: wrong input\n");
        return -1;
    }

    makeGraph();

    printf("%d\n", edmondsKarp(0, -1));

    return 0;
}

void makeGraph(){

    int numNodes = m * n;

    makeNormalNodes(numNodes);

    makeTargetNode();

    makeSourceNode();

    parseInput();
}

void makeNormalNodes(int numNodes) {
    int nodeId, street, avenue;
    for(street = 1; street <= n; street++){
        for(avenue = 1; avenue <= m; avenue++){
            nodeId = m * (street - 1) + avenue;
            Node* node = new Node(nodeId, 0, 1, -1);
            makeAdjNode(node, avenue, street);
            graph.insert( pair<int,Node*>( nodeId, node ) );
        }
    }
}

void makeAdjNode(Node* node, int avenue, int street){

    int nodeId = node->getNodeId();

    if(street == 1){
        node->addAdjacency(nodeId + m);
    }
    else if(street == n){
        node->addAdjacency(nodeId - m);
    }
    else {
        node->addAdjacency(nodeId + m);
        node->addAdjacency(nodeId - m);
    }

    if(avenue == 1){
        node->addAdjacency(nodeId + 1);
    }
    else if(avenue == m){
        node->addAdjacency(nodeId - 1);
    }
    else {
        node->addAdjacency(nodeId + 1);
        node->addAdjacency(nodeId - 1);
    }
}

void makeSourceNode() {
    int sourceID = 0;
    Node* node = new Node(sourceID, c, c, 0);
    graph.insert( pair<int,Node*>( sourceID, node ) ); // mega-source
}

void makeTargetNode() {
    int targetID = -1;
    Node* node = new Node(targetID, 0, s, -1);
    graph.insert( pair<int,Node*>( targetID, node ) ); // mega-target
}

void parseInput(){
    int i, avenue, street;

    for(i = 0; i < s; i++){
        scanf("%d %d", &avenue, &street);
        int nodeId = m * (street - 1) + avenue;
        graph[-1]->addAdjacency(nodeId);
        graph[nodeId]->addAdjacency(-1);
    }

    for(i = 0; i < c; i++){
        scanf("%d %d", &avenue, &street);
        int nodeId = m * (street - 1) + avenue;
        graph[0]->addAdjacency(nodeId);
        graph[nodeId]->addAdjacency(0);
    }
}

int bfs(int startNodeId, int endNodeId)
{
    queue<int> q;
    q.push(startNodeId);

    while(!q.empty())
    {
        int currentNode = q.front();
        printf("current node: %d\n", currentNode);
        q.pop();

        for(int i : graph[currentNode]->getAdjacencies())
        {
            if(graph[i]->getParent() == -1 && !graph[i]->isFull())
            {
                graph[i]->setParent(currentNode);
                printf("(if) current node: %d   ----  parent: %d\n", i, currentNode);
                if(i == endNodeId)
                    return 1; //max flow of augmenting path always 1
                
                q.push(i);
            
            }
        }
    }
    return 0;
}

int edmondsKarp(int startNodeId, int endNodeId)
{
    int maxFlow = 0;
    while(true)
    {
        int flow = bfs(startNodeId, endNodeId);
        cout << "flow: " << flow << endl; 
        if (flow == 0)
            break;
        
        maxFlow += flow;
        int currentNode = endNodeId;
        while(currentNode != startNodeId)
        {
            int previousNode = graph[currentNode]->getParent();

            int currentNodeCapacity = graph[currentNode]->getCurrentCapacity();
            int previousNodeCapacity = graph[previousNode]->getCurrentCapacity();

            graph[currentNode]->setCurrentCapacity(currentNodeCapacity + 1);
            graph[previousNode]->setCurrentCapacity(previousNodeCapacity + 1);

            currentNode = previousNode;
        }

    }
    return maxFlow;
}
