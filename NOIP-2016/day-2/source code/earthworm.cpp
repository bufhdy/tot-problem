#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
using namespace std;
const int MAXN = 100005,
	MAXM = 7000005;
int Amount, Time, Grow, u, v, t,
	Length[MAXN],
	Store[3][MAXM], Left[3], Right[3];

int MaxIndex(void)
{
	int MaxValue = INT_MIN, CrtIndex = -1;

	for (int i = 0; i < 3; ++i)
		if (Right[i] - Left[i] >= 1 && 
			Store[i][Left[i]] > MaxValue) {
			MaxValue = Store[i][Left[i]];
			
			CrtIndex = i;
		}
	
	return CrtIndex;
}

bool Compare(int x, int y)
{
	return x > y;
}

int main(void)
{
#ifndef  _DEBUG
	freopen("earthworm.in", "r", stdin);
	freopen("earthworm.out", "w", stdout);
#endif // ! _DEBUG

	cin >> Amount >> Time >> Grow >> u >> v >> t;

	for (int i = 0; i < Amount; ++i)
		cin >> Length[i];

	sort(Length, Length + Amount, Compare);

	for (int i = 0; i < Amount; ++i)
		Store[0][i] = Length[i];

	memset(Left, 0, sizeof(Left));
	memset(Right, 0, sizeof(Right));
	Right[0] = Amount;

	int Current, CrtIndex, Temp, CrtLeft, CrtRight;
	for (int i = 0; i < Time; ++i) {
		CrtIndex = MaxIndex();
		Current = Store[CrtIndex][Left[CrtIndex]++];
		Temp = i * Grow;

		if ((i + 1) % t == 0)
			cout << Current + Temp << ' ';
		
		CrtLeft = (long long)(Current + Temp) * u / v;
		CrtRight = (Current + Temp) - CrtLeft;
		CrtLeft -= Temp, CrtRight -= Temp;

		Store[1][Right[1]++] = CrtLeft - Grow;
		Store[2][Right[2]++] = CrtRight - Grow;
	}
	puts("");

	Temp = Time * Grow;
	for (int i = 0; i < Amount + Time; ++i) {
		CrtIndex = MaxIndex();
		Current = Store[CrtIndex][Left[CrtIndex]++];
		
		if ((i + 1) % t == 0)
			cout << Current + Temp << ' ';
	}

	return 0;
}
