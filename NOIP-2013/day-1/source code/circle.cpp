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

int main(void)
{
#ifndef _DEBUG
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);
#endif // !_DEBUG

	int Amount, To, k, x;
	cin >> Amount >> To >> k >> x;

	long long Real = 1;

	for (int i = 0; i < k / 18; ++i)
		Real = Real * ((long long)1e18 % Amount) % Amount;

	Real = Real * ((long long)pow(10, (k % 18)) % Amount) % Amount;

	int Place = 0;
	for (int i = 0; i < Real; ++i)
		Place = (Place + Amount - To) % Amount;

	cout << (Place + x) % Amount;
	
	return 0;
}