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

const int MAXN = 100005;

/*

	3P algorithm sure it is

*/

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
	int Value, CircleMin, CircleLength;
	long long CircleSum;

	VertexHead(void) : CircleMin(INT_MAX), CircleSum(0) {}
} Graph[MAXN];

int LastIndex[MAXN];
void Road(int From)
{
	vector<long long> RoadSum(1);
	vector<int> RoadValue(1);

	memset(LastIndex, NotAVertex, sizeof(LastIndex));

	RoadSum[0] = RoadValue[0] = 0;
	RoadSum.push_back(Graph[From].Value);
	RoadValue.push_back(Graph[From].Value);
	LastIndex[From] = 1;
	int Current = Graph[From].Adjacent->Index;

	while (Current != NotAVertex) {
        if (LastIndex[Current] == NotAVertex) {
        	int TempIndex = RoadSum.size() - 1;
			RoadSum.push_back(RoadSum[TempIndex] + Graph[Current].Value);
			RoadValue.push_back(Graph[Current].Value);
			// IsVisited[Current] = true;
			LastIndex[Current] = TempIndex + 1;
			Current = Graph[Current].Adjacent->Index;
        } else {
            Graph[Current].CircleSum =
            	RoadSum[RoadSum.size() - 1] - RoadSum[LastIndex[Current] - 1];

			Graph[Current].CircleMin =
				*min_element(RoadValue.begin() + LastIndex[Current],
					RoadValue.end());

			Graph[Current].CircleLength = RoadSum.size() - LastIndex[Current];

			break;
        }
	}
}

int k;
void Search(int From)
{
	int Current = From, MinValue = INT_MAX;
	long long Sum = 0;
	for (int i = 0; i < k; ++i) {
		if (Graph[Current].CircleLength) {
            Sum += ((k - i + 1) / Graph[Current].CircleLength) *
				Graph[Current].CircleSum;

			i += (k - i + 1) % Graph[Current].CircleLength;

            // i += k - i - (k - 1) % Graph[Current].CircleLength - 1;
            // Sum += ((k - 1) / Graph[Current].CircleLength - 1) * Graph[Current].CircleSum;
			// cout << i << endl << k << endl;
			// i += (k - i - (k - i) % Graph[Current].CircleLength);

			Sum -= Graph[Current].Value;
		}

		if (Graph[Current].Value < MinValue)
			MinValue = Graph[Current].Value;
		Sum += Graph[Current].Value;

		Current = Graph[Current].Adjacent->Index;
	}

	cout << Sum << ' ' << MinValue << endl;
}

int main(void)
{
#ifndef LOCAL
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif // LOCAL

	int n;
	cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		int To;
		cin >> To;

		Graph[i].Index = i;
		Graph[i].Grow(To);
	}

	for (int i = 0; i < n; ++i)
		cin >> Graph[i].Value;

	for (int i = 0; i < n; ++i)
		Road(i);

	for (int i = 0; i < n; ++i)
		Search(i);


	return 0;
}
