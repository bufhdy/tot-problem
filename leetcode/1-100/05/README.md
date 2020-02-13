# 5. Longest Palindromic Substring

[link](https://leetcode.com/problems/longest-palindromic-substring/)

## Solution

It helps me review the LCS (Longest Common Substring) algorithm, though the algorithm may not help me to solve the problem. Let's talk a little bit about LCS. To solve LCS, the first thing to acquire is Longest Common Suffix. 

`LCSf(i, j) = LCSf(i-1, j-1) + 1 if S[i] = T[j] else 0` is the rule of calculation. Now, if we try to solve LCS in the meantime, it goes similarly like `LCS(i, j) = LCS(i-1, j-1) + 1 if S[i] = T[j] else 0`. (We can say that LCSf is the special case of LCS, which means LCS(n, m) is the answer of LCSf.) Each time we've got LCS(i, j), it'll be compared with a maxinum, keeping up-to-dated, as well as its corresponding string. Code here:

```python
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
```

So how can we solve the problem? No one cannot solve it with brute force, but we're supposed to analyse what costs more time? We'd find every single substring and check whether it's palindromic and this is where time is stolen. We can cut the time using dynamic programming.

`dyn(i, j) = dyn(i+1, j-1) and S[i] == S[j] else False`. However, as we use some indices like `i+1`, we can't do it linearly but crossingly like the code: (Don't forget to initialise. )

```python
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

```

Well, it'll take $O(n^2)$ which is still a bit slow. Now it's time for Manacher's Algorithm. With this algorithm, the original string (like `abcbd`) will be expanded to something like `*a*b*c*b*d*`. Each character in the new string represents a axis of symmetry. And then we'll get new array `P` to record the radius of a palindromic substring. `i` of `P[i]` indicates the center index of a palindromic substring. Like:

```
L | * a * b * c * b * d *
P | 1 2 1 2 1 4 1 2 1 2 1
```

We're going to calculate linearly from the third place of `P`. (The first and the second one is fixed.) Considering:

```
--j--   --i--
------a------
```

`a` stands for the axis, `i` is the current place where we want to get `P[i]`, `j` is the refraction of `i`. When the substring of `j` lives in the range of substring of `a`, part of `P[i]` can inherited the value of `P[j]` (since it's symmetric), and anothor part is calculating by stretching out for the place outside the range of substring of `a`. When:

```
---j---  --i--
 ------a------
```

`j` is too big to live in the range, the former part of `P[i]` can only inherited the length of `j` **in the range**. The latter part is discovered with the same method mentioned above.

In the progress, the only two another variables we need to store are the `a` and the radius of `a`. Code here:

```python
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
```
It saves a lot of time.
