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

const int Score[5][5] = {
    { 0, 0, 1, 1, 0 },
    { 1, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 1 },
    { 0, 0, 1, 0, 1 },
    { 1, 1, 0, 0, 0 }
}; // Score[a][b] means a to b

int main(void)
{
#ifndef LOCAL
	freopen("rps.in", "r", stdin);
	freopen("rps.out", "w", stdout);
#endif

	int N, N_A, N_B;
    int Array_A[205], Array_B[205];

    cin >> N >> N_A >> N_B;

    for (int i = 0; i < N_A; ++i)
		cin >> Array_A[i];

    for (int i = 0; i < N_B; ++i)
		cin >> Array_B[i];

	int Score_A = 0, Score_B = 0;
    for (int i = 0; i < N; ++i) {
		Score_A += Score[Array_A[i % N_A]][Array_B[i % N_B]];
		Score_B += Score[Array_B[i % N_B]][Array_A[i % N_A]];
    }

	cout << Score_A << ' ' << Score_B;

    return 0;
}
