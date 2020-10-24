#include <bits/stdc++.h>
using namespace std;

const int maxn=1e3+5;
int fa[maxn],Rank[maxn];
int m,n;
void init(int n){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        Rank[i]=1;
    }
}
int getfa(int x){
    return x==fa[x]?x:(fa[x]=getfa(fa[x]));
}
void Union(int x,int y){
    int fx=getfa(x),fy=getfa(y);
    if(fx==fy) return;
    if(Rank[fx]<=Rank[fy]) fa[fx]=fy;
    else fa[fy]=fx;
    if(Rank[fx]==Rank[fy]) Rank[fy]++;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int x,y;
    cin>>n>>m;
    init(n);
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        Union(x,y);
    }
    for(int i=1;i<=n;i++){
        cout<<fa[i]<<endl;
    }
    return 0;
}
