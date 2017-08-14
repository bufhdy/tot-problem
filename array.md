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
#include <functional>
using namespace std;
const int MAXN = 1005,
	MOD = (int)1e9 + 7;

priority_queue<int, vector<int>, greater<int> > Array;

int main(void)
{
	int n, k, x;
	scanf("%d %d %d", &n, &k, &x);

	bool IsNegative = false;
	for (int i = 1; i <= n; ++i) {
		int Temp;
		scanf("%d", &Temp);

		if (Temp < 0) IsNegative = !IsNegative;
		
		Array.push(abs(Temp));
	}

	while (k--) {
		int Min = Array.top();
		Array.pop();

		if (IsNegative)
			Min += x;
		else Min -= x;

		if (Min < 0) {
			IsNegative = !IsNegative;
			Min = abs(Min);
		}


		Array.push(Min);
	}

	long long Sum = 1;
	while (!Array.empty()) {
		Sum = Sum * (long long)Array.top() % MOD;
		Array.pop();
	}

	if (IsNegative) Sum = -Sum;

	printf("%d\n", (Sum + MOD) % MOD);
	
	return 0;
}
```

