#include <stdio.h>
#include <vector>

struct node
{
    int student;
    std::vector<int> friendship;
};

void student_parser(int n, node *graph[]);
void friendship_parser(int m, node *graph[]);

int main()
{
    int n, m;
    scanf("%d,%d", n, m);

    if (n < 2 || m < 1){
        printf("error: wrong input\n");
        return -1;
    }

    node *graph[n+1];
    int *solution[n+1];
    
    student_parser(n, graph);
    friendship_parser(m, graph);

    return 0;
}

void student_parser(int n, node *graph[])
{
    for (int i = 1; i < n+1; i++)
    {
        scanf("%d", graph[i]->student);
    }
}

void friendship_parser(int m, node *graph[])
{
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", a, b);
        graph[a]->friendship.push_back(b);
    } 
}