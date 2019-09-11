#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <complex>
using namespace std;

long int power(long int n);

vector<complex<long double>> inv_fft(vector<complex<long double>> coeff, long int n);

vector<complex<long double>> fft(vector<complex<long double>> coeff, long int n);

long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

int main() {
    long int t;
    cin >> t;
    while(t--){
        long int n;
        long double p,q,r,s;
        cin >> n;
        vector<complex<long double>> a_coeff, b_coeff, a_val, b_val, c_val, c_coeff;
        long int n_new = power(2*n);
        for(long int i=0; i<n; ++i){
            cin >> p;
            cin >> q;
            a_coeff.push_back(complex<long double> (p, q));
        }
        for(long int i=0; i<n; ++i){
            cin >> r;
            cin >> s;
            b_coeff.push_back(complex<long double> (r, s));
        }
        for(long int i=n; i<n_new; ++i){
            a_coeff.push_back(complex<long double> (0,0));
            b_coeff.push_back(complex<long double> (0,0));
        }
        n=n_new;
        
        a_val = fft(a_coeff, a_coeff.size());
        b_val = fft(b_coeff, b_coeff.size());
        for(long int i=0; i<a_val.size(); ++i)
            c_val.push_back(a_val[i]*b_val[i]);
        
        c_coeff = inv_fft(c_val, c_val.size());
        for(long int i=0; i<n; ++i){
            if( (real(c_coeff[i])/n) < 0 && (real(c_coeff[i])/n) > -0.0005)
                c_coeff[i].real(0);
            if( (imag(c_coeff[i])/n) < 0 && (imag(c_coeff[i])/n) > -0.0005)
                c_coeff[i].imag(0);
            printf("(%.3llf,%.3llf)\n",(real(c_coeff[i])/n), (imag(c_coeff[i])/n));
        }
    }
    return 0;
}

vector<complex<long double>> fft(vector<complex<long double>> coeff, long int n){
    if(n==1)
        return coeff;
    vector<complex<long double>> e_coeff, o_coeff, e_val, o_val, val;
    for(long int i=0; i<n; ++i){
        if(i%2==0)
            e_coeff.push_back(coeff[i]);
        else
            o_coeff.push_back(coeff[i]);
    }
    e_val = fft(e_coeff, n/2);
    o_val = fft(o_coeff, n/2);
    for(long int i=0; i<n/2; ++i){
        complex<long double> w(cos((2*pi*i/n)),sin((2*pi*i/n)));
        val.push_back(e_val[i] + w*o_val[i]);
    }
    for(long int i=0; i<n/2; ++i){
        complex<long double> w(cos((2*pi*i/n)),sin((2*pi*i/n)));
        val.push_back(e_val[i] - w*o_val[i]);
    }
    return val;
}

vector<complex<long double>> inv_fft(vector<complex<long double>> coeff, long int n){
    if(n==1)
        return coeff;
    vector<complex<long double>> e_coeff, o_coeff, e_val, o_val, val;
    for(long int i=0; i<n; ++i){
        if(i%2==0)
            e_coeff.push_back(coeff[i]);
        else
            o_coeff.push_back(coeff[i]);
    }
    e_val = inv_fft(e_coeff, n/2);
    o_val = inv_fft(o_coeff, n/2);
    for(long int i=0; i<n/2; ++i){
        complex<long double> w(cos((2*pi*i/n)),sin((-2*pi*i/n)));
        val.push_back(e_val[i] + w*o_val[i]);
    }
    for(long int i=0; i<n/2; ++i){
        complex<long double> w(cos((2*pi*i/n)),sin((-2*pi*i/n)));
        val.push_back(e_val[i] - w*o_val[i]);
    }
    return val;
}

long int power(long int n){
    long int temp=1;
    while(temp<n){
        temp*=2;
    }
    return temp;
}