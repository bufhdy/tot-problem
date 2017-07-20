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
const int MAXN = 100001;

int Array[MAXN];

int main(void)
{
#ifndef _DEBUG
	freopen("block.in", "r", stdin);
	freopen("block.out", "w", stdout);
#endif // !_DEBUG

	int n, Answer;
	cin >> n;

	for (int i = 1; i <= n; ++i)
		cin >> Array[i];

	Answer = Array[1];

	for (int i = 2; i <= n; ++i) {
		Answer += Array[i];
		Answer -= min(Array[i], Array[i - 1]);
	}

	cout << Answer << endl;

	return 0;
}