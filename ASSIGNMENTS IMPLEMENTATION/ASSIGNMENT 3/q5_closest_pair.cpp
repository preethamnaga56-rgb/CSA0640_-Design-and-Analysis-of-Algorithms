#include <bits/stdc++.h>
using namespace std;struct P{double x,y;};double dist(P a,P b){return hypot(a.x-b.x,a.y-b.y);}
double brute(vector<P>&p,int l,int r){double d=DBL_MAX;for(int i=l;i<=r;i++)for(int j=i+1;j<=r;j++)d=min(d,dist(p[i],p[j]));return d;}
double solve(vector<P>&p,int l,int r){if(r-l<=3)return brute(p,l,r);int m=(l+r)/2;double midx=p[m].x,d=min(solve(p,l,m),solve(p,m+1,r));vector<P>s;for(int i=l;i<=r;i++)if(abs(p[i].x-midx)<d)s.push_back(p[i]);sort(s.begin(),s.end(),[](P a,P b){return a.y<b.y;});for(int i=0;i<(int)s.size();i++)for(int j=i+1;j<(int)s.size()&&s[j].y-s[i].y<d;j++)d=min(d,dist(s[i],s[j]));return d;}
int main(){int n;cout<<"Number of points (>=2): ";if(!(cin>>n)||n<2)return 1;vector<P>p(n);for(auto&x:p)cin>>x.x>>x.y;sort(p.begin(),p.end(),[](P a,P b){return a.x<b.x;});cout<<fixed<<setprecision(6)<<"Closest distance: "<<solve(p,0,n-1)<<"\n";}
