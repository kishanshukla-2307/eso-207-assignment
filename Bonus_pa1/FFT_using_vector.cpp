#include <cmath>
#include<bits/stdc++.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<complex>
#define pi 3.14159265358979323846264338327950288
using namespace std;

int power(int n){
    int temp = 1;
    while(temp<n){
        temp*=2;
    }
    return temp;
}

vector< complex<double> > fft(vector< complex<double> >& coeff, int n){
    if(n==1)
        return coeff;
    vector< complex<double> > e_coeff, o_coeff, e_val, o_val, val;
    for (int i = 0; i < n; ++i){
        if(i%2==0){
            e_coeff.push_back(coeff[i]);
        }
        else{
            o_coeff.push_back(coeff[i]);
        }
    }
    e_val = fft(e_coeff, n/2);
    o_val = fft(o_coeff, n/2);
    for (int i = 0; i < n/2; ++i){
        complex<double> wi(cos(2*M_PI*i/n),sin(2*M_PI*i/n));
        val.push_back(e_val[i] + wi*o_val[i]);
    }
    for (int i = 0; i < n/2; ++i){
        complex<double> wi(cos(2*M_PI*i/n),sin(2*M_PI*i/n));
        val.push_back(e_val[i] - wi*o_val[i]);
    }
    return val;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int n,temp;
        double a,b;
        scanf("%d",&n);
        vector< complex<double> > coeff;
        for (int i = 0; i < n; ++i){
            cin >> a;
            cin >> b;
            complex<double> temp(a,b);
            coeff.push_back(temp);
        }
        int n_new = power(n);
        for(int i=n; i<n_new; ++i){
            complex<double> temp2(0,0);
            coeff.push_back(temp2);
        }
        n = n_new;
        vector< complex<double> > dft;
        dft = fft(coeff, n);
        for (int i = 0; i < n; ++i){
            if( real(dft[i]) < 0.0004 && real(dft[i]) > -0.0004)
                dft[i].real(0);
            if( imag(dft[i]) < 0.0004 && imag(dft[i]) > -0.0004)
                dft[i].imag(0);
            cout<<fixed;
            cout<<"("<<setprecision(3)<<real(dft[i])<<","<<imag(dft[i])<<")"<<"\n";
        }
    }
    return 0;
}