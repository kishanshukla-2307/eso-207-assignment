#include<iostream>
#include<stdlib.h>

typedef long long int lli;
using namespace std;

lli inf=1e18;
lli Time=0;
struct Node{
    lli val;
    struct Node* next;
};

struct Graph{
    lli v;
    bool* visited;
    lli* finish;
    struct Node** adj;
};

struct Graph* buildGraph(lli v);
void addedge(struct Graph*, lli src, lli dest);
struct Node* createNode(lli val);
lli dfs(struct Graph* g, lli s, lli len);

int main(){
    int t;
    cin >> t;
    while(t--){
        lli v,e,temp1,temp2;
        cin >> v >> e;
        struct Graph* g = buildGraph(v);
        struct Graph* gt = buildGraph(v);
        for(lli i=0; i<e; ++i){
            cin >> temp1 >> temp2;
            addedge(g, temp1, temp2);
            addedge(gt, temp2, temp1);
        }
        for (lli i=0; i<v; i++){
            if(!g->visited[i])
                dfs(g, i, 0);
        }
        lli len=0;
        for (lli i=0; i<v; i++)
            if(g->finish[i]>len)
                len=g->finish[i];
        len++;
        lli hash[len], lmx=0,temp=0;
        for (lli i=0; i<len; i++)
            hash[i]=-1;
        for (lli i=0; i<v; i++)
            hash[g->finish[i]]=i;
        for(lli i=len-1; i>=0; i--){
            if(hash[i]!=-1){
                if(!gt->visited[hash[i]]){
                    temp=dfs(gt, hash[i], 0);
                    if(temp>lmx)
                        lmx=temp;
                }
            }
        }
        cout << lmx << "\n";
    }
    return 0;
}

struct Graph* buildGraph(lli v){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = v;
    graph->adj = (struct Node**)malloc(v*sizeof(struct Node*));
    graph->finish = (lli*)malloc(v*sizeof(lli));
    graph->visited = (bool*)malloc(v*sizeof(bool));
    for(lli i=0; i<v; ++i){
        graph->adj[i]=NULL;
        graph->visited[i]=false;
        graph->finish[i]=0;
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

lli dfs(struct Graph* g, lli s, lli len){
    struct Node* src = g->adj[s];
    struct Node* temp = src;
    g->visited[s]=true;
    Time++;
    while(temp!=NULL){
        if(!g->visited[temp->val])
            len+=dfs(g, temp->val, 0);
        temp = temp->next;
    }
    len++;
    Time++;
    g->finish[s]=Time;
    return len;
}