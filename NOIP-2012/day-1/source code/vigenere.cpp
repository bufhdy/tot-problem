#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
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
const int MAXL = 1005;

struct Main {
	char k[MAXL], m[MAXL];
	int kLgt, mLgt,
		Key[105];

	Main(void)
	{
		scanf("%s %s", k, m);

		kLgt = strlen(k);
		mLgt = strlen(m);
		for (int i = 0; i < kLgt; ++i)
			if (k[i] >= 'a')
				Key[i] = k[i] - 'a';
			else
				Key[i] = k[i] - 'A';

		int Cnt = 0;
		while (Cnt < mLgt) {
			char c = m[Cnt] - Key[Cnt % kLgt];
			
			if (c < 'A' || (c < 'a' && m[Cnt] >= 'a'))
				c += 26;
			printf("%c", c);
			
			++Cnt;
		}

		puts("");
	}
};

int main(void)
{
	delete new Main();
	

	return 0;
}