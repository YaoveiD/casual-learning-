#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;

int fa[maxn],last[maxn],e;
struct graph {
    int u,v,w,pre;
    //graph(int x,int y,int z,int d):u(x),v(y),w(z),pre(d){}
}G[3*maxn];
void addage(int u,int v,int w){
    G[++e].u=u;
    G[e].v=v;
    G[e].w=w;
    G[e].pre=last[u];
    last[u]=e;
}
int cmp(graph x,graph y){
    return x.w<y.w;
}
int getfa(int x){
    return x==fa[x]?x:fa[x]=getfa(fa[x]);
}
void Union(int x,int y){
    int fx=getfa(x),fy=getfa(y);
    if(x!=y) fa[fx]=fy;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m,n,u,v,w;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        addage(u,v,w);
    }
    sort(G+1,G+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int totcost=0;
    //kruskal
    for(int i=1;i<=n-1;i++){
        if(getfa(G[i].u)!=getfa(G[i].v)){
            Union(G[i].u,G[i].v);
            totcost+=G[i].w;
            cout<<"add "<<G[i].u<<" to "<<G[i].v<<endl;
        }
    }
    cout<<totcost<<endl;
    return 0;
}
