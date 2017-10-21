```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
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
const int MAXN = 1e5 + 5;

struct Brute_1 {
	int n;

	struct Unit {
		int x, y, Min, Idx;

		void GetMin(void)
		{
			Min = min(x, y);
			if (Min < 1)
				Min = INT_MAX;
		}

		bool operator < (const Unit & a) const
		{
			return Min < a.Min;
		}
	} Pairs[MAXN];

	Brute_1(void)
	{
		int Array[2];
		scanf("%d %d", &n, &Array[0]);

		for (int i = 1; i <= n - 1; ++i) {
			scanf("%d", &Array[i % 2]);

			Pairs[i] = { Array[(i - 1) % 2], Array[i % 2] };
			Pairs[i].GetMin();

			Pairs[i].Idx = i;
		}

		int Cnt= 0;
		while (true) {
			Unit &Crt = *min_element(Pairs + 1, Pairs + n);
			if (Crt.Min != INT_MAX) {
				int i = Crt.Idx;

				--Pairs[i].x;
				--Pairs[i].y;
				Pairs[i].GetMin();

				if (i - 1 >= 1) {
					--Pairs[i - 1].y;
					Pairs[i - 1].GetMin();
				}
				if (i + 1 <= n - 1) {
					--Pairs[i + 1].x;
					Pairs[i + 1].GetMin();
				}

				++Cnt;
			} else break;
		}

		printf("%d\n", Cnt);
	}
};

struct Main {
	int n, Array[MAXN], SumB[MAXN],
		f[MAXN][2], Ans, Suffix[MAXN], Tmp[MAXN][2];
	// 表示第 i 个数的当前值为 j，它的上一个值是否为 0 的情况的答案。
    // f[][]

	Main(void) : SumB(), Ans(INT_MAX)
	{
		scanf("%d", &n);

		int Max = INT_MIN;
        for (int i = 1; i <= n; ++i) {
			scanf("%d", Array + i);

			if (Array[i] > Max)
				Max = Array[i];
		}

		for (int i = 0; i <= Max; ++i)
			f[i][0] = f[i][1] = Suffix[i] = 0x3f3f3f3f;

		f[0][0] = Suffix[0] = 0;

		for (int i = 1; i <= n; ++i) {
            for (int j = Array[i - 1] + 1; j <= Array[i]; ++j)
				f[j][0] = f[j][1] = Suffix[j] = 0x3f3f3f3f;

			for (int j = Array[i]; j >= 0; --j)
				Tmp[j][0] = Tmp[j][1] = 0x3f3f3f3f;

            for (int j = Array[i]; j >= 0; --j) {
				if (Suffix[Array[i] - j] + Array[i] - j < Tmp[j][0])
					Tmp[j][0] = Suffix[Array[i] - j] + Array[i] - j;

                if (f[Array[i] - j][0] + Array[i] - j < Tmp[j][0])
					Tmp[j][0] = f[Array[i] - j][0] + Array[i] - j;

                if (f[Array[i] - j][0] + Array[i] - j < Tmp[j][1])
					Tmp[j][1] = f[Array[i] - j][0] + Array[i] - j;
            }

            Suffix[Array[i] + 1] = 0x3f3f3f3f;

            for (int j = Array[i]; j >= 0; --j) {
				f[j][0] = Tmp[j][0];
				f[j][1] = Tmo[j][1];

				Suffix[j] = min(Suffix[j + 1], f[j][1]);
            }

            Ans = f[0][0];

            for (int i = 0; i <= Array[n]; ++i)
				if (f[i][1] > Ans)
					Ans = f[i][1];

			printf("%d\n", Ans);
		}
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("dark.in", "r", stdin);
	freopen("dark.out", "w", stdout);
#endif // LOCAL

	delete new Main();

	return 0;
}
```
