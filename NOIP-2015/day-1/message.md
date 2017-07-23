# message

Build an array to store the unidirectional graph, To, at the same time, record the in degree of each vertex.

IsVisited Array is used to save vertices that should be deleted because their in degrees equal to 0, or are going to be 0 after others’ deletions. Thus we do get rid of them with a queue, Travel, with which we’ve done some pushing and poping.

Right now, we’ve got a minimal graph without zero-in-degree vertices, and with some cycles. What we need to do now, is to traverse every single cycle, and work out the minimum. And that turns out to be the answer.

```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int To[MAXN], Indegree[MAXN];
bool IsVisited[MAXN];

int main(void)
{
	int n;
	cin >> n;
	
	for (int i = 1; i <= n; ++i) {
		cin >> To[i];
		++Indegree[To[i]];
	}
	
	stack<int> Travel; 
	for (int i = 1; i <= n; ++i)
		if (Indegree[i] == 0) {
			Travel.push(i);
			IsVisited[i] = true;
		}
	
	while(!Travel.empty()) {
		int x = Travel.top();
		Travel.pop();
		
		if (--Indegree[To[x]] == 0) {
			IsVisited[To[x]] = true;
			
			Travel.push(To[x]);
		}
	}
	
	int MinLength = INT_MAX;
	for (int i = 1; i <= n; ++i) {
		if (!IsVisited[i]) {
			IsVisited[i] = true;
			
			int Current = To[i], Length = 1;
			while(!IsVisited[Current]) {
				++Length;
				IsVisited[Current] = true;
				Current = To[Current];
			}
			
			if (Length < MinLength)
				MinLength = Length;
		}
	}
	
	cout << MinLength << endl;
	
	return 0;
}
```

