#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <stack>
using namespace std;
const int MAXN = 100005;

// O(n * m) algorithm

bool xBlock[MAXN] = { false }, yBlock[MAXN] = { false };

int main(void)
{
#ifndef LOCAL
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w", stdout);
#endif // LOCAL

	int n, m;
	cin >> n >> m;

	long long Left = n * n;
	while (m--) {
		int x, y;
		cin >> x >> y;
		int Count = 0;

		for (int i = 1; i <= n; ++i) {
			if (!xBlock[x] && !yBlock[i])
				++Count;
			if (!xBlock[i] && !yBlock[y])
				++Count;
		}

		if (!xBlock[x] && !yBlock[y]) --Count;

		Left -= Count;

		xBlock[x] = yBlock[y] = true;

		cout << Left << endl;
	}


	return 0;
}
