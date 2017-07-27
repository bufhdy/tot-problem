#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
using namespace std;
const int MAXN = 2005, MAXM = 2005;
int k, 
    C[MAXN][MAXN], Count[MAXN][MAXN];

int main(void)
{
#ifndef  _DEBUG
    freopen("problem.in", "r", stdin);
    freopen("problem.out", "w", stdout);
#endif // ! _DEBUG

    int Case;
    cin >> Case >> k;

    memset(C, 0, sizeof(C));
    C[0][0] = 1;

    for (int i = 1; i < MAXN; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] =
                (C[i - 1][j] + C[i - 1][j - 1]) % k;
    }

    memset(Count, 0, sizeof(Count));
    for (int i = 0; i < MAXN - 1; ++i)
        for (int j = 0; j < MAXM - 1; ++j) {
            if (j <= i && C[i][j] == 0) Count[i + 1][j + 1] = 1;
            Count[i + 1][j + 1] += 
                Count[i + 1][j] + 
                Count[i][j + 1] - 
                Count[i][j];
        }

    while (Case--) {
        int n, m;
        cin >> n >> m;
        ++n, ++m;
        cout << Count[n][m] << endl;;
    }

    return 0;
}