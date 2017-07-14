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