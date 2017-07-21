# message

We could assume that the min time equals to the amount of people at first. Next, build an array to store the unidirectional graph, To, at the same time, record the in degree of each vertex.

IsVisited Array is used to save vertices that should be deleted because their in degrees equal to 0, or are going to be 0 after others’ deleting. Thus we do get rip of them with a queue, Travel, with which we’ve done some pushing and poping.

Right now, we’ve got a minimal graph without zero-in-degree vertices, and with some cycles. What we need to do now, is to traverse every single cycle, and work out the minimum. And that turns out to be the answer.

```c++
#include <bits/stdc++.h>
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
```

