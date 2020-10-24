#bfs review 你好
maze = []
path = []
d = [(1,0),(-1,0),(0,1),(0,-1)]
def check(move):
	return (move[0] >= 0 and move[0] < m) and (move[1] >= 0 and move[1] < n) 
def bfs(s,e,maze):
	ee = 0
	print(s)
	path.append(s)
	maze[s[0]][s[1]] = 1
	while len(path) > 0:
		s=path.pop(0)
		print(s)
		if s[0:2] == e[0:2]:
			print(s[2])
		for each in d:
			new=(s[0]+each[0],s[1]+each[1],s[2]+1)
			if check(new):
				if maze[new[0]][new[1]] == 0:
					print('insert',new)
					ee += 1
					path.append(new)
					maze[new[0]][new[1]] = 1
m,n = map(int,input().split())
for i in range (m):
	maze.append(list(map(int,input().split())))
bfs((0,0,0),(2,0,0),maze)
