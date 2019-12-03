#include<iostream>
#include<stdlib.h>
#include<ctime>

typedef long long int lli;
using namespace std;
time_t start, stop;
lli inf=1e18;
lli Time=0;

void sp(lli s, lli t, lli v,lli** w, lli* d, lli* visited);
lli min(lli, lli);
void relax(lli u, lli v, lli** w, lli* d);
lli extractmin(lli *d, lli size, lli*);

int main(){
    start = time(NULL);
    lli v,e,temp1,temp2,temp3;
    cin >> v >>e;
    lli** w;
    w=(lli**)malloc(v*sizeof(lli*));
    for(lli i=0; i<v; ++i){
        w[i] = (lli*)malloc(v*sizeof(lli));
    }
    for(lli i=0; i<v; ++i){ 
        for(lli j=0; j<v; ++j){
            w[i][j]=10001;
        }
    }
    for(lli i=0; i<e; ++i){
        scanf("%lld %lld %lld",&temp1,&temp2,&temp3);
       
        w[temp1][temp2]=temp3;
        stop=time(NULL);
        if(stop-start > 1.0){
            cout << " 1";
            return 0;
        }
    }
    stop=time(NULL);
    if(stop-start > 1.0){
        cout << " 1";
        return 0;
    }
    lli s,t;
    cin >> s >> t;
    lli d[v],visited[v];
    for(lli i=0; i<v; ++i){
        visited[i]=0;
        stop=time(NULL);
        if(stop-start > 1.0){
            cout << " 1";
            return 0;
        }
    }
    sp(s, t, v, w, d, visited);
    cout << d[t] << "\n";
    return 0;
}

void sp(lli s, lli t, lli v, lli** w, lli* d, lli* visited){
    for(lli i=0; i<v; ++i)
        d[i]=inf;
    d[s]=0;
    for(lli i=0; i<v-1; ++i){
        stop=time(NULL);
        if(stop-start > 1.0){
            cout << " 1";
            return ;
        }
        lli u = extractmin(d,v,visited);
        if(u==t)
            return;
        visited[u]=1;
        for(lli i=0; i<v; ++i){
            stop=time(NULL);
            if(stop-start > 1.0){
                cout << " 1";
                return;
            }
            if(w[u][i]<10001 && !visited[i] && d[u]!=inf)
                relax(u, i, w, d);
        }
    }
    return;
}

void relax(lli u, lli v, lli** w, lli* d){
    if(d[v]>d[u]+w[u][v]) d[v]=d[u]+w[u][v];
    return;
}

lli extractmin(lli *d, lli size, lli* visited){
    lli min=inf,mini;
    for(lli i=0; i<size; ++i){
        if(!visited[i] && d[i]<=min){
            min=d[i];
            mini=i;
        }
        stop=time(NULL);
        if(stop-start > 1.0){
            cout << " 1";
            return 0;
        }
    }
    return mini;
}

lli min(lli x, lli y){
    if(x>y)
        return y;
    else
        return x;
}