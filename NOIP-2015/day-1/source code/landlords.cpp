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
using namespace std;
const int MAXN = 20;

int Stock[MAXN], Count;

void Search(int Current[], int Extra)
{
	if (Extra >= Count) return;

	int Out = Extra,
		Left[5] = { 0 };
	for (int i = 0; i <= 13; ++i)
		++Left[Current[i]];

	while (Left[2] >= 2 && Left[4] >= 1) // A A A A B B C C
		Left[2] -= 2, --Left[4], ++Out;

	while (Left[2] >= 1 && Left[3] >= 1) // A A A B B
		--Left[2], --Left[3], ++Out;

	while (Left[1] >= 2 && Left[4] >= 1) // A A A A B C
		Left[1] -= 2, --Left[4], ++Out;

	while (Left[2] >= 1 && Left[4] >= 1) // A A A A B B
		--Left[2], --Left[4], ++Out;

	while (Left[1] >= 1 && Left[3] >= 1) // A A A B
		--Left[1], --Left[3], ++Out;

	for (int i = 1; i <= 4; ++i) // single
		Out += Left[i];

	if (Out < Count)
		Count = Out;

	for (int i = 2; i <= 11; ++i) { // A A A B B B C C C
		int Interval = i;
		while (Current[Interval] >= 3) Interval++;
		if (Interval - i <= 1) continue;
		--Interval;

		for (int j = i + 1; j <= Interval; ++j) {
			for (int k = i; k <= j; ++k)
				Current[k] -= 3;

			Search(Current, Extra + 1);

			for (int k = i; k <= j; ++k)
				Current[k] += 3;
		}
	}

	for (int i = 2; i <= 11; ++i) { // A A B B C C
		int Interval = i;
		while (Current[Interval] >= 2) Interval++;
		if (Interval - i <= 2) continue;
		--Interval;

		for (int j = i + 2; j <= Interval; ++j) {
			for (int k = i; k <= j; ++k)
				Current[k] -= 2;

			Search(Current, Extra + 1);

			for (int k = i; k <= j; ++k)
				Current[k] += 2;
		}
	}


	for (int i = 2; i <= 9; ++i) { // A B C D E
		int Interval = i;
		while (Current[Interval] >= 1) Interval++;
		if (Interval - i <= 4) continue;
		--Interval;

		for (int j = i + 4; j <= Interval; ++j) {
			for (int k = i; k <= j; ++k)
				--Current[k];

			Search(Current, Extra + 1);

			for (int k = i; k <= j; ++k)
				++Current[k];
		}
	}
}

int main(void)
{
	int Case, Card;
	cin >> Case >> Card;

	while (Case--) {
		memset(Stock, 0, sizeof(Stock));
		Count = INT_MAX;

		for (int i = 1; i <= Card; ++i) {
			int Number, Type;
			cin >> Number >> Type;

			if (Number == 1) Number = 13; // J Q K A
			else if (Number > 1) --Number; // except joker
			else Number = 0;

			++Stock[Number];
		}

		Search(Stock, 0);

		cout << Count << endl;
	}

	return 0;
}