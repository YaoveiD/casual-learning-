'''
n, m = map(int, input().split())
graph = [ set() for _ in range(n + 1) ]

for i in range(m):
	u, v = map(int, input().split())
	graph[u].append(v)
	graph[v].append(u)
'''
from collections import deque
graph = {
	'A': ['B', 'C'],
	'B': ['A', 'C', 'D'],
	'C': ['A', 'B', 'D', 'E'],
	'D': ['B', 'C', 'E', 'F'],
	'E': ['C', 'D'],
	'F': ['D']
}

def BFS(graph, src):
	ret = []
	queue = deque()
	queue.append(src)
	vis = set()
	vis.add(src)
	while queue:
		u = queue.popleft()
		nodes = graph[u]
		for v in nodes:
			if v not in vis:
				queue.append(v)
				vis.add(v)
		ret.append(u)
	return ret

print('BFS:', BFS(graph, 'A'))

def DFS(graph, src):
	ret = []
	stack = deque()
	stack.append(src)
	vis = set()
	vis.add(src)
	while stack:
		u = stack.pop()
		nodes = graph[u]
		for v in nodes:
			if v not in vis:
				stack.append(v)
				vis.add(v)
		ret.append(u)
	return ret

seen = set()
def dfs(graph, src):
	print(src)
	seen.add(src)
	for dest in graph[src]:
		if dest not in seen:
			dfs(graph, dest)

dfs(graph, 'A')
print('DFS:', DFS(graph, 'A'))