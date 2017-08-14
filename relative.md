```c++
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
const int MAXN = 200005,
	MOD = (int)1e9 + 7;

struct Vertex {
	Vertex *Next;
	int To;

	Vertex(void) : Next(NULL) {}
};

struct VtxHead : Vertex {
	Vertex *Head;
	long long Count;
	int Size;

	void Grow(int To)
	{
		if (Head == NULL) {
			Next = new Vertex();
			Next->To = To;
			Head = Next;
		} else {
			Next->Next = new Vertex();
			Next = Next->Next;
			Next->To = To;
		}
	}

	VtxHead(void) : Count(1), Size(0), Head(NULL) {}
} Tree[MAXN];

long long Inv(long long x)
{
	long long y = MOD - 2, Result = 1;

	while (y) {
		if (y & 1)
			Result = Result * x % MOD;
		x = x * x % MOD;
		
		y >>= 1;
	}

	return Result;
}

long long C(long long m, long long n)
{
	n = std::min(n, m - n);

	long long Mul = 1, Division = 1;
	for (int i = m - n + 1; i <= m; i++)
		Mul = Mul * i % MOD;
	
	for (int i = 2; i <= n; i++)
		Division = Division * i % MOD;
	
	return Mul * Inv(Division) % MOD;
}

void Search(int x)
{
	for (Vertex *i = Tree[x].Head;
		i != NULL;
		i = i->Next) {
		Search(i->To);

		Tree[x].Count =
			Tree[x].Count * Tree[i->To].Count % MOD *
			C(Tree[i->To].Size + Tree[x].Size, Tree[x].Size) % MOD;

		Tree[x].Size += Tree[i->To].Size;
	}

	++Tree[x].Size;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; ++i) {
		int Father;
		scanf("%d", &Father);

		Tree[Father].Grow(i);
	}

	Search(0);

	printf("%d\n", Tree[0].Count);

	return 0;
}
```
