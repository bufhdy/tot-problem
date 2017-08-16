```c++
// learn about hash

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
using namespace std;
const int MAXN = 100005;

const int LgtHash = 1 << 26;
struct Container {
	int Head[LgtHash],
		Value[MAXN], Next[MAXN], Count[MAXN],
		Index;

	void operator += (int x)
	{
		int Position = x & (LgtHash - 1), i;
		for (i = Head[Position];
			i && Value[i] != x;
			i = Next[i]) ;

		if (i) ++Count[i];
		else {
			++Index;
			Value[Index] = x;
			Count[Index] = 1;
			Next[Index] = Head[Position];
			Head[Position] = Index;
		}
	}

	int operator [] (int x)
	{
		int Position = x & (LgtHash - 1), i;
		for (i = Head[Position];
			i && Value[i] != x;
			i = Next[i]) ;
		return Count[i];
	}

	Container(void) : Index(0) {
		memset(Count, 0, sizeof(Count));
	}
} Hash;

int w[MAXN], Index = 0;
void Initialise(void)
{
	for (int i = 1; i < 30; ++i)
		for (int j = 0; j < i; ++j)
			w[Index++] =
				(1 << i) | (1 << j);
}

int main(void)
{
	Initialise();

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		Hash += x;
	}

	long long Answer = 0;
	for (int i = 0; i < m; ++i) {
		int x;
		scanf("%d", &x);

		for (int j = 0; j < Index; ++j)
			Answer += Hash[x ^ w[j]];
	}

	cout << Answer << endl;

	return 0;
}
```

