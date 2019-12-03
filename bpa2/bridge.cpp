#include<iostream>
#include<stdlib.h>
using namespace std;

long long int inf=1e18;
long long int t=0;


struct Graph* makegraph(long long int v);
void gE(struct Graph*, long long int src, long long int dest);
void addbridge(struct Graph* graph, long long int src, long long int dest);
struct Node* makeNode(long long int val);
void findbridge(struct Graph* g, long long int s, long long int dest);
long long int min(long long int, long long int);

struct Node{
    long long int val;
    struct Node* next;
};

struct Graph{
    long long int v;
    bool* vis;
    long long int* disc;
    long long int* lowest;
    long long int* p;
    struct Node** adjacency;
    struct Node** bridge;
};


long long int min(long long int x, long long int y){
    if(x>y)
        return y;
    else
        return x;
}

int main(){
    long long int v,e;
    cin >> v >> e;
    struct Graph* g = makegraph(v);
    long long int t1,t2;
    for(long long int i=0; i<e; ++i){
        cin >> t1 >> t2;
        gE(g, t1, t2);
    }
    for (long long int i=0; i<v; i++){
        if(!g->vis[i]){
            g->p[i]=-1;
            findbridge(g, i, 0);
        }
    }
    int flag=1;
    for(long long int i=0; i<v; ++i){
        struct Node* temp3 = g->bridge[i];
        while(temp3!=NULL){
            flag=0;
            cout << i << " " << temp3->val << "\n";
            temp3 = temp3->next;
        }
    }
    if(flag)
        cout<< "No\n";
    return 0;
}

struct Graph* makegraph(long long int v){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = v;
    graph->adjacency = (struct Node**)malloc(v*sizeof(struct Node*));
    graph->bridge = (struct Node**)malloc(v*sizeof(struct Node*));
    graph->disc = (long long int*)malloc(v*sizeof(long long int));
    graph->lowest = (long long int*)malloc(v*sizeof(long long int));
    graph->vis = (bool*)malloc(v*sizeof(bool));
    graph->p = (long long int*)malloc(v*sizeof(long long int));
    for(long long int i=0; i<v; ++i){
        graph->adjacency[i]=NULL;
        graph->bridge[i]=NULL;
        graph->vis[i]=false;
        graph->disc[i]=0;
        graph->lowest[i] =0;
        graph->p[i]=-1;
    }
    return graph;
}


void findbridge(struct Graph* g, long long int s, long long int dest){
    struct Node* src = g->adjacency[s];
    struct Node* temp = src;
    t++;
    g->vis[s]=true;
    g->disc[s]=t;
    g->lowest[s]=t;
    while(temp!=NULL){
        if(!g->vis[temp->val]){
            g->p[temp->val]=s;
            findbridge(g, temp->val, 0);
            g->lowest[s] = min(g->lowest[s], g->lowest[temp->val]);
            if(g->disc[s]<g->lowest[temp->val]){
                if(s>temp->val)
                    addbridge(g, temp->val, s);
                else
                    addbridge(g, s, temp->val);
            }
        }else if(g->p[s]!=temp->val)
            g->lowest[s] = min(g->lowest[s], g->disc[temp->val]);
        temp = temp->next;
    }
    return;
}

void gE(struct Graph* graph, long long int src, long long int dest){
    struct Node* n = makeNode(dest);
    n->next = graph->adjacency[src];
    graph->adjacency[src] = n;
    struct Node* n2 = makeNode(src);
    n2->next = graph->adjacency[dest];
    graph->adjacency[dest] = n2;
}

void addbridge(struct Graph* graph, long long int src, long long int dest){
    struct Node* n = makeNode(dest);
    n->next = graph->bridge[src];
    graph->bridge[src] = n;
}

struct Node* makeNode(long long int val){
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}
