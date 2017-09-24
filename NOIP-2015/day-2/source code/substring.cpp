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
const int MAXN = 1005,
	MOD = 1e9 + 7;

/*
	题目大意：
		从 A 中选 k 个子串，连接起来刚好为 B。

	题解：
	规定数组下标从 0 开始。
	
	f[i][j][l] 表示：i 从 1 开始，
		串 A 匹配到 i - 1 个位置，
		串 B 匹配到 j - 1 个位置，
		且恰好选串 A 的 i - 1 号元素
		的方案总数。

	s[i][j][l] 表示：i 从 1 开始，
		串 A 匹配到 i - 1 个位置，
		串 B 匹配到 j - 1 个位置
		的方案总数，
		s[m][n][l] 即为所求。

	边界情况：
	s[i][0][0] = 1;

	状态转移方程：
	s[i][j][l] =
		s[i - 1][j][l] + f[i][j][l];
	上一阶段串 A 没有使用第 i - 1 个位置的总数，
		加上串 A 使用第 i - 1 个位置的方案总数。

	求 f[i][j][l]，类似求最长公共子序列，
		如果 A[i - 1] == B[j - 1]，
			串 A 的 i - 1 位置
				可以与 i - 2 位置合成一组，
				组数不变；
			串 A 的 i - 1 位置
				不与 i - 2 位置合成一组，
				组数增加。
			f[i][j][l] =
				f[i - 1][j - 1][l] +
				s[i - 1][j - 1][l - 1];
	如果 A[i - 1] != B[j - 1]，
		则 f[i][j][l] = 0。
*/

struct Origin {
	int n, m, k;
	char A[1005], B[205];
	int f[MAXN][205][205],
		s[MAXN][205][205];

	Origin(void) : s(), f()
	{
		scanf("%d %d %d %s %s",
			&n, &m, &k, A, B);

		s[0][0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			s[i][0][0] = 1;

			for (int j = 1; j <= m; ++j)
				if (A[i - 1] == B[j - 1])
					for (int l = 1; l <= min(k, j); ++l) {
						f[i][j][l] = (
							s[i - 1][j - 1][l - 1] +
							f[i - 1][j - 1][l]) % MOD;
						s[i][j][l] = (
							s[i - 1][j][l] +
							f[i][j][l]) % MOD;
					}
				else
					for (int l = 1; l <= min(k, j); ++l)
						s[i][j][l] =
							s[i - 1][j][l];
		}

		printf("%d\n", s[n][m][k]);
	}
};

struct Main {
	int n, m, k;
	char A[1005], B[205];
	int f[205][205],
		s[205][205];

	Main(void) : s(), f()
	{
		scanf("%d %d %d %s %s",
			&n, &m, &k, A, B);

		s[0][0] = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = m; j > 0; --j)
				if (A[i - 1] == B[j - 1])
					for (int l = min(k, j); l > 0; --l) {
						f[j][l] = (
							s[j - 1][l - 1] +
							f[j - 1][l]) % MOD;
						s[j][l] = (
							s[j][l] +
							f[j][l]) % MOD;
					}
				else fill(f[j], f[j] + min(k, j) + 1, 0);

		printf("%d\n", s[m][k]);
	}
};

int main(void)
{
	// delete new Origin();
	delete new Main();

	return 0;
}