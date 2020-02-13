class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if not s: return ""

        n = len(s)
        unit = 2*numRows - 2 if numRows > 1 else 1
        
        ret = ""
        for start in range(min(n, numRows)):
            i = start
            step = unit - 2*start
            ret += s[i]
            while i + step < n:
                i += step
                step = unit - step
                if step != unit: ret += s[i]

        return ret


s = Solution()
print(s.convert("A", 1))