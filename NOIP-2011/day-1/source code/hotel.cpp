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
#include <ctime>
using namespace std;
const int MAXN = 55; // 颜色数

struct Hotel {
	/*
		题目大意：
			从 1 到 n 编号的 n 个点，每个点有标识符 c、花费 v；
			一个可行方案：
				选择各异且标识符 c 相同的两点，
				以及两点间（包括两点）的一点，使花费 v 小于预算 p；
			求可行方案数。
	 */

	int n, k, p, 
		Crt, Sum = 0,
		// LastPst：某一种标识符最后一次出现的位置；
		LastPst[MAXN], 
		// CntPst：某一种标识符出现次数；
		CntPst[MAXN],
		// CrtCntPst：当前标识符客栈出现次数；
		CrtCntPst[MAXN];

	Hotel(void) : LastPst(), CntPst(), CrtCntPst()
	{
		scanf("%d %d %d", &n, &k, &p);

		for (int i = 1; i <= n; ++i) {
			int c, v;
			scanf("%d %d", &c, &v);

			if (v <= p) // 花费 v 小于预算 p；
				Crt = i; // 记录可行位置（一定记录的是最右边的）；

			if (LastPst[c] <= Crt) // 标识符 c 最后出现的位置在 Crt 左面，满足条件；
				CrtCntPst[c] = CntPst[c]; // 当前标识符 c 出现的次数；

			LastPst[c] = i; // 记录位置和增加数量
			++CntPst[c];

			Sum += CrtCntPst[c]; 
		}

		printf("%d\n", Sum);
	}
};

int main(void)
{
	delete new Hotel();

	return 0;
}