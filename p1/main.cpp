#include <stdio.h>
#include <vector>

struct component
{
    int node;
    std::vector<int> connection;
};

void node_parser(int n, component *graph[]);
void connection_parser(int m, component *graph[]);

int main()
{
    int n, m;
    scanf("%d,%d", n, m);

    if (n < 2 || m < 1){
        printf("error: wrong input\n");
        return -1;
    }

    component *graph[n+1];
    
    node_parser(n, graph);
    connection_parser(m, graph);

    return 0;
}

void node_parser(int n, component *graph[])
{
    for (int i = 1; i < n+1; i++)
    {
        scanf("%d", graph[i]->node);
    }
}

void connection_parser(int m, component *graph[])
{
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", a, b);
        graph[a]->connection.push_back(b);
    } 
}