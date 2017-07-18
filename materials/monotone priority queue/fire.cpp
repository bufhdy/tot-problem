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
#include <deque>
#include <string>
#include <stack>
using namespace std;
const int MAXN = 100005;

int Dynamic[MAXN] = { 0 };

int main(void)
{
	int n, m, Cost[MAXN];
	cin >> n >> m;

	for (int i = 1; i <= n; ++i)
		cin >> Cost[i];

	deque<int> Monotone;
	for (int i = 1; i <= m; ++i) {
		Dynamic[i] = Cost[i];

		while (!Monotone.empty() &&
			Dynamic[Monotone.back()] >= Dynamic[i])
				Monotone.pop_back();
		Monotone.push_back(i);
		// make nothing bigger than Dynamic[i]
	}

	for (int i = m + 1; i <= n; ++i) {
        Dynamic[i] = Dynamic[Monotone.front()] + Cost[i];

        while (!Monotone.empty() &&
			Dynamic[Monotone.back()] >= Dynamic[i])
				Monotone.pop_back();
		Monotone.push_back(i);

		while (!Monotone.empty() &&
			Monotone.front() <= i - m)
			Monotone.pop_front();
		// get rid of anthing out of range
	}

	cout <<
		*min_element(Dynamic + n - m + 1,
			Dynamic + 1 + n) << endl;

	return 0;
}


/*

5 3
1 2 5 6 2

 */
