# club

Storage of a circle needs to be augmented like:

![store-a-circle](https://raw.githubusercontent.com/bufhdy/tot-problem/master/image/store-a-circle.png)

`bool Dynamic[i][j]` means if `i` or `j` can defeat every single people between `i + 1` and `j - 1`, specially, we set each `Dynamic[i][i + 1]` to `true`. Code:

```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 85; // for a circle, double it

bool Dynamic[MAXN][MAXN] = { false };
int Array[MAXN][MAXN];

int main(void)
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			cin >> Array[i][j];

			Array[i][j + n] =
				Array[i + n][j] =
				Array[i + n][j + n] =
				Array[i][j];
			// copy to draw a larger graph for a circle
		}

	for (int i = 1; i <= 2 * n; ++i)
		Dynamic[i][i + 1] = true; // initialisition

	for (int i = 2 * (n - 1); i >= 1; --i)
		for (int j = i + 2; j <= 2 * n; ++j)
			// guarantee the used has been calculated
			for (int k = i + 1; k < j; ++k) // a connection
				if ((Array[i][k] == 1 || Array[j][k] == 1) && // i or j
					Dynamic[i][k] && Dynamic[k][j]) { // left all
					Dynamic[i][j] = true;
					break;
				}

	for (int i = 1; i <= n; ++i)
		if (Dynamic[i][i + n])
			puts("1");
		else puts("0");

	return 0;
}
```

Also, the space can be optimised by an adequate MOD operation.

