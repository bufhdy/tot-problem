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

int Height[MAXN];

int main(void)
{
#ifndef _DEBUG
	freopen("flower.in", "r", stdin);
	freopen("flower.out", "w", stdout);
#endif // !_DEBUG

	int n, Status = 1;
	cin >> n;

	for (int i = 1; i <= n; ++i)
		cin >> Height[i];

	int Count = 1;
	for (int i = 2; i <= n; ++i) {
		if (Height[i] > Height[i - 1])
			if (Status != 2) {
				++Count;
				Status = 2;
			}
		if (Height[i] < Height[i - 1])
			if (Status != 3) {
				++Count;
				Status = 3;
			}
	}

	cout << Count << endl;

	return 0;
}