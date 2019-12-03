#include<iostream>
#include<stdlib.h>

typedef long long int lli;
using namespace std;

lli inf=1e18;
struct Node{
    lli val;
    struct Node* next;
};

struct Graph{
    lli v;
    bool* visited;
    bool* color;
    struct Node** adj;
};

struct Graph* buildGraph(lli v);
void addedge(struct Graph*, lli src, lli dest);
struct Node* createNode(lli val);
bool dfs(struct Graph* g, lli s);

int main(){
    int t;
    cin >> t;
    while(t--){
        lli v,e,temp1,temp2;  cin >> v >> e;
        struct Graph* g = buildGraph(v);
        for(lli i=0; i<e; ++i){
            cin >> temp1 >> temp2;
            temp1--; temp2--;
            addedge(g, temp1, temp2);
        }
        bool temp;
        for (lli i=0; i<v; i++){
            if(!g->visited[i]){
                g->color[i]=false;
                g->visited[i]=true;
                temp=dfs(g, i);
                if(!temp){
                    cout << "No" << "\n";
                    break;
                }
            }
        }
        if(temp)
            cout << "Yes" << "\n";
    }
    return 0;
}

struct Graph* buildGraph(lli v){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = v;
    graph->adj = (struct Node**)malloc(v*sizeof(struct Node*));
    graph->color = (bool*)malloc(v*sizeof(bool));
    graph->visited = (bool*)malloc(v*sizeof(bool));
    for(lli i=0; i<v; ++i){
        graph->adj[i]=NULL;
        graph->visited[i]=false;
    }
    return graph;
}

void addedge(struct Graph* graph, lli src, lli dest){
    struct Node* node = createNode(dest);
    node->next = graph->adj[src];
    graph->adj[src] = node;
}

struct Node* createNode(lli val){
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}

bool dfs(struct Graph* g, lli s){
    struct Node* src = g->adj[s];
    struct Node* temp = src;
    while(temp!=NULL){
        if(!g->visited[temp->val]){
            g->visited[temp->val]=true;
            g->color[temp->val]=!g->color[s];
            if(!dfs(g, temp->val))
                return false;
        }
        else{
            if(g->color[temp->val]==g->color[s])
                return false;
        }
        temp=temp->next;
    }

    return true;
}