/*
Miguel Baptista - 86481
Mariana Chinopa - 92518
*/

#include <stdio.h>
#include <utility>
#include <vector>
#include <map>

using namespace std;

class Node {
    int _nodeId;
    int _currentCapacity;
    int _maxCapacity;
    vector<int> _adjacencies; //node ids (2-5 node ids (exceptions mega source and mega target))

    public:
        Node(int nodeId, int currentCapacity, int maxCapacity){
            _nodeId = nodeId;
            _currentCapacity = currentCapacity;
            _maxCapacity = maxCapacity;
        }

        int getNodeId() { return _nodeId; }

        void setNodeId(int nodeId) { _nodeId = nodeId; } 

        int getCurrentCapacity() { return _currentCapacity; }

        void setCurrentCapacity(int currentCapacity) { _currentCapacity = currentCapacity; } 

        int getMaxCapacity() { return _maxCapacity; }

        void setMaxCapacity(int maxCapacity) { _maxCapacity = maxCapacity; } 

        vector<int> getAdjacencies() { return _adjacencies; }

        void setAdjacencies(vector<int> adjacencies) { _adjacencies = adjacencies; }

        void addAdjacency(int adj) { _adjacencies.push_back(adj); }

        bool isFull() { return (_currentCapacity == _maxCapacity); }
};


map<int, Node*> graph;
int m, n, s, c;
vector<int> adjNode, adjSource, adjTarget;

int main() {

    scanf("%d,%d", &m, &n);
    scanf("%d,%d", &s, &c);

    if (m < 1 || n < 1 || s < 1 || c < 1) {
        printf("error: wrong input\n");
        return -1;
    }

    makeGraph();

    return 0;
}

void makeGraph(){

    int numNodes = m * n;

    makeNormalNodes(numNodes);

    makeTargetNode();

    makeSourceNode();
}

void makeNormalNodes(int numNodes) {
    int nodeId, street, avenue;
    for(avenue = 1; avenue <= m; avenue++){
        for(street = 1; street <= n; street++){
            nodeId = avenue * street;
            Node* node = new Node(nodeId, 0, 1);
            makeAdjNode(node, avenue, street);
            graph.insert( pair<int,Node*>( nodeId, node ) );
        }
    }
}

void makeAdjNode(Node* node, int avenue, int street){

    int nodeId = node->getNodeId();

    if(street == 1){
        node->addAdjacency(nodeId + 4);
    }
    else if(street == n){
        node->addAdjacency(nodeId - 4);
    }
    else {
        node->addAdjacency(nodeId + 4);
        node->addAdjacency(nodeId - 4);
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
    Node* node = new Node(sourceID, 0, c);
    graph.insert( pair<int,Node*>( sourceID, node ) ); // mega-source
}

void makeTargetNode() {
    int targetID = -1;
    Node* node = new Node(targetID, 0, s);
    graph.insert( pair<int,Node*>( targetID, node ) ); // mega-target
}