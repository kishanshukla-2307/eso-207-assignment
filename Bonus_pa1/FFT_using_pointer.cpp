#include<cmath>
#include<bits/stdc++.h>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
#include<complex>
#define pi 3.141592653589793238462
using namespace std;

int power(int n){
    int temp=1;
    while(temp<n){
        temp*=2;
    }
    return temp;
}

double ** fft(double ** coeff, int n, int c){
    if(n==1)
        return coeff;
    double ** e_coeff = (double **)malloc((n/2)*sizeof(double*));
    double ** o_coeff = (double **)malloc((n/2)*sizeof(double*));
    double ** val = (double **)malloc((n)*sizeof(double*));
    for(int i=0; i<n/2; ++i){
        e_coeff[i] = (double *)malloc(2*sizeof(double));
        o_coeff[i] = (double *)malloc(2*sizeof(double));
    }
    for(int i=0; i<n; ++i){
        val[i] = (double *)malloc(2*sizeof(double));
    }
    for(int i=0; i<n; ++i){
        if(i%2==0){
            e_coeff[i/2][0] = coeff[i][0];
            e_coeff[i/2][1] = coeff[i][1];
        }
        else{
            o_coeff[i/2][0] = coeff[i][0];
            o_coeff[i/2][1] = coeff[i][1];
        }
    }
    double ** e_val = fft(e_coeff, n/2, 2);
    double ** o_val = fft(o_coeff, n/2, 2);
    for(int i=0; i<n/2; i++){
        double w_real = cos(2*M_PI*i/n);
        double w_imag = sin(2*M_PI*i/n);
        val[i][0] = e_val[i][0] + w_real*o_val[i][0] - w_imag*o_val[i][1] ;
        val[i][1] = e_val[i][1] + w_imag*o_val[i][0] + w_real*o_val[i][1] ;
        val[i+n/2][0] = e_val[i][0] - w_real*o_val[i][0] + w_imag*o_val[i][1];
        val[i+n/2][1] = e_val[i][1] - w_imag*o_val[i][0] - w_real*o_val[i][1];
    }
    return val;
    
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n, n_new;
        cin >> n;
        n_new = power(n);
        double ** coeff = (double **)malloc(n_new*sizeof(double*));
        for(int i=0; i<n_new; ++i){
            coeff[i] = (double *)malloc(2*sizeof(double));
        }
        for(int i=0; i<n; ++i){
            cin >> coeff[i][0];
            cin >> coeff[i][1];
        }
        for(int i=n; i<n_new; ++i){
            coeff[i][0]=0;
            coeff[i][1]=0;
        }
        double ** dft = fft(coeff, n_new, 2);
        for(int i=0; i<n_new; ++i){
            cout<<fixed;
            cout<<"("<<setprecision(3)<<dft[i][0]<<","<<setprecision(3)<<dft[i][1]<<")"<<"\n";
        }
    }
    return 0;
}