#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
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
const int MAXN = 2005;

int C[MAXN][MAXN], Sum[MAXN][MAXN],
	k;

inline void Calc(void)
{
	C[0][0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		C[i][0] = C[i][i] = 1;

		for (int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] +
				C[i - 1][j - 1]) % k;
	}

	for (int i = 0; i < MAXN - 1; ++i)
		for (int j = 0; j < MAXN - 1; ++j)
			Sum[i + 1][j + 1] =
				(j <= i && C[i][j] == 0) +
				Sum[i + 1][j] + Sum[i][j + 1] -
				Sum[i][j];
}

int main(void)
{
	freopen("problem.in", "r", stdin);
	freopen("problem.out", "w", stdout);

	int t;
	scanf("%d %d", &t, &k);

	Calc();

	while (t--) {
		int n, m;
		scanf("%d %d", &n, &m);

		printf("%d\n", Sum[n + 1][m + 1]);
	}

	return 0;
}