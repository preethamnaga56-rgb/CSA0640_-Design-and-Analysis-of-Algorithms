#include <bits/stdc++.h>
using namespace std;
long long karatsuba(long long x,long long y){if(x<10||y<10)return x*y;int n=max(to_string(x).size(),to_string(y).size()),m=n/2;long long p=1;for(int i=0;i<m;i++)p*=10;long long a=x/p,b=x%p,c=y/p,d=y%p;long long z2=karatsuba(a,c),z0=karatsuba(b,d),z1=karatsuba(a+b,c+d)-z2-z0;return z2*p*p+z1*p+z0;}
int main(){long long x,y;cout<<"Enter two non-negative integers (keep product within signed 64-bit range): ";if(!(cin>>x>>y)||x<0||y<0)return 1;cout<<"Karatsuba product: "<<karatsuba(x,y)<<"\n";}
