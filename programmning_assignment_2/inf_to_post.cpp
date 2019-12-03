#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<string>
using namespace std;

long int top=-1;

void Push(char c, char *s){
    top++;
    s[top]=c;
}

void Pop(char *s){
    top--;
}

bool Empty(){
    if(top==-1)
        return true;
    return false;
}

char Top(char *s){
    return s[top];
}

int precedence(char c){
    if(c=='-')
        return 1;
    if(c=='+')
        return 2;
    if(c=='*')
        return 3;
    if(c=='/')
        return 4;
    if(c=='^')
        return 5;
    return 0;
}


int main() {
    string inf,post;
    cin >> inf;
    char s[inf.size()];
    for(int i=0; i<inf.length(); ++i){
        if( (inf[i] >= 65 && inf[i] <= 90) || (inf[i]>=97 && inf[i]<=122) || (inf[i]>=48 && inf[i]<=57)){
            post.push_back(inf[i]);
        }
        else if( inf[i]=='(' || inf[i]==')'){
            if(inf[i]=='(')
                Push(inf[i], s);
            else{
                while( Top(s) != '(' ){
                    post.push_back(Top(s));
                    Pop(s);
                }
                Pop(s);
            }
        }
        else{
            while(!Empty()){
                if( precedence(inf[i]) > precedence(Top(s)))
                    break;
                post.push_back(Top(s));
                Pop(s);
            }
            Push(inf[i], s);
        }
    }
    while( !Empty()){
        post.push_back(Top(s));
        Pop(s);
    }
    for(int i=0; i<post.length(); ++i){
        cout << post[i];
    }
    return 0;
}
