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
#include <ctime>
using namespace std;
const int MAXN = 1005,
	MOD = 10007;

struct Main {
	/*
	
		(ax + by)^k
	
	 */
	
	long long a, b;
	int k, n, m, C[MAXN][MAXN];
	void CalculateC(int x)
	{
		for (int i = 0; i <= x; ++i) {
			C[i][0] = 1;
			for (int j = 1; j <= i; ++j)
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j] %
					MOD;
		}
	}

	Main(void) : C()
	{
		scanf("%lld %lld %d %d %d",
			&a, &b, &k, &n, &m);

		CalculateC(k);

		long long Answer = C[k][n];

		for (int i = 1; i <= n; ++i)
			Answer = Answer * a % MOD;
		for (int i = 1; i <= m; ++i)
			Answer = Answer * b % MOD;

		printf("%lld\n", Answer);
	}
};

int main(void)
{
	delete new Main();

	return 0;
}