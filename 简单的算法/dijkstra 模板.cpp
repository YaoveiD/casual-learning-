#include <bits/stdc++.h>
using namespace std;
#define inf 100000000000000
const int maxn=20005;
int n,m;
long long ans;
int first[maxn];
long long dis[maxn];
bool vis[maxn];
struct node{
    int u,v,w,pre;
}G[3*maxn];
void add(int u,int v,int w,int idx){
    G[idx].u=u;
    G[idx].v=v;
    G[idx].w=w;
    G[idx].pre=first[u];
    first[u]=idx;
}
struct point{
    int i;
    long long s;
    bool operator < (const point &a ) const{
        return s>a.s;
    }
    point(int i,long long s):i(i),s(s){
    }
};
priority_queue <point> pq;
void Dijkstra(int s=1){
    for(int i=1;i<=n;i++) dis[i]=inf;
    dis[s]=0;
    pq.push(point(s,dis[s]));
    while(!pq.empty()){
        int tmp=pq.top().i;pq.pop();
        if(vis[tmp]) continue;
        vis[tmp]=true;
        for(int i=first[tmp];i;i=G[i].pre){
            if(dis[tmp]+G[i].w<=dis[G[i].v]&&!vis[G[i].v]){
                dis[G[i].v]=dis[tmp]+G[i].w;
                pq.push(point(G[i].v,dis[G[i].v]));
            }
        }
    }
}
void Init(){
    memset(vis,false,sizeof(vis));
    ans=0;
    memset(first,0,sizeof(first));
    memset(G,0,sizeof(G));
}
int main()
{
    int u,v,w;
    int T;cin>>T;
    while(T--){
        cin>>n>>m;
        Init();
        for(int i=1;i<=m;i++){
            cin>>u>>v>>w;
            add(u,v,w,i);
        }
        Dijkstra();
        for(int i=1;i<=n;i++){
            ans+=dis[i];
        }
        memset(first,0,sizeof(first));
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=m;i++){
            add(G[i].v,G[i].u,G[i].w,i);
        }
        Dijkstra();
        for(int i=1;i<=n;i++){
            ans+=dis[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}
