#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

struct Main {
	struct Edge {
		int u, v, Capacity, Flow;

		Edge (int u, int v, int Capacity, int Flow) :
			u(u), v(v), Capacity(Capacity), Flow(Flow) {}
	};

	struct Edmonds_Karp {
		vector<Edge> Edges;
		vector<int> Graph[MAXN]; // 保存下标
		int n, 
			Augment[MAXN], Previous[MAXN];
			// 当起点到 Augment[i] 的可改进量；

		void Initialise(int n)
		{
			for (int i = 0; i < n; ++i)
				G[i].clear();

			Edges.clear();
		}

		void Add(int u, int v, int Capacity)
		{
			Edges.push_back(Edge(u, v, Capacity, 0));
			Edges.push_back(Edge(v, u, 0, 0));

			int m = Edges.size() - 1;

			Graph[u].push_back(m - 1);
			Graph[v].push_back(m);
		}
	};

	int MaxFlow(int s, int t)
	{
		int FlowSum = 0;
		while (1) {
			memset(Augment, 0, sizeof Augment);

			queue<int> Travel;
			Travel.push(s);
			Augment[s] = INT_MAX;

			while (!Travel.empty()) {
				int From = Travel.front();
				Travel.pop();

				for (int i = 0; i < Graph[From].size(); ++i) {
					Edge &Temp = Edges[Graph[From][i]];

					if (!Augment[Temp.v] && Temp.Capacity > Temp.Flow) {
						Previous[Temp.v] = Graph[From][i];
						Augment[Temp.v] = min(Augment[From], Temp.Capacity - Temp.Flow);

						Travel.push(Temp.v);
					}
				}

				if (Augment[t]) break;
			}

			if (!Augment[t]) break;

			for (int i = t; i != s; i = Edges[Previous[i]].From) {
				Edges[Previous[i]].Flow += Augment[t];
				Edges[Previous[i] ^ 1].Flow -= Augment[t];
			}

			FlowSum += Augment[t];
		}

		return flow;
	}


	Main(void) {}
};

int main(void)
{
	delete new Main();

	return 0;
}