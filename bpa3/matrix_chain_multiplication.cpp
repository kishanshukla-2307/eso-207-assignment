#include <cmath>
#include <iostream>
using namespace std;
typedef long long int lli;
lli inf=1e18;
lli mcm(lli* p, lli**m, lli** s, lli l, lli r){
    if(l==r){
        return 0;
    }
    lli min=inf, temp, b;
    for(lli i=l; i<r; ++i){
        if(m[l][i]==-1){
            m[l][i] = mcm(p,m,s,l,i);
        }
        if(m[i+1][r]==-1){
            m[i+1][r] = mcm(p,m,s,i+1,r);
        }
        temp = m[l][i] + m[i+1][r] + p[l-1]*p[i]*p[r];
        if(temp < min){
             min = temp;
             s[l][r] = i;
        }
    }
    return min;
}

int main() {
    int t;
    cin >> t;
    while(t--){
        int k;
        cin >> k;
        lli p[k+1];
        for(int i=0; i<k+1; ++i){
            cin >> p[i];
        }
        lli**m, **s;
        m = (lli**)malloc((k+1)*sizeof(lli*));
        s = (lli**)malloc((k+1)*sizeof(lli*));
        for(lli i=0; i<k+1; ++i){
           m[i] = (lli*)malloc((k+1)*sizeof(lli));
           s[i] = (lli*)malloc((k+1)*sizeof(lli));
        }
        for(lli i=0; i<k+1; ++i){
           for(lli j=0; j<k+1; ++j){
               m[i][j]=-1;
               s[i][j]=-1;
           }
           s[i][i]=i;
           m[i][i]=0;
        }
        cout << mcm(p, m, s, 1, k) << "\n";
    }
    return 0;
}