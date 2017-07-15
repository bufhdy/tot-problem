#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <string>
using namespace std;
const int MAXN = 1000005;

int Array[MAXN];

int main(void)
{
#ifndef LOCAL
	freopen("equation.in", "r", stdin);
	freopen("equation.out", "w", stdout);
#endif // LOCAL

    int n, m;
    cin >> n >> m;

    if (n == 2) {
        for (int i = 0; i <= n; ++i)
			cin >> Array[i];

		queue<int> Answer;

        for (int i = 1; i <= m; ++i) {
			int Sum = 0;

			for (int j = 0; j <= n; ++j)
				Sum += Array[j] * (int)pow(i, j);

			if (Sum == 0) Answer.push(i);
		}

        cout << Answer.size() << endl;

        while(!Answer.empty()) {
            cout << Answer.front() << endl;
            Answer.pop();
        }
    }

	return 0;
}
