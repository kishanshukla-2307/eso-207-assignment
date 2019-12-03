#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct stack{
    int top;
    int *arr;
};

void Push(int key,struct stack* s){
    s->top = s->top + 1;
    s->arr[s->top]=key;
}

int Top(struct stack* s){
    return s->arr[s->top];
}

void Pop(struct stack* s){
    s->top = s->top - 1;
}

bool Empty(struct stack* s){
    if(s->top==-1)
        return true;
    return false;
}

int main() {
    long int s,temp,n;
    cin >> s;
    while(s--){
        cin >> n;
        long int h[n],jb[n];
        for(long int i=0; i<n; ++i){
            cin >> h[i];
        }
        struct stack *st,s;
        st = &s;
        st->arr = (int*)malloc(sizeof(int)*n);
        st->top=-1;
        Push(0, st);
        jb[0]=1;
        for(long int i=1; i<n; ++i){
            while((h[Top(st)]<=h[i])){
                Pop(st);
                if(Empty(st))
                    break;
            }
            if(Empty(st)){
                jb[i]=i+1;
                Push(i, st);
            }
            else{
                jb[i]=i-Top(st);
                Push(i, st);
            }
        }
        for(long int i=0; i<n; ++i){
            cout << jb[i] << "\n";
        }
    }
    return 0;
}