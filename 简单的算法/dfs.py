#8 queens
'''
class Solution1:
    def totalNQueens(self, n: int) -> int:
        res = 0
        col = set()
        diag1 = set()
        diag2 = set()
        def dfs(row: int):
            nonlocal res
            if row == n:
                res += 1
                return
            else:
                for i in range(n):
                    if i not in col and i+row not in diag1 and i-row not in diag2:
                        col.add(i)
                        diag1.add(i+row)
                        diag2.add(i-row)
                        dfs(row + 1)
                        col.remove(i)
                        diag1.remove(i+row)
                        diag2.remove(i-row)
        dfs(0)
        return res
'''
cnt = 0
ans = []
vis = [[]for i in range(2)]
def dfs(step):
	if step == 8:
		global cnt
		cnt += 1
		print(ans)
		return
	else:
		for i in range(1,9):
			if i in ans:
				continue
			if (step-i+8 in vis[0]) or (step+i in vis[1]):
				continue
			ans.append(i)
			vis[1].append(step+i)
			vis[0].append(step-i+8)
			dfs(step+1)
			ans.pop()
			vis[1].pop()
			vis[0].pop()
if __name__ == '__main__':
	dfs(0)
	print ("cnt =",cnt)