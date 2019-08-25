#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int SearchFirstElement(long long int *, int, int);

void BinarySearch(long long int *arr, int l, int r, int tar);

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        long long int arr[n],k;
        for(int i=0; i<n; ++i){
            scanf("%lld",&arr[i]);
        }
        scanf("%lld",&k);
        int i=SearchFirstElement(arr, 0, n-1);
        // printf("%d\n",i);
        if(k <= arr[n-1])
            BinarySearch(arr, i, n-1, k);
        else
            BinarySearch(arr, 0, i-1, k);
    }
    return 0;
}

void BinarySearch(long long int *arr, int l, int r, int tar){
    if(l<=r){
        int mid = (l+r)/2;
        if( tar < arr[mid] ){
            BinarySearch(arr, l, mid-1, tar);
        }
        else if( tar > arr[mid ]){
            BinarySearch(arr, mid+1, r, tar);
        }
        else if (tar==arr[mid])
            printf("%d\n",mid);
    }
    else
        printf("-1\n");
}

int SearchFirstElement(long long int *arr, int l, int r){
    if(l < r){
        int m = (l+r)/2;
        if(arr[l] < arr[r])
            return l;
        else if (arr[l] < arr[m])
            return SearchFirstElement(arr, m+1, r);
        else
            return SearchFirstElement(arr, l+1, m);
    }
    else 
        return l;
}