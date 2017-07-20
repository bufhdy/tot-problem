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

int Build[MAXN];

int main(void)
{
	int n, Work;
	cin >> n;

	for (int i = 1; i <= n; ++i)
		cin >> Build[i];

	Work = Build[1];

	for (int i = 2; i <= n; ++i)
		if (Build[i] > Build[i - 1])
			Work += Build[i] - Build[i - 1];

	cout << Work << endl;

	return 0;
}