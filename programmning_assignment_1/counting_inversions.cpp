#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

long long int MergeSort_CrossInversions(long long int * arr, int l, int m, int r);

long long int MergeSort_CountInversions(long long int * arr, int l, int r);

int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        long long int arr[n];
        for(int i=0; i<n; ++i){
            scanf("%lld",&arr[i]);
        }
        printf("%lld\n",MergeSort_CountInversions(arr, 0, n-1));
        // for(int i=0; i<n; ++i){
        //     printf("%lld ",arr[i]);
        // }
    }
    return 0;
}

long long int MergeSort_CountInversions(long long int * arr, int l, int r){
    if(l<r){
        int mid=(l+r)/2;
        long long int a = MergeSort_CountInversions(arr, l, mid);
        long long int b = MergeSort_CountInversions(arr, mid+1, r);
        long long int c = MergeSort_CrossInversions(arr, l, mid, r);
        return a + b + c;
    }
    return 0;
}

long long int MergeSort_CrossInversions(long long int * arr, int l, int m, int r){
    long long int L[m-l+2], R[r-m+1];
    L[m-l+1] = 10000000000000001;
    R[r-m] = 10000000000000001;
    for(int i=0; i<m-l+1; ++i){
        L[i] = arr[l+i];
    }
    for(int i=0; i<r-m; ++i){
        R[i] = arr[m+1+i];
    }
    long long int rp=0, lp=0, count_inv=0;
    for(int i=l; i<=r; ++i){
        if(L[lp]>R[rp]){
            arr[i]=R[rp];
            rp++;
            if(lp!=m-l+1)
                count_inv += m-l+1-lp;
            //printf("%d\n",count_inv);
        }
        else if(L[lp]<R[rp]){
            arr[i]=L[lp];
            lp++;
        }
        else if(L[lp]==R[rp]){
            arr[i] = L[lp];
            lp++;
        }
    }
    return count_inv;
}