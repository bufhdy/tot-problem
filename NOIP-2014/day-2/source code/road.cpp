#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <string>
using namespace std;
#define NotAVertex -1

const int MAXN = 10005;

struct Vertex {
	int Index;

	Vertex *Adjacent;

	void Grow(int NewIndex)
	{
		Vertex *Current = this;

		while (Current->Adjacent != NULL)
			Current = Current->Adjacent;

		Current->Adjacent = new Vertex();
		Current->Adjacent->Index = NewIndex;
	}

	Vertex(void) : Adjacent(NULL), Index(NotAVertex) {}
};

struct VertexHead : Vertex {
	int Distance;
	bool IsChecked;
	bool BadPoint;

	VertexHead(void) :
		Distance(INT_MAX), IsChecked(false), BadPoint(false) {}
} Graph[MAXN];

int Start, End;

bool IsVisited[MAXN] = { false };
bool IsConnected(int x)
{
	memset(IsVisited, false, sizeof(IsVisited));
	IsVisited[x] = true;
	stack<int> Travel;
	Travel.push(x);

	while (!Travel.empty()) {
		int From = Travel.top();
		Travel.pop();

		Vertex *Current = Graph[From].Adjacent;
		while (Current != NULL) {
			if (!IsVisited[Current->Index]) {
				IsVisited[Current->Index] = true;

				Travel.push(Current->Index);
			}

			Current = Current->Adjacent;
		}
	}

	return IsVisited[End];
}

void Check(int x)
{
	memset(IsVisited, false , sizeof(IsVisited));

	stack<int> Travel;
	Travel.push(x);

	while (!Travel.empty()) {
		int From = Travel.top();
		Travel.pop();

		Vertex *Current = Graph[x].Adjacent;
		while (Current != NULL) {
			if (!IsVisited[Current->Index]) {
				IsVisited[Current->Index] = true;

				if (Graph[Current->Index].BadPoint) {
					Graph[x].IsChecked = true;
					Graph[x].BadPoint = true;
					return;
				}
			}

			Current = Current->Adjacent;
		}
	}

	Graph[x].IsChecked = true;
	Graph[x].BadPoint = false;
}

void Search(int Start)
{
	Graph[Start].Distance = 0;
	queue<int> Travel;
	Travel.push(Start);

	while (!Travel.empty()) {
		int From = Travel.front();
		Travel.pop();

		Vertex *Current = Graph[From].Adjacent;
		while (Current != NULL) {
			if (!Graph[Current->Index].IsChecked) Check(Current->Index);

			if (Graph[Current->Index].Distance == INT_MAX &&
				!Graph[Current->Index].BadPoint) {
					Graph[Current->Index].Distance = Graph[From].Distance + 1;

				Travel.push(Current->Index);
			}

			Current = Current->Adjacent;
		}
	}
}

int main(void)
{
#ifndef LOCAL
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
#endif // LOCAL

	int VertexAmount, ArcAmount;
	cin >> VertexAmount >> ArcAmount;

	for (int i = 1; i <= VertexAmount; ++i)
		Graph[i].Index = i;

	for (int i = 0; i < ArcAmount; ++i) {
		int From, To;
		cin >> From >> To;

		Graph[From].Grow(To);
	}

	cin >> Start >> End;

	for (int i = 1; i <= VertexAmount; ++i)
		if (!IsConnected(i)) {
			Graph[i].IsChecked = true;
			Graph[i].BadPoint = true;
		}

	Search(Start);

	if (Graph[End].Distance == INT_MAX) cout << -1 << endl;
	else cout << Graph[End].Distance << endl;

	return 0;
}
