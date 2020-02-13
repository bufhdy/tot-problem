class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n, m = len(s), len(p)

        dym = [[False] * (m + 1) for _ in range(n + 1)]
        dym[n][m] = True
        for i in range(n, -1, -1):
            for j in range(m - 1, -1, -1):
                fst_matched = i < n and p[j] in { s[i], '.' }
                
                if j < m-1 and p[j+1] == '*':
                    dym[i][j] = dym[i][j+2] or fst_matched and dym[i+1][j]
                else: dym[i][j] = fst_matched and dym[i+1][j+1]
        
        return dym[0][0]
                

    def isMatch_recr(self, s: str, p: str) -> bool:
        if not p: return not s
        
        fst_matched = bool(s) and p[0] in { s[0], '.' }

        if len(p) > 1 and p[1] == '*':
            return self.isMatch_recr(s, p[2:]) or fst_matched and self.isMatch_recr(s[1:], p)
        else: return fst_matched and self.isMatch_recr(s[1:], p[1:])


s = Solution()
print(s.isMatch("aa", "a*"))
