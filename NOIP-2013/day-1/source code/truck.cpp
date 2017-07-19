#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <stack>
using namespace std;
#define NotAVertex -1
const int MAXN = 1005;

struct Vertex {
	int Index, Limit;

	Vertex *Head, *Adjacent;

	void Grow(int NewIndex, int Limit)
	{
		if (Head == NULL) {
			Adjacent = new Vertex();
			Adjacent->Index = NewIndex;
			Adjacent->Limit = Limit;
			Head = Adjacent;
		}
		else {
			Adjacent->Adjacent = new Vertex();
			Adjacent->Adjacent->Index = NewIndex;
			Adjacent->Adjacent->Limit = Limit;
			Adjacent = Adjacent->Adjacent;
		}
	}

	Vertex(void) : Index(NotAVertex), Head(NULL), Adjacent(NULL) {}
};

struct VertexHead : Vertex {
	VertexHead(void) {}
} Graph[MAXN];

int MaxValue = INT_MIN, CurrentValue = INT_MIN;
bool IsVisited[MAXN] = { false };
int To;
void Search(int From)
{
	if (From == To) {
		if (CurrentValue > MaxValue)
			MaxValue = CurrentValue;
		return;
	}

	Vertex *Current = Graph[From].Adjacent;
	while (Current != NULL) {
		int Temp = CurrentValue;
		IsVisited[Current->Index] = true;

		if (Current->Limit > CurrentValue)
			CurrentValue = Current->Limit;

		Search(Current->Index);

		CurrentValue = Temp;
		IsVisited[Current->Index] = false;
		
		Current = Current->Adjacent;
	}
}

int main(void)
{
#ifndef _DEBUG
	freopen("truck.in", "r", stdin);
	freopen("truck.out", "w", stdout);
#endif // !_DEBUG

	int Amount, Path;
	cin >> Amount >> Path;

	for (int i = 1; i <= Amount; ++i)
		Graph[i].Index = i;

	for (int i = 1; i <= Path; ++i) {
		int u, v, Limit;
		cin >> u >> v >> Limit;

		Graph[u].Grow(v, Limit);
		Graph[v].Grow(u, Limit);
	}
	
	int Query;
	cin >> Query;

	while (Query--) {
		int From;
		cin >> From >> To;

		memset(IsVisited, false, sizeof(IsVisited));

		Search(From);

		if (IsVisited[To])
			cout << MaxValue << endl;
		else cout << -1 << endl;
	}
	
	
	return 0;
}