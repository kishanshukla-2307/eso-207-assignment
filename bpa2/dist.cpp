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
    lli* discovery;
    lli* connectivity;
    lli* parent;
    lli* distance;
    struct Node** adj;
    struct Node** bridge;
};

struct Graph* buildGraph(lli v);
void addedge(struct Graph*, lli src, lli dest);
void addbridge(struct Graph* graph, lli src, lli dest);
struct Node* createNode(lli val);
void dfs(struct Graph* g, lli s);
lli min(lli, lli);
void breakedge(struct Graph*, lli , lli);
void bfs(struct Graph*, lli);

struct Queue 
{ 
    int head, tail, size; 
    unsigned capacity; 
    int* array; 
}; 


struct Queue* buildQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->head = 0;
    queue->size = 0; 
    queue->tail = capacity - 1;
    queue->array = (int*) malloc(capacity * sizeof(int)); 
    return queue; 
} 

int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity); 
} 

int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) 
{ 
    if (isFull(queue)) 
        return; 
    queue->tail = (queue->tail + 1)%queue->capacity; 
    queue->array[queue->tail] = item; 
    queue->size += 1; 
} 

int dequeue(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return -1; 
    int x = queue->array[queue->head]; 
    queue->head = (queue->head + 1)%queue->capacity; 
    queue->size -= 1; 
    return x; 
} 
 
int head(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return -1; 
    return queue->array[queue->head]; 
} 

int tail(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return -1; 
    return queue->array[queue->tail]; 
} 

int main(){
    lli v,e,temp1,temp2,q;
    cin >> v >> e >> q;
    struct Graph* g = buildGraph(v);
    struct Graph* g2 = buildGraph(v);
    for(lli i=0; i<e; ++i){
        cin >> temp1 >> temp2;
        addedge(g, temp1, temp2);
        addedge(g2, temp1, temp2);
    }
    for (lli i=0; i<v; i++){
        if(!g->visited[i]){
            g->parent[i]=-1;
            dfs(g, i);
        }
    }
    lli a,b;
    for(lli i=0; i<v; ++i){
        struct Node* temp3 = g->bridge[i];
        if(temp3!=NULL){
            a=i;
            b=temp3->val;
            break;
        }
    }
    breakedge(g2, a, b);
    bfs(g2, a);
    bfs(g2, b);
    // for(lli i=0; i<v; ++i){
    //     struct Node* temp = g2->adj[i];
    //     while(temp!=NULL){
    //         cout << i << "----" << temp->val << "\n";
    //         temp=temp->next;
    //     }
    // }
    while(q--){
        lli s,t;
        cin >> s >> t;
        cout << g2->distance[s] + g2->distance[t] + 1 << "\n";
    }
    return 0;
}

void bfs(struct Graph* g, lli s){
    struct Queue* q = buildQueue(g->v);
    enqueue(q, s);
    g->visited[s]=true;
    g->distance[s]=0;
    while(!isEmpty(q)){
        lli v = dequeue(q);
        struct Node* temp = g->adj[v];
        while(temp!=NULL){
            if(!g->visited[temp->val]){
                g->parent[temp->val]=v;
                g->distance[temp->val]=g->distance[v]+1;
                g->visited[temp->val]=true;
                enqueue(q, temp->val);
            }
            temp = temp->next;
        }
    }
    return;
}

void breakedge(struct Graph* g, lli x, lli y){
    struct Node* temp = g->adj[x], *temp2=g->adj[x];
    if(temp->val==y){
        g->adj[x]=temp->next;
    }else{
        while(temp->val!=y){
            temp2=temp;
            temp=temp->next;
        }
        temp2->next=temp->next;
    }
    temp = g->adj[y],temp2=g->adj[y];
    if(temp->val==x){
        g->adj[y]=temp->next;
    }else{
        while(temp->val!=x){
            temp2=temp;
            temp=temp->next;
        }
        temp2->next=temp->next;
    }
}

struct Graph* buildGraph(lli v){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = v;
    graph->adj = (struct Node**)malloc(v*sizeof(struct Node*));
    graph->bridge = (struct Node**)malloc(v*sizeof(struct Node*));
    graph->discovery = (lli*)malloc(v*sizeof(lli));
    graph->connectivity = (lli*)malloc(v*sizeof(lli));
    graph->visited = (bool*)malloc(v*sizeof(bool));
    graph->parent = (lli*)malloc(v*sizeof(lli));
    graph->distance = (lli*)malloc(v*sizeof(lli));
    for(lli i=0; i<v; ++i){
        graph->adj[i]=NULL;
        graph->bridge[i]=NULL;
        graph->visited[i]=false;
        graph->discovery[i]=0;
        graph->connectivity[i] =0;
        graph->parent[i]=-1;
        graph->distance[i]=0;
    }
    return graph;
}

void addedge(struct Graph* graph, lli src, lli dest){
    struct Node* node = createNode(dest);
    node->next = graph->adj[src];
    graph->adj[src] = node;
    struct Node* node2 = createNode(src);
    node2->next = graph->adj[dest];
    graph->adj[dest] = node2;
}

void addbridge(struct Graph* graph, lli src, lli dest){
    struct Node* node = createNode(dest);
    node->next = graph->bridge[src];
    graph->bridge[src] = node;
}

struct Node* createNode(lli val){
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}

void dfs(struct Graph* g, lli s){
    struct Node* src = g->adj[s];
    struct Node* temp = src;
    Time++;
    g->visited[s]=true;
    g->discovery[s]=Time;
    g->connectivity[s]=Time;
    while(temp!=NULL){
        if(!g->visited[temp->val]){
            g->parent[temp->val]=s;
            dfs(g, temp->val);
            g->connectivity[s] = min(g->connectivity[s], g->connectivity[temp->val]);
            if(g->discovery[s]<g->connectivity[temp->val]){
                if(s>temp->val)
                    addbridge(g, temp->val, s);
                else
                    addbridge(g, s, temp->val);
            }
        }else if(g->parent[s]!=temp->val)
            g->connectivity[s] = min(g->connectivity[s], g->discovery[temp->val]);
        temp = temp->next;
    }
    return;
}

lli min(lli x, lli y){
    if(x>y)
        return y;
    else
        return x;
}