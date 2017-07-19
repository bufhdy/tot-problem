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

	long long Amount, To, k, x, Answer = 1, Temp = 10;
	cin >> Amount >> To >> k >> x;

	while (k) {
		if (k & 1)
			Answer = (Answer * Temp) % Amount;
		k >>= 1;
		Temp = ((Temp % Amount) * (Temp % Amount)) % Amount;
	}

	cout << (x + (To * Answer) % Amount) % Amount << endl;
	
	return 0;
}