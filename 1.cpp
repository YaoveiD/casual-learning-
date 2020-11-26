#include <iostream>
#include <map>
using namespace std;
typedef long long ll;
const ll maxn = 105;
struct node{
	ll v;
	struct node* next;
};
typedef struct node arcnode;
typedef struct vnode{
	ll u;
	arcnode *firstarc;
}vnode, adjlist[maxn];
typedef struct{
	adjlist edges;
	ll vexnum, arcnum;
}algraph;
map<ll,ll> index;
void creat(algraph &G){
	cout << "n, m" << endl;
	cin >> G.vexnum >> G.arcnum;
	cout << "vex" << endl;
	for (ll i = 1; i <= G.vexnum; ++i) {
		cin >> G.edges[i].u;
		index[G.edges[i].u] = i;
		G.edges[i].firstarc = NULL;
	}
	ll u, v;
	for (ll i = 1; i <= G.arcnum; ++i) {
		cout << "u, v" << endl;
		cin >> u >> v;
		node* edge = new node;
		edge->v = v; edge->next = NULL;
		edge->next = G.edges[index[u]].firstarc;
		G.edges[index[u]].firstarc = edge;
	}
}
int main()
{
	algraph G;
	creat(G);
	for (ll i = 1; i <= G.vexnum; ++i) {
		cout << G.edges[i].u << ": ";
		for (node* node = G.edges[i].firstarc; node != NULL; node = node->next) {
			cout << node->v << " ";
		}
		cout << endl;
	}
	return 0;
}
