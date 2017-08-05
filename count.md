# count

```c++
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
const int MAXN = 25,
	MAXB = 2097155,
	MOD = 1e9 + 7;

int LowBit(int x)
{
	return x & -x;
}

int CntBinary[MAXB],
	False[MAXN],
	FalseCntBinary[MAXB][MAXN],
	/*
		FalseCntBinary[i][j] is
			the false count inserting j
			in the situation of i (known as a binary)
	*/
	Dynamic[MAXB][MAXN];
	/*
		Dynamic[i][j] means
			in the situation of i (binary)
			j has been mistaken
	 */

int main(void)
{
#ifndef LOCAL
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif // LOCAL

	int n, m, k;
	cin >> n >> m >> k;

	int Limit = (1 << n) - 1;

	while (m--) {
		int u, v;
		cin >> u >> v;

		False[u] += (1 << (v - 1));
		// False means u can't be with which
		// like 01010
	}

	for (int i = 1; i <= Limit; ++i)
		CntBinary[i] =
			CntBinary[i - LowBit(i)] + 1;

	for (int s = 0; s <= Limit; ++s) // from 0000 to 1111
		for (int x = 1; x <= n; ++x)
			if ((s & (1 << (x - 1))) == 0)
				FalseCntBinary[s][x] =
					CntBinary[False[x] & s];
						// to insert and
						// to meet the false situation

	Dynamic[0][0] = 1; // set the original situation

	for (int s = 0; s <= Limit; ++s)
		for (int i = 0; i <= k; ++i)
			if (Dynamic[s][i])
				for (int x = 1; x <= n; ++x)
					if ((s & (1 << (x - 1))) == 0)
						if (i + FalseCntBinary[s][x] <= k)
							Dynamic[s | (1 << (x - 1))]
								[i + FalseCntBinary[s][x]] =
									(Dynamic[s | (1 << (x - 1))]
										[i + FalseCntBinary[s][x]] +
											Dynamic[s][i]) % MOD;

	int Count = 0;
	for (int i = 0; i <= k; ++i)
		Count = (Count + Dynamic[Limit][i]) % MOD;

	cout << Count << endl;

	return 0;
}
```