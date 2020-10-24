class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        ans, n = 0, len(s)
        r = -1
        rec = set()
        for i in range(n):
            if i > 0:
                rec.remove(s[i-1])
            while r+1 < n and s[r+1] not in rec:
                r += 1
                rec.add(s[r])
            ans = max(ans, r-i+1)
        return ans
s = Solution()
if __name__ == __main__:
    ans = s.lengthOfLongestSubstring('abcacadfseasadd')
    print(ans)
