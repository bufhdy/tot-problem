#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 110;

int n, m;
int par[maxn];

struct Edge {
	int u, v, c;
	bool operator<(const Edge &a) const
	{
		return c < a.c;
	}

	Edge(int _u, int _v, int _c)
	{
		u = _u, v = _v, c = _c;
	}
};

vector<Edge> edge;

int findx(int x)
{
	if (par[x] == x) return x;
	else return par[x] = findx(par[x]);
}

void init(void)
{
	for (int i = 1; i <= n; ++i) {
		par[i] = i;
	}
}

int main(void)
{
	while (~scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		edge.clear();
		for (int i = 0; i < m; ++i) {
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			edge.push_back(Edge(u, v, c));
		}
		sort(edge.begin(), edge.end());
		int ans = inf;
		for (int i = 0; i <= m - n + 1; ++i) {
			init();
			int cnt = 0;
			for (int j = i; j < m; j++) {
				int t1 = findx(edge[j].u);
				int t2 = findx(edge[j].v);
				if (t1 != t2) {
					par[t1] = t2;
					cnt++;
				}
				if (cnt == n - 1) {
					ans = min(ans, edge[j].c - edge[i].c);
					break;
				}
			}
		}
		if (ans == inf) puts("-1");
		else printf("%d\n", ans);
	}
	return 0;

}