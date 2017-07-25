#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <bitset>
using namespace std;
#define OutOfRange -1
const int MAXN = 1e6 + 5;

struct Interval {
	int From, To, Value;

	int Half(void)
	{
		return (From + To) / 2;
	}

	Interval(void) :
		From(OutOfRange), To(OutOfRange),
		Value(0) {}
} Tree[MAXN * 4];

int Array[MAXN],
	AsrAnd = INT_MIN, AsrOr = 0;

int Left(int x)
{
	return 2 * x;
}

int Right(int x)
{
	return 2 * x + 1;
}

void Build(int Current, int From, int To)
{
	
	Tree[Current].From = From;
	Tree[Current].To = To;

	if (From == To) {
		Tree[Current].Value = Array[From];
		return;
	}

	int Half = Tree[Current].Half();

	Build(Left(Current), From, Half);
	Build(Right(Current), Half + 1, To);

	Tree[Current].Value =
		Tree[Left(Current)].Value & 
			Tree[Right(Current)].Value;
}

int Temp = INT_MAX;
void QryAnd(int Current, int From, int To)
{
	if (Tree[Current].From == From &&
		Tree[Current].To == To) {
		Temp &= Tree[Current].Value; // ?
		return;
	}

	int Half = Tree[Current].Half();

	if (To <= Half)
		QryAnd(Left(Current), From, To);
	else if (From >= Half + 1)
		return QryAnd(Right(Current), From, To);
	else {
		QryAnd(Left(Current), From, Half);
		QryAnd(Right(Current), Half + 1, To);
	}
}

int main(void)
{
#ifndef _DEBUG
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
#endif // !_DEBUG

	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; ++i) {
		cin >> Array[i];
		AsrOr |= Array[i];
		
		// must be the maximun
	}

	Build(1, 1, n);

	for (int i = 1; i <= n - k + 1; ++i) {
		Temp = INT_MAX;
		
		QryAnd(1, i, i + k - 1);

		if (Temp > AsrAnd)
			AsrAnd = Temp;
	}

	cout << AsrOr << ' ' << AsrAnd << endl;

	return 0;
}