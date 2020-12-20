#include <iostream>
#include <map>
using namespace std;
/**
 * 链表实现
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
		if (!index.count(u) || !index.count(v)) {
			cout << "no such vexs" << endl;
			--i;
			continue;
		}
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
 */

// another version
#include <iostream>
using namespace std;
const int maxn = 1005;
// Data structure to store Adjacency list nodes
struct Node {
	int to, cost;
	Node* next;
};

// Data structure to store graph edges
struct Edge{
	int src, dest, weight;
};

struct Graph{
	int n, m; //n->numbers of nodes, m->edges
	Node **head;
	Graph(int n = 0): n(n), m(0){
		head = new Node*[n + 1];
		for (int i = 0; i < n + 1; ++i) {
			head[i] = nullptr;
		}
	}

	~Graph(){
		for (int i = 0; i < m; ++i) {
			delete[] head[i];	
		}
		delete[] head;
	}
};

// Function to allocate new node of Adjacency List
Node* getNode(int to, int weight, Node *head){
	Node* node = new Node;
	node->to = to;
	node->cost = weight;
	node->next = head;
	return node;
}

//add an edge into the graph
void add(Graph &G, int src, int dest, int weight){
	Node* node = getNode(dest, weight, G.head[src]);
	G.head[src] = node;
	++G.m;
}

// print all neighboring vertices of given vertex
void printList(Node* ptr, int i){
    while (ptr != nullptr) {
        cout << "(" << i << ", " << ptr->to
            << ", " << ptr->cost << ") ";
        ptr = ptr->next;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
	int n, m, u, v, w;
	cin >> n >> m;// nodes and edges
	Graph G(n);
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		add(G, u, v, w);
	}
	for (int i = 0; i < n; ++i) {
		printList(G.head[i], i);
	}
	return 0;
}