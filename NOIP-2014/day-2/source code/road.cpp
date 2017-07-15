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
	bool IsMarked;

	VertexHead(void) :
		Distance(INT_MAX), IsMarked(false) {}
} Graph[MAXN];

bool IsVisited[MAXN] = { false };
void SearchFirst(int Start)
{
	IsVisited[Start] = Graph[Start].IsMarked = true;
	queue<int> Travel;
	Travel.push(Start);

	while (!Travel.empty()) {
		int From = Travel.front();
		Travel.pop();

		Vertex *Current = Graph[From].Adjacent;
		while (Current != NULL) {
			if (!IsVisited[Current->Index]) {
				IsVisited[Current->Index] = true;

				Graph[Current->Index].IsMarked = true;

				Travel.push(Current->Index);
			}

			Current = Current->Adjacent;
		}
	}
}

void Search(int Start)
{
	Graph[Start].Distance = 0;
	queue<int> Travel;
	Travel.push(Start);

	while (!Travel.empty()) {
		int From = Travel.front();
		Travel.pop();

		int Count = 0;
		Vertex *Current = Graph[From].Adjacent;
		while (Current != NULL) {
			if (Graph[Current->Index].Distance == INT_MAX &&
				Graph[Current->Index].IsMarked) {
				Graph[Current->Index].Distance = Graph[From].Distance + 1;

				Travel.push(Current->Index);
			}

			Current = Current->Adjacent;
		}
	}
}

int Start, End;

int main(void)
{
	int VertexAmount, ArcAmount;
	cin >> VertexAmount >> ArcAmount;

	for (int i = 1; i <= VertexAmount; ++i)
		Graph[i].Index = i;

	for (int i = 0; i < ArcAmount; ++i) {
		int From, To;
		cin >> From >> To;

		Graph[To].Grow(From);
	}

	cin >> Start >> End;

	SearchFirst(End);

	stack<int> Quit;
	for (int i = 1; i <= VertexAmount; ++i) {
		if (!Graph[i].IsMarked) {
			Vertex *Current = Graph[i].Adjacent;
			while (Current != NULL) {
				Quit.push(Current->Index);

				Current = Current->Adjacent;
			}
		}
	}

	while (!Quit.empty()) {
		Graph[Quit.top()].IsMarked = false;
		Quit.pop();
	}

	Search(End);

	if (Graph[Start].Distance == INT_MAX)
		cout << -1 << endl;
	else cout << Graph[Start].Distance << endl;

	return 0;
}
