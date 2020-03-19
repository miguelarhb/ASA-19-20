/*
Miguel Baptista - 86481
Mariana Chinopa - 92518
*/

#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

class Node{
    int _id;
    int _grade;
    bool _onStack;
    int _low;
    int _discover;
    vector<int> _connections;
    
    public:
        Node() { }

        Node(int id, int grade, bool onStack = false, int low = -1, int discover = -1)
        {
            _id = id;
            _grade = grade;
            _onStack = onStack;
            _low = low; 
            _discover = discover;
        }

        int get_id() { return _id; }
        
        void set_id(int id) { _id = id; }

        int get_grade() { return _grade; }
        
        void set_grade(int grade) { _grade = grade; }

        bool get_onStack() { return _onStack; }

        void set_onStack(bool onStack) { _onStack = onStack; }

        int get_low() { return _low; }
        
        void set_low(int low) { _low = low; }

        int get_discover() { return _discover; }
        
        void set_discover(int discover) { _discover = discover; }

        vector<int> get_connections() { return _connections; }
        
        void set_connections(vector<int> connections) { _connections = connections; }

        void add_connection(int id) { _connections.push_back(id); }

};

vector<Node*> graph;
stack<int> discover_tracker;
int visited = 0;

void grades_parser(int n);
void connections_parser(int m);
int min(int a, int b);
bool max(int a, int b);
void tarjan(int n);
void tarjanDFS(int id);
void print_output(int n);

int main()
{
    int n, m;
    scanf("%d,%d", &n, &m);

    if (n < 2 || m < 1){
        printf("error: wrong input\n");
        return -1;
    }

    grades_parser(n);
    connections_parser(m);

    tarjan(n);

    print_output(n);

    return 0;
}

void grades_parser(int n)
{
    int grade;
    graph.push_back(new Node()); //jump graph[0]
    for (int i = 1; i < n+1; i++)
    {
        scanf("%d", &grade);
        Node* node = new Node(i, grade);
        graph.push_back(node);
    }
}  

void connections_parser(int m)
{
    int a, b;
    for(int i = 0; i < m; i++){
        scanf("%d %d", &a, &b);
        graph[a]->add_connection(b);
    } 
}

int min(int a, int b)
{
   return (a < b) ? a : b;
}

bool max(int a, int b)
{
   return (a > b) ? true : false;
}

void tarjan(int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (graph[i]->get_discover() == -1)
            tarjanDFS(i);    
    }

}

void tarjanDFS(int id)
{
    discover_tracker.push(id);
    graph[id]->set_onStack(true);
    graph[id]->set_discover(visited);
    graph[id]->set_low(visited);
    visited++;
    for (int j : graph[id]->get_connections())
    {
        if (graph[j]->get_discover() == -1)
        {
            tarjanDFS(j);
            graph[id]->set_low( min ( graph[id]->get_low(), graph[j]->get_low() ) );
        }
        else if (graph[j]->get_onStack())
        {
            graph[id]->set_low( min ( graph[id]->get_low(), graph[j]->get_discover() ) );
        }
    }

    int max_grade = 0;
    vector<int> scc;

    if ( graph[id]->get_discover() == graph[id]->get_low() )
    {
        while (!discover_tracker.empty())
        {
            int stack_node = discover_tracker.top();
            discover_tracker.pop();
            graph[stack_node]->set_onStack(false);
            graph[stack_node]->set_low( graph[id]->get_discover() );

            if ( graph[stack_node]->get_grade() > max_grade )
            {
                max_grade = graph[stack_node]->get_grade();
            }
            scc.push_back( graph[stack_node]->get_id() );          

            if (stack_node == id)
            {
                break;
            } 
        }
    }

    for (int i : scc) 
    {
        graph[i]->set_grade(max_grade);
    }
}

void print_output(int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", graph[i]->get_grade());
    }
}
