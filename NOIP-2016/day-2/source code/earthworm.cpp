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
const int MAXN = 7e6 + 5;

int n, m, q, u, v, t;

struct Brute_1 {
	queue<int> Ogl, Lft, Rgt;

	int OglTmp[MAXN];

	Brute_1(void)
	{
		for (int i = 1; i <= n; ++i)
			scanf("%d", OglTmp + i);

		sort(OglTmp + 1, OglTmp + n + 1);

		for (int i = n; i >= 1; --i)
			Ogl.push(OglTmp[i]);

		for (int i = 1; i <= m; ++i) {
			int Max = Ogl.front(),
				Type = 1;

			if (!Lft.empty() && Lft.front() > Max) {
				Max = Lft.front();
				Type = 2;
			}

			if (!Rgt.empty() && Rgt.front() > Max) {
				Max = Rgt.front();
				Type = 3;
			}

			if (Type == 1) Ogl.pop();
			else if (Type == 2) Lft.pop();
			else Rgt.pop();

			printf("%d ", Max);

			int Part = floor(u * Max / v);
			Lft.push(Part);
			Rgt.push(Max - Part);
		}
	}
};

struct Main {
	int OglTmp[MAXN], qTmp;

	queue<int> Ogl, Lft, Rgt;

	Main(void) : qTmp()
	{
		for (int i = 1; i <= n; ++i)
			scanf("%d", OglTmp + i);
		
		sort(OglTmp + 1, OglTmp + n + 1);

		for (int i = n; i >= 1; --i)
			Ogl.push(OglTmp[i]);

		for (int i = 1; i <= m; ++i) {
			int Max = INT_MIN, Type;
			
			if (!Ogl.empty() && Ogl.front() > Max) {
				Max = Ogl.front();
				Type = 1;
			}

			if (!Lft.empty() && Lft.front() > Max) {
				Max = Lft.front();
				Type = 2;
			}

			if (!Rgt.empty() && Rgt.front() > Max) {
				Max = Rgt.front();
				Type = 3;
			}

			Max += qTmp;

			if (Type == 1) Ogl.pop();
			else if (Type == 2) Lft.pop();
			else Rgt.pop();

			int Part = (long long)Max * u / v,
				Other = Max - Part;

			if (i % t == 0) 
				printf("%d ", Max);

			Lft.push(Part - qTmp - q);
			Rgt.push(Other - qTmp - q);

			qTmp += q;
		} puts("");

		for (int i = 1; i <= n + m; ++i) {
			int Max = INT_MIN, Type;

			if (!Ogl.empty() && Ogl.front() > Max) {
				Max = Ogl.front();
				Type = 1;
			}

			if (!Lft.empty() && Lft.front() > Max) {
				Max = Lft.front();
				Type = 2;
			}

			if (!Rgt.empty() && Rgt.front() > Max) {
				Max = Rgt.front();
				Type = 3;
			}

			if (Type == 1) Ogl.pop();
			else if (Type == 2) Lft.pop();
			else Rgt.pop();

			if (i % t == 0)
				printf("%d ", Max + qTmp);
		}

		puts("");
	}
};

int main(void)
{
	scanf("%d %d %d %d %d %d",
		&n, &m, &q, &u, &v, &t);

	delete new Main();

	return 0;
}
