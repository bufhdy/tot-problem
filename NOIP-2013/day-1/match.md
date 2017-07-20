# match

We'll think in which way it can be to get the best result. 

We can suppose that there is two 2-element arrays, { a, b } and { c, d }, ordered from smaller to bigger. Set S<sub>1</sub> = (a - c) * (a - c) + (b - d) * (b - d), and S<sub>2</sub> = (a - d) * (a - d) + (c - d) * (c - d). In this case, S<sub>1</sub> - S<sub>2</sub> = 2 * (d - c) * (a - b) < 0. Use *mathematical induction* to conclude that if the two arrays are in order, it has the mininum value.

Now, what we're going to do is to find out every single inversion:

```c++
for (int i = 1; i <= n; ++i)
	Inversion[Array_2[i].Position] = Array_1[i].Position;
// suppose that Array_2[i].Position is right,
// and get the corresponding position in Array_1
// Inversion[Array_1[i].Position] = Array_2[i].Position also okay
```

In typical O(log n) *binary indexed tree*, we should have three basic functions:

```c++
int LowBit(int x)
{
	return x & (-x);
}

void Edit(int x)
{
	for (int i = x; i <= n; i += LowBit(i))
		// goto a bigger index and higher place
		++BIT[i];
}

int SumFromBegin(int x)
{
	int Sum = 0;

	for (int i = x; i > 0; i -= LowBit(i))
		// goto a smaller index but higher place
		Sum += BIT[i];

	return Sum;
}
```

And for this problem, BIT[i] has been initialised with zero, so we can judge inversions by counting the addtions of index in the wrong range:

```c++
int Pair = 0;
for (int i = 1; i <= n; ++i) {
	Edit(Inversion[i]);
	Pair = (Pair + i - SumFromBegin(Inversion[i])) % MOD;
	// if it's an inversion,
	// SumFromBegin(Inversion[i]) will be smaller than i
}
```

And whole source code here:

```c++
#include <bits/stdc++.h>
using namespace std;
#define NotAVertex -1
const int MAXN = 100005,
	MOD = 99999997;

struct Unit {
	int Value, Position;

	bool operator < (const Unit &x) const
	{
		return Value < x.Value;
	}
} Array_1[MAXN], Array_2[MAXN];

bool Compare(const Unit &x, const Unit &y)
{
	return x < y;
}

int n, Inversion[MAXN], BIT[MAXN] = { 0 };

int LowBit(int x)
{
	return x & (-x);
}

void Edit(int x)
{
	for (int i = x; i <= n; i += LowBit(i))
		// goto a bigger index and higher place
		++BIT[i];
}

int SumFromBegin(int x)
{
	int Sum = 0;

	for (int i = x; i > 0; i -= LowBit(i))
		// goto a smaller index but higher place
		Sum += BIT[i];

	return Sum;
}

int main(void)
{
	cin >> n;

	for (int i = 1; i <= n; ++i) {
		cin >> Array_1[i].Value;
		Array_1[i].Position = i;
	}

	for (int i = 1; i <= n; ++i) {
		cin >> Array_2[i].Value;
		Array_2[i].Position = i;
	}

	sort(Array_1 + 1, Array_1 + n + 1, Compare);
	sort(Array_2 + 1, Array_2 + n + 1, Compare);

	for (int i = 1; i <= n; ++i)
		Inversion[Array_2[i].Position] = Array_1[i].Position;
	// suppose that Array_2[i].Position is right,
	// and get the corresponding position in Array_1
	// Inversion[Array_1[i].Position] = Array_2[i].Position also okay

	int Pair = 0;
	for (int i = 1; i <= n; ++i) {
		Edit(Inversion[i]);
		Pair = (Pair + i - SumFromBegin(Inversion[i])) % MOD;
		// if it's an inversion,
		// SumFromBegin(Inversion[i]) will be smaller than i
	}

	cout << Pair << endl;

	return 0;
}
```

