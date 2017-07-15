#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <string>
using namespace std;

const int MAXN = 140;

int main(void)
{
	int Distance, Amount, Map[MAXN][MAXN] = { { 0 } };
	cin >> Distance >> Amount;

	int xMax = INT_MIN, xMin = INT_MAX, yMax = INT_MIN, yMin = INT_MAX;
	for (int i = 0; i < Amount; ++i) {
		int x, y;
		cin >> x >> y;

		if (x > xMax)
			xMax = x;
		if (x < xMin)
			xMin = x;

		if (y > yMax)
			yMax = y;
		if (y < yMin)
			yMin = y;

		cin >> Map[x][y];
	}

	multiset<int> MaxCount;
	MaxCount.insert(INT_MIN);

	for (int i = 0; i <= 128; ++i)
		for (int j = 0; j <= 128; ++j) {
			int Count = 0;

			for (int k = i - Distance; k <= i + Distance; ++k)
				for (int l = j - Distance; l <= j + Distance; ++l) {
					if (k < 0 || k > 128 || l < 0 || l > 128) continue;
					Count += Map[k][l];
				}

			MaxCount.insert(Count);
		}

	multiset<int>::iterator it = MaxCount.end();
	--it;

	cout << MaxCount.count(*it) << ' ' <<
		*it << endl;

	return 0;
}
