class Solution:
    def manacher(self, S):
        if S == "": return ""

        n = len(S)
        L = []
        for i in range(2 * n + 1):
            L.append('*' if i % 2 == 0 else S[i // 2])

        P = [1, 2]
        mx, id = 2, 1
        for i in range(2, 2 * n + 1):
            j = 2 * id - i
            if id + mx <= i: P.append(1)
            elif id - mx <= j - P[j]:
                P.append(P[j])
            else: P.append(j - id + mx)
            while i - P[i] >= 0 and i + P[i] < 2 * n + 1 and L[i - P[i]] == L[i + P[i]]:
                P[i] += 1
            if P[i] > mx: mx, id = P[i], i

        return ''.join(L)[id - mx + 1:id + mx].replace('*', '')

    def dynp(self, S):
        if S == "": return ""

        n = len(S)
        dyn = [[(i == j) for j in range(n)] for i in range(n)]

        ret, max_lgt = S[0], 1
        for k in range(1, n):
            for i in range(0, n - k):
                j = k + i
                s = S[i:j + 1]
                dyn[i][j] = (S[i] == S[j] and (j - i < 2 or dyn[i + 1][j - 1]))

                if dyn[i][j]:
                    if len(s) > max_lgt: ret, max_lgt = s, len(s)

        return ret

    def LCS(self, S, T):  # This method cannot be applied to this problem
        ret, max_lgt = "", 0
        dyn = [[0 for _ in range(len(T))] for _ in range(len(S))]

        for i in range(len(S)):
            for j in range(len(T)):
                if i == 0 or j == 0:
                    dyn[i][j] = int(S[i] == T[j])
                else:
                    if S[i] == T[j]: dyn[i][j] = dyn[i - 1][j - 1] + 1

                if dyn[i][j] > max_lgt:
                    ret, max_lgt = S[i - max_lgt + 1:i + 1], dyn[i][j]

        return ret

    def longestPalindrome(self, s: str) -> str:
        return self.manacher(s)


s = Solution()
print(s.longestPalindrome("12212321"))
