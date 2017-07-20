# block

In this problem, we're just going to look for a pattern, that is, from 2nd element if Build[i] is bigger than Build[i - 1], that means we should add extra delta of Build[i] - Build[i - 1] to current Work, just like:

![block_1](https://raw.githubusercontent.com/bufhdy/tot-problem/master/NOIP-2013/day-2/image/block_1.png)

If it's smaller, that's okay because the smaller part has been calculated already, and code:

```c++
#include <bits/stdc++.h>
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
```







