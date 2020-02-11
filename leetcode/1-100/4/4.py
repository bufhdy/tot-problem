class Solution:
    def median_i(self, N1, N2, lft, rgt):
        n, m = len(N1), len(N2)
        i = (lft + rgt) // 2
        j = (n + m) // 2 - i

        if (i == 0 or j == m or N1[i - 1] <= N2[j]) and (j == 0 or i == n or N2[j - 1] <= N1[i]):
            return i, j
        elif i > 0 and N1[i - 1] > N2[j]:
            return self.median_i(N1, N2, lft, i - 1)
        elif i < n and N2[j - 1] > N1[i]:
            return self.median_i(N1, N2, i + 1, rgt)


    def findMedianSortedArrays(self, N1: [int], N2: [int]) -> float:
        n, m = len(N1), len(N2)
        if n > m:
            n, m, N1, N2 = m, n, N2, N1

        i, j = self.median_i(N1, N2, 0, n)

        if i == n: min_rgt = N2[j]
        elif j == m: min_rgt = N1[i]
        else: min_rgt = min(N1[i], N2[j])

        if (n + m) % 2 == 1:
            return min_rgt

        if i == 0: max_lft = N2[j-1]
        elif j == 0: max_lft = N1[i-1]
        else: max_lft = max(N1[i - 1], N2[j - 1])

        return (max_lft + min_rgt) / 2


s = Solution()
print(s.findMedianSortedArrays([1, 3], [2]))