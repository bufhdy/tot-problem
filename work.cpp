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

const int MAXN = 200005,
	MOD = 10007;

struct Vertex {
    vector<int> Adjacent;
    int Count, Value, Distance;

    void Grow(int NewIndex)
    {
    	// Adjacent.resize(++Count);
        Adjacent[Count++] = NewIndex;
    }

    Vertex(void) {
    	Distance = INT_MAX;
    	Count = 0;
		Adjacent.resize(MAXN);
    }
} Graph[MAXN];

int MaxValue = INT_MIN, Sum = 0;

int Temp[MAXN];

void Search(int Start)
{
	memset(Temp, 0, sizeof(Temp));

	long long Sum_1 = 0;
	int Max_1 = INT_MIN, Max_2 = INT_MIN;

    for (int i = 0; i < Graph[Start].Count; ++i) {
        Temp[i] = Graph[Graph[Start].Adjacent[i]].Value;

        Sum_1 += Temp[i];
    }

    for (int i = 0; i < Graph[Start].Count; ++i) {
        Sum = (Sum + (Sum_1 - Temp[i]) * Temp[i]) % MOD;

        if (Temp[i] > Max_1) {
			Max_2 = Max_1;
			Max_1 = Temp[i];
        } else if (Temp[i] > Max_2)
			Max_2 = Temp[i];
    }

    if (Max_1 != INT_MIN && Max_2 != INT_MIN)
		if (Max_1 * Max_2 > MaxValue)
			MaxValue = Max_1 * Max_2;
}

int main(void)
{
	int n; // it's just a tree
	cin >> n;

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

	for (int i = 1; i <= n; ++i)
		Search(i);

	cout << MaxValue << ' ' << Sum << endl;

	return 0;
}
