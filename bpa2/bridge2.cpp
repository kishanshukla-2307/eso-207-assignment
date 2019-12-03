 
/*
// Sample code to perform I/O:
#include <stdio.h>
int main(){
	int num;
	scanf("%d", &num);              			// Reading input from STDIN
	printf("Input number is %d.\n", num);       // Writing output to STDOUT
}
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int V;
    struct Node *next;
};
typedef struct Node Node;

struct Graph
{
    int V;
    Node **adj;
};
typedef struct Graph Graph;

Graph *createGraph(int V, int E);
void addEdges(Graph *G, int E);
void addEdge(Graph *G, int p, int q);

Graph *createGraph(int V, int E)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->V = V;
    G->adj = (Node **)malloc(V * sizeof(Node*));
    for(int i = 0; i < V; i++)
        G->adj[i] = NULL;
    return G;
}

void addEdge(Graph *G, int p, int q)
{
    Node *p_node = (Node *)malloc(sizeof(Node));
    p_node->V = p;
    p_node->next = G->adj[q];
    G->adj[q] = p_node;

    Node *q_node = (Node *)malloc(sizeof(Node));
    q_node->V = q;
    q_node->next = G->adj[p];
    G->adj[p] = q_node;
}

void addEdges(Graph *G, int E)
{
    for(; E > 0; E--)
    {
        int p, q;
        scanf("%d %d\n", &p, &q);
        addEdge(G, p, q);
    }
}

void DFS(Graph *G, int v, int p, int q, int *visited)
{
    visited[v] = 1;
    Node *n = G->adj[v];
    for(; n; n = n->next)
    {
        // ignore edge p-q
        if(v == p && n->V == q)
            continue;
        if(v == q && n->V == p)
            continue;
        if(visited[n->V] == 0)
            DFS(G, n->V, p, q, visited);
    }
}

int checkBridge(Graph *G, int p, int q)
{
    int visited[G->V];
    for(int i = 0; i < G->V; i++)
        visited[i] = 0;
    DFS(G, p, p, q, visited);
    return !(visited[q]);
}

int main(void)
{
    int T;
    scanf("%d\n", &T);
    for(; T > 0; T--)
    {
        int V, E, p, q;
        scanf("%d\n%d\n", &V, &E);
        Graph *G = createGraph(V, E);
        addEdges(G, E);
        for (long long int i = 0; i < V; i++){
            Node* temp = G->adj[i];
            while(temp!=NULL){
                
            }
        }
        
        if(checkBridge(G, p, q))
            printf("Bridge\n");
        else
            printf("Not Bridge\n");
    }
    return 0;
}