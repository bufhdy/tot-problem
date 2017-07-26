# toy

There're two numbers, a and b. One of them may be negative. You should notice that if you want to calculate a % b, use ((a % b) + b) % b to get the right answer.

```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;

char Name[MAXN][15];
bitset<MAXN> IsOutside;

int main(void)
{
	int n, Query;
	cin >> n >> Query;

	for (int i = 0; i < n; ++i) {
		bool Temp;
		cin >> Temp >> Name[i];
		IsOutside[i] = Temp;
	}
	
	long long Position = 0;
	while (Query--) {
		bool IsRight;
		long long Turn;
		cin >> IsRight >> Turn;

		if (!IsRight)
			if (IsOutside[Position] == true)
				Position = (Position + Turn) % n;
			else Position = ((Position - Turn) % n + n) % n;
      		// eliminate the interference of negative numbers
		else 
			if (IsOutside[Position] == true)
				Position = ((Position - Turn) % n + n) % n;
			else Position = (Position + Turn) % n;
	}

	cout << Name[Position] << endl;

	return 0;
}
```

