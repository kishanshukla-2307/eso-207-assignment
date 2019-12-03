#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class node{
    public:
    int data;
    node * next;
    node()
    {
        next = NULL;
    }
};

int s,t;
static int time_check = 1;

void dfs(node ** arr,int sv,int * parent,bool * visited,int * time,int * desc_ans)
{
    int b;
    time[sv] = time_check;
    desc_ans[sv] = time_check;
    time_check++;
    node * head = arr[sv]->next;
    while(head!=NULL)
    {
        b = head->data;
        if(visited[b] == false)
        {
            visited[b] = true;
            parent[b] = sv;
            dfs(arr,b,parent,visited,time,desc_ans);
            desc_ans[sv] = min(desc_ans[b],desc_ans[sv]);
            if(desc_ans[b]>time[sv])
            {
                s = b;
                t = sv;
            }
        }
        else if(parent[sv] != b)
        {
            desc_ans[sv] = min(desc_ans[sv],time[b]);
        }
        head = head->next;
    }
    
}

void bfs(node ** arr,int sv,int * distance,bool * visited)
{
    int a,b;
    queue <int> store;
    store.push(sv);
    visited[sv] = true;
    distance[sv] = 0;
    while(store.empty() == false)
    {
        a = store.front();
        store.pop();
        node * head = arr[a]->next;
        while(head!=NULL)
        {
            b = head->data;
            head = head->next;
            if(visited[b] == false)
            {
                store.push(b);
                distance[b] = distance[a]+1;
                visited[b] = true;
            }
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
        int v,e,j,a,b,k,q,x,y;
        cin >> v;
        cin >> e;
        cin >> q;
        node ** arr = new node*[v];
        node ** last = new node*[v];
        for(j=0;j<v;j++)
        {
            node * item1 = new node;
            item1->data = j;
            arr[j] = item1;
            last[j] = item1;
        }
        
        for(k=0;k<e;k++)
        {
            cin >> a;
            cin >> b;
            node * item = new node;
            node * item2 = new node;
            item->data = b;
            item2->data = a;
            last[a]->next = item;
            last[b]->next = item2;
            last[a] = last[a]->next;
            last[b] = last[b]->next;
        }
        int * time = new int[v];
        bool * visited = new bool[v];
        int * parent = new int[v];
        int * desc_ans = new int[v];
        for(k=0;k<v;k++)
        {
            time[k] = 0;
            visited[k] = false;
            parent[k] = -1;
            desc_ans[k] = 0;
        }
        visited[0] = true;
        dfs(arr,0,parent,visited,time,desc_ans);
        node * head = arr[s];
        while(head->next->data != t)
        {
            head = head->next;
        }
        head->next = head->next->next;
        node * head_t = arr[t];
        while(head_t->next->data != s)
        {
            head_t = head_t->next;
        }
        head_t->next = head_t->next->next;
        int * distance = new int[v];
        for(k=0;k<v;k++)
        {
            distance[k] = 0;
            visited[k] = false;
        }
        bfs(arr,s,distance,visited);
        bfs(arr,t,distance,visited);
        for(k=0;k<q;k++)
        {
            cin >> x;
            cin >> y;
            cout << 1+distance[x]+distance[y]<<endl;
        }
        return 0;
}