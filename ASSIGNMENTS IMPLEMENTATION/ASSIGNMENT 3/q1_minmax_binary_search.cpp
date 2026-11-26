#include <bits/stdc++.h>
using namespace std;
pair<int,int> minmaxDC(const vector<int>&a,int l,int r){
 if(l==r)return {a[l],a[l]};if(r==l+1)return {min(a[l],a[r]),max(a[l],a[r])};
 int m=l+(r-l)/2;auto x=minmaxDC(a,l,m),y=minmaxDC(a,m+1,r);return {min(x.first,y.first),max(x.second,y.second)};
}
int main(){int n;cout<<"Array size: ";if(!(cin>>n)||n<=0)return 1;vector<int>a(n);for(int&x:a)cin>>x;auto [mn,mx]=minmaxDC(a,0,n-1);cout<<"Minimum: "<<mn<<"\nMaximum: "<<mx<<"\nSorted array required for binary search? Enter sorted array size and values: ";int m;if(!(cin>>m)||m<0)return 1;vector<int>b(m);for(int&x:b)cin>>x;int t;cout<<"Target: ";cin>>t;int l=0,r=m-1,ans=-1;while(l<=r){int mid=l+(r-l)/2;if(b[mid]==t){ans=mid;break;}if(b[mid]<t)l=mid+1;else r=mid-1;}cout<<(ans<0?"NOT_FOUND":"Found at index "+to_string(ans))<<"\n";}
