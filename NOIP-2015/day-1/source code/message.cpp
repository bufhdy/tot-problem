#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
using namespace std;
const int MAXN = 200005;

int To[MAXN] = { 0 }, Indegree[MAXN] = { 0 };
bool IsVisited[MAXN] = { false };

int main(void)
{
	int Amount, MinTime;
	cin >> Amount;
	MinTime = Amount;

	for (int i = 1; i <= Amount; i++) {
 		cin >> To[i];
		++Indegree[To[i]];
	}

	queue<int> Travel;
	for (int i = 1; i <= Amount; i++)
		if (Indegree[i] == 0) {
			Travel.push(i);
			IsVisited[i] = true;
		}

	while (!Travel.empty()) {
		int Vertex = Travel.front();
		Travel.pop();

		if (--Indegree[To[Vertex]] == 0) {
			Travel.push(To[Vertex]);
			IsVisited[To[Vertex]] = true;
		}
	}

	for (int i = 1; i <= Amount; i++)
		if (!IsVisited[i]) {
			IsVisited[i] = true;
			int Length = 1,
				Vertex = To[i];

			while (!IsVisited[Vertex]) {
				IsVisited[Vertex] = true;
				Vertex = To[Vertex];
				++Length;
			}

			if (Length <= MinTime)
				MinTime = Length;
		}

	cout << MinTime << endl;

	return 0;
}