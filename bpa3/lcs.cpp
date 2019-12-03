#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long int lli;
long int max(long int x, long int y){
    if(x>y)
        return x;
    else
        return y;
}
int main() {
    lli t;
    // cin >> t;
    scanf("%lld",&t);
    while(t--){
        lli m,n;
        // cin >> m >> n;
        scanf("%lld %lld",&m,&n);
        char sp[m+1],tp[n+1];
        scanf("%s %s",sp,tp);
        // // cout << s+1 ;
        lli pre=0,suff=0;
        lli ans[2][n+1]; 
        lli k; 
        for (lli i=0; i<=m; i++){
            k=i%2; 
            for (lli j=0; j<=n; j++){ 
                if (i==0 || j==0){
                    ans[k][j] = 0;
                }
                else if (sp[i-1] == tp[j-1]) {
                     ans[k][j] = ans[1 - k][j - 1] + 1;
                }
                else{
                    ans[k][j] = max(ans[1 - k][j], ans[k][j - 1]); 
                }
            }
        }
        // if(pre+suff>=min)
        //     cout << min << "\n";
        // else
            // cout << ans[k][n] << "\n";
        printf("%lld\n",ans[k][n]);
    }
    return 0;
}
