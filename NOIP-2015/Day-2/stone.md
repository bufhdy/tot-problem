# 1. stone

We use **bisection algorithm** to solve the problem, stone.

First of all, fill in the Distance array, and don’t forget to add the Length as a unit because the start and end point are just normal like the others.

Declare Left and Right as the max limit of delta, and then continuing assume the Middle is the answer, and get into the Check() to verify whether it is adequate. If not, adjust the Left and Right value to get approached.

Finally, Left equals to Right and that is the right answer to the problem.

```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;

int Distance[MAXN] = { 0 },
	Amount, Remove;

bool Check(int x)
{
	int Count = 0,
		Last = 0;

	for (int i = 1; i <= Amount; ++i)
		if (Distance[i] - Last < x) ++Count;
		else Last = Distance[i];

	if (Count > Remove)
		return false;
	return true;
}

int main(void)
{
	int Length;
	cin >> Length >> Amount >> Remove;

	for (int i = 1; i <= Amount; ++i)
		cin >> Distance[i];
	Distance[++Amount] = Length;

	int Left = 0, Right = Length;

	while (Left <= Right) {
		int Middle = (Left + Right) / 2;

		if (Check(Middle)) Left = Middle + 1;
		else Right = Middle - 1;
	}

	cout << Right << endl;

	return 0;
}
```