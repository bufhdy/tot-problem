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

const int MAXN_60 = 2005;
const int Moder = 10007;

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
	bool IsVisited;
    int Distance;
	int Value;

	void Reset(void) {
		Distance = INT_MAX;
	}

	VertexHead(void) {
		Reset();
	}
} Graph[MAXN_60];

int MaxValue = INT_MIN, Sum = 0;

void Unweighted(int Start)
{
    Graph[Start].Distance = 0;
    queue<int> Travel;
    Travel.push(Start);

	while (!Travel.empty()) {
        int From = Travel.front();
        Travel.pop();

        Vertex *Current =
			Graph[From].Adjacent;

		while (Current != NULL) {
            if (Graph[Current->Index].Distance == INT_MAX) {
				Graph[Current->Index].Distance = Graph[From].Distance + 1;
				Travel.push(Current->Index);
            }

            Current = Current->Adjacent;
		}


	}
}

bool IsVisited[MAXN_60] = { false };

int main(void)
{
#ifndef LOCAL
	freopen("link.in", "r", stdin);
	freopen("link.out", "w", stdout);
#endif

    int n; // it's just a tree
    cin >> n;

    for (int i = 1; i <= n; ++i)
		Graph[i].Index = i;

    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;

        Graph[a].Grow(b);
        Graph[b].Grow(a);
    }

    for (int i = 1; i <= n; ++i) {
        int Value;
        cin >> Value;

		Graph[i].Value = Value;
    }

    for (int i = 1; i <= n; ++i) {
        Unweighted(i);

        for (int j = 1; j <= n; ++j) {
            if (Graph[j].Distance == 2) {
                int Temp = Graph[i].Value * Graph[j].Value % Moder;
                Sum = (Sum + Temp) % Moder;

                if (Temp > MaxValue)
					MaxValue = Temp;
            }

			Graph[j].Reset();
		}
    }

    cout << MaxValue << ' ' << Sum << endl;

    return 0;
}
