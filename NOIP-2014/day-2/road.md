# road

## reflection

I spent lots of time(about 5 hours) to finished this problem, and I think when it comes to some knowledge of tree, I'll mess up and hard to find the solution.

Specifically, the biggest problem I'm facing is the store adjacency list. I used my own methond like having Vertex and VertexHead(inheriting from Vertex) structures:

```c++
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
	... // variables that every vertex should store

	VertexHead(void) :
		...(...) {}
} Graph[MAXN];
```

I used to feel prond of it because of its object-oriented style and logic, but it just take pretty much space and waste time when running `Grow()`.

I should've get a Head and Tail(Vertex*) instead of Adjacent. Thus it just take O(1) in `Grow()`:

```c++
struct Vertex {
	int Index;

	Vertex *Head, *Adjacent;

	void Grow(int NewIndex)
	{
		if (Head == NULL) {
			Adjacent = new Vertex();
			Adjacent->Index = NewIndex;
			Head = Adjacent;
		} else {
			Adjacent->Adjacent = new Vertex();
			Adjacent = Adjacent->Adjacent;
			Adjacent->Index = NewIndex;
		}
	}

	Vertex(void) : Index(NotAVertex), Head(NULL), Adjacent(NULL) {}
};
```

Okay, at last, I wrote:

```c++
struct Vertex {
	int To;
	Vertex  *Next;

	Vertex(void) : To(NotAVertex), Next(NULL) {}
};

struct VtxHead : Vertex {
	... // variables that every vertex should store
	Vertex *Head;

	void Grow(int NewIndex)
	{
		if (Head == NULL) {
			Next = new Vertex();
			Next->To = NewIndex;
			Head = Next;
		}
		else {
			Next->Next = new Vertex();
			Next = Next->Next;
			Next->To = NewIndex;
		}
	}

	VtxHead(void) :
		Head(NULL),
		...(...) {}
} Graph[MAXN];
```

For the reason to save the space, just like:

![road](https://github.com/bufhdy/tot-problem/raw/master/NOIP-2014/day-2/image/road_1.png)

<br />

## solve

As for the problem, I only describe the procedure of solving.

After reading the data, BFS(`Search()`) for the cannot-be-visited vertices, and mark the others. Then deal with the unmarked vertices, that is, unmark every adjacent vertex of them. Totally, they take O(|E| + |V|) + O(n).

At Last BFS again, find and print the minimum distance from End to Start, and if it's `INT_MAX`, that means there's no path between. Instead, print -1. All of them above takes 2 * O(|E| + |V|) + O(n) = O(n).

<br />

## source code

```c++
#include <bits/stdc++.h>
using namespace std;
#define NotAVertex -1

const int MAXN = 10005;

struct Vertex {
	int Index;

	Vertex *Head, *Adjacent;

	void Grow(int NewIndex)
	{
		if (Head == NULL) {
			Adjacent = new Vertex();
			Adjacent->Index = NewIndex;
			Head = Adjacent;
		} else {
			Adjacent->Adjacent = new Vertex();
			Adjacent->Adjacent->Index = NewIndex;
			Adjacent = Adjacent->Adjacent;
		}
	}

	Vertex(void) : Index(-1), Head(NULL), Adjacent(NULL) {}
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

		Vertex *Current = Graph[From].Head;
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
		Vertex *Current = Graph[From].Head;
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
			Vertex *Current = Graph[i].Head;
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
```
