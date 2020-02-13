# 10. Regular Expression Matching

[link](https://leetcode.com/problems/regular-expression-matching/)

## Solution

Last day I had just watched [a lecture](https://missing.csail.mit.edu/2020/data-wrangling/) from MIT talking about Regular Expression. You may want to visit [this tutorial for regex](https://regexone.com). Okay, back to the topic.

The only hard part of dealing with this problem is annoying Kleene star (`*`), which is also greedy; it wants to eat as many lettres as rules allow. Anyway, we can deal with it recursively by just dividing it into 2 cases:

1. Eat the current lettre and pass the others with the same `*` rule (`is_first_lettre_matched and is_matched(s[1:], p)`);
2. Or, leave the current lettre alone and erase the `*` rule by skipping 2 patterns (`_*`), (`is_matched(s, p[2:])`)

Code:

```python
def isMatch_recr(self, s: str, p: str) -> bool:
    if not p: return not s
    
    fst_matched = bool(s) and p[0] in { s[0], '.' }

    if len(p) > 1 and p[1] == '*':
        return self.isMatch_recr(s, p[2:]) or fst_matched and self.isMatch_recr(s[1:], p)
    else: return fst_matched and self.isMatch_recr(s[1:], p[1:])
```

As you may notice, we've done some repeated jobs for `is_matched()` calulation. So we can translate the code into a dynamic programming version. `dyn[i][j]` means we're dealing with i-th lettre in `s` and j-th pattern. Empty string and patterns should be matched (`dyn[n][m] = True`). All we need to do is to translate.

```python
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
```

And [44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/) is similar.
