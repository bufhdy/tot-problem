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
const int MAXN = 100005;

struct Main {
	struct Carpet {
		int xL, yD, xR, yU;

		void Calc(int xE, int yE)
		{
			xR = xL + xE;
			yU = yD + yE;
		}

		bool IsIn(int x, int y)
		{
			if (x >= xL && x <= xR &&
				y >= yD && y <= yU) return true;
			return false;
		}

		Carpet(void) {}
	} Ceremony[MAXN];

	Main(void)
	{
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; ++i) {
			int xE, yE;
			scanf("%d %d %d %d",
				&Ceremony[i].xL, &Ceremony[i].yD, &xE, &yE);

			Ceremony[i].Calc(xE, yE);
		}

		int x, y;
		scanf("%d %d", &x, &y);

		for (int i = n; i >= 1; --i)
			if (Ceremony[i].IsIn(x, y)) {
				printf("%d", i);
				exit(0);
			}

		puts("-1");
		exit(0);
	}
};

int main(void)
{
	delete new Main();

	return 0;
}