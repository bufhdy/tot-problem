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
const int MAXN = 2005;

int n, Request, Path, Classroom,
	Class_1[MAXN], Class_2[MAXN],
	Cost[305][305];
double k[MAXN];

void Floyd(void)
{
	for (int Via = 0; Via < Classroom; ++Via)
		for (int From = 0; From < Classroom; ++From)
			for (int To = 0; To < Classroom; ++To)
				Cost[From][To] = min(
					Cost[From][Via] + Cost[Via][To],
					Cost[From][To]
				); // 分段走和直接走的最小值
}

double Dynamic[MAXN][MAXN][2];
// Dynamic[i][j][k] 表示在选了 j 个教室的情况下，第 i 个教室是否选择（k）

int main(void)
{
	cin >> n >> Request >> Classroom >> Path;

	memset(Cost, 0x3f, sizeof(Cost));
	for (int i = 0; i < Classroom; ++i) Cost[i][i] = 0;

	for (int i = 0; i < n; ++i) {
		scanf("%d", &Class_1[i]);
		--Class_1[i]; // 以 0 开始保存下标，接下来的自减操作同
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &Class_2[i]);
		--Class_2[i];
	}
	for (int i = 0; i < n; ++i)
		scanf("%lf", &k[i]);

	for (int i = 0; i < Path; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		--a, --b;

		if (w < Cost[a][b]) // 排除多条路径的干扰
			Cost[a][b] = Cost[b][a] = w;
	}

	Floyd(); // Floyd 求多源最短路径

	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= Request; ++j)
			Dynamic[i][j][0] =
			Dynamic[i][j][1] = DBL_MAX;

	Dynamic[0][0][0] = Dynamic[0][1][1] = 0.0;

	for (int i = 1; i < n; ++i)
		for (int j = 0; j <= Request; ++j) { // 列举每种请求
			Dynamic[i][j][0] = min(
				Dynamic[i - 1][j][0] + // 回退到前一状态
					Cost[Class_1[i - 1]][Class_1[i]],
				Dynamic[i - 1][j][1] + // 加权求期望值
					k[i - 1] * Cost[Class_2[i - 1]][Class_1[i]] + // 通过
					(1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_1[i]] // 不通过
			);

			if (j > 0)
				Dynamic[i][j][1] = min(
					Dynamic[i - 1][j - 1][0] + // 回退到前一状态
						k[i] * Cost[Class_1[i - 1]][Class_2[i]] + // 通过
						(1 - k[i]) * Cost[Class_1[i - 1]][Class_1[i]], // 不通过
					Dynamic[i - 1][j - 1][1] +
						k[i] * k[i - 1] * Cost[Class_2[i - 1]][Class_2[i]] + // 都通过
						(1 - k[i]) * (1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_1[i]] + // 都通不过
						k[i] * (1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_2[i]] + // 前一个通过
						(1 - k[i]) * k[i - 1] * Cost[Class_2[i - 1]][Class_1[i]] // 后一个通过
				);
		}

	double MinEnergy = DBL_MAX;

	for (int i = 0; i <= Request; ++i) {
		if (Dynamic[n - 1][i][0] < MinEnergy)
			MinEnergy = Dynamic[n - 1][i][0];
		if (Dynamic[n - 1][i][1] < MinEnergy)
			MinEnergy = Dynamic[n - 1][i][1];
	}

	printf("%.2f\n", MinEnergy);

	return 0;
}