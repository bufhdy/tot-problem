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

