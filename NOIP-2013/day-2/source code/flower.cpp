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
const int MAXN = 100005;

int Height[MAXN];

enum Status {
	Begin, Peak, Trough
};

int main(void)
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; ++i)
		cin >> Height[i];

	int Count = 1, Status = Begin;
	// the first must be counted
	for (int i = 2; i <= n; ++i) {
		if (Height[i] > Height[i - 1]) // find peak
			if (Status != Peak) {
				++Count;
				Status = Peak;
			}
		if (Height[i] < Height[i - 1]) // find trough
			if (Status != Trough) {
				++Count;
				Status = Trough;
			}
	}

	cout << Count << endl;

	return 0;
}