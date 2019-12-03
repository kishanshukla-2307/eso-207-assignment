#include<iostream>
#include<stdlib.h>
typedef long long int lli;
using namespace std;

lli inf=1e18;
lli Time=0;
struct edge{
    lli x;
    lli y;
    lli w;
};


struct setp{
    lli parent;
    lli height;
};

lli find(struct setp* s, lli v);
void Union(struct setp*s, lli u, lli v);
void quicksort(struct edge* g, lli l, lli r);
lli partition(struct edge* g, lli l, lli r);
lli random(lli l, lli r);

int main(){
    lli v,e,temp1,temp2,temp3,q,ans,n;
    cin >> v >> e >> q;
    struct edge g[e],mst[v],mst1[v];
    for(lli i=0; i<e; ++i){
        scanf("%ld %ld %ld",&temp1,&temp2,&temp3);
        g[i].x=temp1;
        g[i].y=temp2;
        g[i].w=temp3;
    }
    quicksort(g,0,e-1);
    struct setp sets[v];
    for(lli i=0; i<v; ++i){
        sets[i].parent = i;
        sets[i].height = 0;
    }
    ans=0,n=0;
    for(lli i=0; i<e; ++i){
        lli xr = find(sets, g[i].x), yr = find(sets, g[i].y);
        if(xr!=yr){
            ans += g[i].w;
            mst[n] = g[i];
            Union(sets, xr, yr);
            n++;
        }
        if(n==v-1){
            break;
        }
    }
    cout << ans << "\n";
    while(q--){
        scanf("%ld %ld %ld",&temp1,&temp2,&temp3);
        lli x=temp1,y=temp2,z=temp3;
        lli i,j=0;
        for(i=0; i<v-1; ++i){
            if(mst[i].w>z){
                mst1[j].x=x;
                mst1[j].y=y;
                mst1[j].w=z;
                j++;
                i--;
                z=inf;
            }
            else{
                mst1[j]=mst[i];
                j++;
            }
        }
        struct setp sets[v];
        for(lli i=0; i<v; ++i){
            sets[i].parent = i;
            sets[i].height = 0;
        }
        ans=0,n=0;
        for(lli i=0; i<v; ++i){
            lli xr = find(sets, mst1[i].x), yr = find(sets, mst1[i].y);
            if(xr!=yr){
                ans += mst1[i].w;
                mst[n].x = mst1[i].x;
                mst[n].y = mst1[i].y;
                mst[n].w = mst1[i].w;
                Union(sets, xr, yr);
                n++;
            }
            if(n==v-1){
                break;
            }
        }
        
        cout << ans << "\n";
    }
    return 0;
}

void quicksort(struct edge* g, lli l, lli r){
    if(l<r){
        lli m = partition(g, l, r);
        quicksort(g, l, m-1);
        quicksort(g, m+1, r);
    }
    return;
}

lli partition(struct edge* g, lli l, lli r){
    lli rnd = random(l,r);
    struct edge temp = g[r];
    g[r] = g[rnd];
    g[rnd] = temp;
    struct edge key=g[r];
    lli i = l-1;
    for(lli j=l; j<=r-1; ++j){
        if(g[j].w <= key.w){
            i++;
            struct edge temp = g[i];
            g[i] = g[j];
            g[j] = temp;
        }
    }
    temp = g[i+1];
    g[i+1] = g[r];
    g[r] = temp;
    return i+1;
}

lli random(lli l, lli r){
    return (rand() % (r - l + 1)) + l;
}

void Union(struct setp*s, lli u, lli v){
    lli ur = find(s, u);
    lli vr = find(s, v);
    if(s[ur].height==s[vr].height){
        s[vr].parent=ur;
        s[ur].height +=1;
    }
    else if(s[ur].height>s[vr].height){
        s[vr].parent=ur;
    }
    else{
        s[ur].parent=vr;
    }
}

lli find(struct setp* s, lli v){
    if(s[v].parent!=v){
        s[v].parent=find(s, s[v].parent);
    }
    return s[v].parent;
}