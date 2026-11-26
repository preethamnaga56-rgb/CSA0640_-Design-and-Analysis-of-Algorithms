#include <bits/stdc++.h>
using namespace std;long long qcomps=0;int maxDepth=0;
void mergeSort(vector<int>&a,int l,int r){if(l>=r)return;int m=l+(r-l)/2;mergeSort(a,l,m);mergeSort(a,m+1,r);vector<int>tmp;int i=l,j=m+1;while(i<=m&&j<=r){if(a[i]<=a[j])tmp.push_back(a[i++]);else tmp.push_back(a[j++]);}while(i<=m)tmp.push_back(a[i++]);while(j<=r)tmp.push_back(a[j++]);copy(tmp.begin(),tmp.end(),a.begin()+l);}
int part(vector<int>&a,int l,int r){int pivot=a[r],i=l-1;for(int j=l;j<r;j++){qcomps++;if(a[j]<=pivot)swap(a[++i],a[j]);}swap(a[i+1],a[r]);return i+1;}
void quick(vector<int>&a,int l,int r,int depth=1){maxDepth=max(maxDepth,depth);if(l<r){int p=part(a,l,r);quick(a,l,p-1,depth+1);quick(a,p+1,r,depth+1);}}
int main(){int n;cout<<"Number of elements: ";if(!(cin>>n)||n<0)return 1;vector<int>a(n);for(int&x:a)cin>>x;auto b=a;mergeSort(a,0,n-1);quick(b,0,n-1);cout<<"Merge sort: ";for(int x:a)cout<<x<<" ";cout<<"\nQuick sort: ";for(int x:b)cout<<x<<" ";cout<<"\nQuick-sort partition comparisons: "<<qcomps<<"\nMaximum recursion depth: "<<maxDepth<<"\n";}
