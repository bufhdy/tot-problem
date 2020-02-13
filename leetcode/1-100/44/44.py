class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n, m = len(s), len(p)

        dym = [[False] * (m + 1) for _ in range(n + 1)]
        dym[n][m] = True
        for i in range(n, -1, -1):
            for j in range(m - 1, -1, -1):
                if p[j] == '*': dym[i][j] = dym[i][j+1] or i < n and dym[i+1][j]
                else: dym[i][j] = i < n and p[j] in { s[i], '?' } and dym[i+1][j+1]
        
        return dym[0][0]

s = Solution()
print(s.isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b"))