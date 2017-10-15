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
const int MAXN = 1e4 + 5;

struct Vtx {
	Vtx *Next;
	int To;

	Vtx(void) : Next(NULL) {}
};

struct VtxHead : Vtx {
	Vtx *Head;
	int Dist;
	bool IsLink;

	void operator += (int To)
	{
		if (!Head) {
			Next = new Vtx();
			Next->To = To;
			Head = Next;
		}
		else {
			Next->Next = new Vtx();
			Next = Next->Next;
			Next->To = To;
		}
	}

	VtxHead(void) : Head(NULL),
		Dist(INT_MAX),
		IsLink(false) {}
} Graph[MAXN], GraphOppo[MAXN];

struct Main {
	int n, m;

	void SearchOppo(int Start)
	{
		queue<int> Travel;
		Travel.push(Start);
		GraphOppo[Start].Dist = 1;

		while (!Travel.empty()) {
			int x = Travel.front();
			Travel.pop();

			for (Vtx *i = GraphOppo[x].Head;
				i; i = i->Next) {
				if (GraphOppo[i->To].Dist == INT_MAX) {
					GraphOppo[i->To].Dist = 1;

					Graph[i->To].IsLink = true;

					Travel.push(i->To);
				}
			}
		}
	}

	void Search(int Start)
	{
		queue<int> Travel;
		Travel.push(Start);
		Graph[Start].Dist = 0;

		while (!Travel.empty()) {
			int x = Travel.front();
			Travel.pop();

			for (Vtx *i = Graph[x].Head;
				i; i = i->Next) {
				if (Graph[i->To].Dist == INT_MAX &&
					Graph[i->To].IsLink) {
					Graph[i->To].Dist =
						Graph[x].Dist + 1;

					Travel.push(i->To);
				}
			}
		}
	}

	Main(void)
	{
		scanf("%d %d", &n, &m);

		for (int i = 1; i <= m; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);

			Graph[u] += v;
			GraphOppo[v] += u;
		}

		int Start, End;
		scanf("%d %d", &Start, &End);

		SearchOppo(End); Graph[End].IsLink = true;

		queue<int> QuitList;
		for (int i = 1; i <= n; ++i)
			if (!Graph[i].IsLink)
				for (Vtx *j = GraphOppo[i].Head;
					j; j = j->Next)
					QuitList.push(j->To);

		while (!QuitList.empty()) {
			Graph[QuitList.front()].IsLink = false;
			QuitList.pop(); 
		}

		Search(Start);

		if (Graph[End].Dist == INT_MAX) puts("-1");
		else printf("%d\n", Graph[End].Dist);
	}
};

int main(void)
{
	delete new Main();

	return 0;
}