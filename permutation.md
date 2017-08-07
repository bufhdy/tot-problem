# permutation

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
const int MAXN = 3005,
	MOD = (int)(1e9) + 7;

long long Dynamic[MAXN][MAXN] = { 0 };

int main(void)
{
#ifndef LOCAL
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif // LOCAL

	Dynamic[2][1] = 1;
	for (int i = 2; i <= 3000; ++i)
		for (int j = 1; 2 * j <= i; ++j)
			if (Dynamic[i][j]) {
				Dynamic[i + 1][j + 1] =
					(Dynamic[i + 1][j + 1] + (Dynamic[i][j] * (i - 2 * j)) % MOD) % MOD;
				Dynamic[i + 1][j] =
					(Dynamic[i + 1][j] + (Dynamic[i][j] * 2 * j) % MOD) % MOD;
			}

	int Query;
	cin >> Query;

	while (Query--) {
		int n, k;
		cin >> n >> k;

		long long Sum = 0;
		for (int i = 0; i <= n - k; ++i)
			Sum = (Sum + Dynamic[n + 1][i]) % MOD;

		cout << Sum << endl;
 	}

	return 0;
}
```
