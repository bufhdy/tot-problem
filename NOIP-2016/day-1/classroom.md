# classroom

## Floyd–Warshall algorithm

Floyd-Warshall use *dynamic programming* to find shortest paths between all pairs of vertices.

```c++
void Floyd(void)
{
	for (int Via = 0; Via < Classroom; ++Via)
		for (int From = 0; From < Classroom; ++From)
			for (int To = 0; To < Classroom; ++To)
				Cost[From][To] = min(
					Cost[From][Via] + Cost[Via][To],
					Cost[From][To]
				); // minimum of separated and whole path 
}
```

There's a little handling in main():

```c++
if (w < Cost[a][b]) // eliminate the interference of multi-path
	Cost[a][b] = Cost[b][a] = w;
```

<br />

## Dynamic

```c++
double Dynamic[MAXN][MAXN][2];
// Dynamic[i][j][k] means that we've chosen j classroom(s)
// and whether(k) we'll choose the classroom of i
```

In main():

```c++
for (int i = 0; i < n; ++i)
	for (int j = 0; j <= Request; ++j)
		Dynamic[i][j][0] =
		Dynamic[i][j][1] = DBL_MAX;

Dynamic[0][0][0] = Dynamic[0][1][1] = 0.0;

for (int i = 1; i < n; ++i)
	for (int j = 0; j <= Request; ++j) { // list different requests
		Dynamic[i][j][0] = min(
			Dynamic[i - 1][j][0] + // back to last situation
				Cost[Class_1[i - 1]][Class_1[i]],
			Dynamic[i - 1][j][1] + // calculate the expected value by weight
				k[i - 1] * Cost[Class_2[i - 1]][Class_1[i]] + // pass
				(1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_1[i]] // not pass
		);

		if (j > 0)
			Dynamic[i][j][1] = min(
				Dynamic[i - 1][j - 1][0] + // back to last situation
					k[i] * Cost[Class_1[i - 1]][Class_2[i]] + // pass
					(1 - k[i]) * Cost[Class_1[i - 1]][Class_1[i]], // not pass
				Dynamic[i - 1][j - 1][1] +
					k[i] * k[i - 1] * Cost[Class_2[i - 1]][Class_2[i]] + // both pass
					(1 - k[i]) * (1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_1[i]] + // both not pass
					k[i] * (1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_2[i]] + // pass the former
					(1 - k[i]) * k[i - 1] * Cost[Class_2[i - 1]][Class_1[i]] // pass the latter
			);
	}
```

Source code:

```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

int n, Request, Path, Classroom,
	Class_1[MAXN], Class_2[MAXN],
	Cost[305][305];
double k[MAXN];

void Floyd(void)
{
	for (int Via = 0; Via < Classroom; ++Via)
		for (int From = 0; From < Classroom; ++From)
			for (int To = 0; To < Classroom; ++To)
				Cost[From][To] = min(
					Cost[From][Via] + Cost[Via][To],
					Cost[From][To]
				); // minimum of separated and whole path
}

double Dynamic[MAXN][MAXN][2];
// Dynamic[i][j][k] means that we've chosen j classroom(s)
// and whether(k) we'll choose the classroom of i

int main(void)
{
	cin >> n >> Request >> Classroom >> Path;

	memset(Cost, 0x3f, sizeof(Cost));
	for (int i = 0; i < Classroom; ++i) Cost[i][i] = 0;

	for (int i = 0; i < n; ++i) {
		scanf("%d", &Class_1[i]);
		--Class_1[i];
		// we save from index of 0 so do the decrement
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &Class_2[i]);
		--Class_2[i];
	}
	for (int i = 0; i < n; ++i)
		scanf("%lf", &k[i]);

	for (int i = 0; i < Path; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		--a, --b;

		if (w < Cost[a][b]) // eliminate the interference of multi-path
			Cost[a][b] = Cost[b][a] = w;
	}

	Floyd();

	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= Request; ++j)
			Dynamic[i][j][0] =
			Dynamic[i][j][1] = DBL_MAX;

	Dynamic[0][0][0] = Dynamic[0][1][1] = 0.0;

	for (int i = 1; i < n; ++i)
		for (int j = 0; j <= Request; ++j) { // list different requests
			Dynamic[i][j][0] = min(
				Dynamic[i - 1][j][0] + // back to last situation
					Cost[Class_1[i - 1]][Class_1[i]],
				Dynamic[i - 1][j][1] + // calculate the expected value by weight
					k[i - 1] * Cost[Class_2[i - 1]][Class_1[i]] + // pass
					(1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_1[i]] // not pass
			);

			if (j > 0)
				Dynamic[i][j][1] = min(
					Dynamic[i - 1][j - 1][0] + // back to last situation
						k[i] * Cost[Class_1[i - 1]][Class_2[i]] + // pass
						(1 - k[i]) * Cost[Class_1[i - 1]][Class_1[i]], // not pass
					Dynamic[i - 1][j - 1][1] +
						k[i] * k[i - 1] * Cost[Class_2[i - 1]][Class_2[i]] + // both pass
						(1 - k[i]) * (1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_1[i]] + // both not pass
						k[i] * (1 - k[i - 1]) * Cost[Class_1[i - 1]][Class_2[i]] + // pass the former
						(1 - k[i]) * k[i - 1] * Cost[Class_2[i - 1]][Class_1[i]] // pass the latter
				);
		}

	double MinEnergy = DBL_MAX;

	for (int i = 0; i <= Request; ++i) {
		if (Dynamic[n - 1][i][0] < MinEnergy)
			MinEnergy = Dynamic[n - 1][i][0];
		if (Dynamic[n - 1][i][1] < MinEnergy)
			MinEnergy = Dynamic[n - 1][i][1];
	}

	printf("%.2f\n", MinEnergy);

	return 0;
}
```

