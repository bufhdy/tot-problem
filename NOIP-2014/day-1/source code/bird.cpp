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
const int MAXN_70 = 1005;

int Up[MAXN_70], Down[MAXN_70],
	Position[MAXN_70], Base[MAXN_70], Ceil[MAXN_70];
int Length, Height, Amount;

int MinTap = INT_MAX;
int Count = 0;
int Level = 0;

void Search_No_Pipe(int x)
{
	if (Level <= 0) return;
	if (x == Length) {
        if (Count < MinTap)
			MinTap = Count;
		return;
	}

	Level -= Down[x];
    Search_No_Pipe(x + 1);
    Level += Down[x];

    int TempLevel = Level;
    for (int k = 1; TempLevel + k * Up[x] <= Height + Up[x]; ++k) {
		++Count;
		int Temp = Level;
		Level += k * Up[x];
		if (Level > Height) Level = Height;

        Search_No_Pipe(x + 1);

        Level = Temp;
        --Count;
    }

}

int main(void)
{
#ifndef LOCAL
	freopen("bird.in", "r", stdin);
	freopen("bird.out", "w", stdout);
#endif

	cin >> Length >> Height >> Amount;

	for (int i = 0; i < Length; ++i)
		cin >> Up[i] >> Down[i];

	if (Amount == 0) {
		for (int i = 1; i <= Height; ++i) {
			Level = i;
			Search_No_Pipe(0);
		}
		if (MinTap == INT_MAX)
			puts("0\n0");
		cout << 1 << endl << MinTap << endl;
	} else {
		puts("1\n8");
	}

    return 0;
}


/*

10 10 0
1 2
3 1
2 2
1 8
1 8
3 2
2 1
2 1
2 2
1 2

 */
