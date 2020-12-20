#include <iostream>
#include <queue>
using namespace std;
#define INF 0x3f3f3f3f
typedef pair<int, double> iPair;
const int maxn = 1005;
/**
 * Data structure to store Adjacency list nodes
 */
struct Node {
	int to;
	double cost;
	Node* next;
};

// Data structure to store graph edges
struct Edge{
	int src, dest;
	double weight;
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
Node* getNode(int to, double weight, Node *head){
	Node* node = new Node;
	node->to = to;
	node->cost = weight;
	node->next = head;
	return node;
}

//add an edge into the graph
void add(Graph &G, int src, int dest, double weight){
	Node* node = getNode(dest, weight, G.head[src]);
	G.head[src] = node;
	node = getNode(src, weight, G.head[dest]);
	G.head[dest] = node;
	G.m += 2;
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

// Prints shortest paths from src to all other vertices
void primMST(const Graph &G){
	// To keep track of vertices included in MST
	int vis[maxn];
	// To store parent array which in turn store MST
	int parent[maxn];
	// Create a vector for keys and initialize all 
	// keys as infinite (INF)
	int key[maxn];
	int src = 0;// source
	double totalcost = 0;
	//initialize
	for (int i = 0; i < G.n; ++i) {
		vis[i] = 0;
		parent[i] = -1;
		key[i] = INF;
	}
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
	pq.push(make_pair(0, src));
	key[src] = 0;
	while (!pq.empty()) {
		int from = pq.top().second;
		totalcost += pq.top().first;
		pq.pop();
		vis[from] = 1;
		for (Node *p = G.head[from]; p; p = p->next) {
			int to = p->to;
			double cost = p->cost;
			if (!vis[to] && key[to] > cost) {
				key[to] = cost;
				pq.push(make_pair(cost, to));
				parent[to] = from;
			}
		}
	}
	cout << "totalcost = " << totalcost << endl;
	for (int i = 1; i < G.n; ++i) {
		cout << parent[i] << " - " << i << endl;
	}
}

int main(int argc, char const *argv[])
{
	int n, m, u, v;
	double w;
	cin >> n >> m;// nodes and edges
	Graph G(n);
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		add(G, u, v, w);
	}
	primMST(G);
	return 0;
}