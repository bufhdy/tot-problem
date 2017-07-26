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
const int MAXN = 1e5 + 5;

char Name[MAXN][15];
bitset<MAXN> IsOutside;

int main(void)
{
	int n, Query;
	cin >> n >> Query;

	for (int i = 0; i < n; ++i) {
		bool Temp;
		cin >> Temp >> Name[i];
		IsOutside[i] = Temp;
	}
	
	long long Position = 0;
	while (Query--) {
		bool IsRight;
		long long Turn;
		cin >> IsRight >> Turn;

		if (!IsRight)
			if (IsOutside[Position] == true)
				Position = (Position + Turn) % n;
			else Position = ((Position - Turn) % n + n) % n; // 排除负数的干扰
		else 
			if (IsOutside[Position] == true)
				Position = ((Position - Turn) % n + n) % n;
			else Position = (Position + Turn) % n;
	}

	cout << Name[Position] << endl;

	return 0;
}