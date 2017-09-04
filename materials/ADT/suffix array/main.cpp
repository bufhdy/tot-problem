#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

struct Main {
	char String[MAXN];
	int n, Limit,
		Sa[MAXN], Temp[MAXN], Temp_2[MAXN],
		Bucket[MAXN];

	void Input(void)
	{
		scanf("%s", String);
		n = strlen(String);
		Limit = CHAR_MAX + 1;
	}

	void Output(void)
	{
		for (int i = 0; i < n; ++i)
			printf("%d ", Sa[i] + 1);
		puts("");
	}

	inline void Empty(void)
	{
		memset(Bucket, 0, sizeof Bucket);
	}

	Main(void)
	{
		Input();

		int *First = Temp, *Second = Temp_2;
		
		Empty();
		for (int i = 0; i < n; ++i) // 装、和、反
			++Bucket[First[i] = String[i]];
		for (int i = 1; i < Limit; ++i)
			Bucket[i] += Bucket[i - 1];
		for (int i = n - 1; i >= 0; --i)
			Sa[--Bucket[First[i]]] = i;

		for (int k = 1; k <= n; k <<= 1) { // 倍增
			int Pst = 0;

			for (int i = n - k; i <= n - 1; ++i) // 循环交换
				Second[Pst++] = i;
			for (int i = 0; i < n; ++i)
				if (Sa[i] >= k)
					Second[Pst++] = Sa[i] - k;

			Empty();
			for (int i = 0; i < n; ++i) // 装、和、反
				++Bucket[First[Second[i]]];
			for (int i = 1; i < Limit; ++i)
				Bucket[i] += Bucket[i - 1];
			for (int i = n - 1; i >= 0; --i)
				Sa[--Bucket[First[Second[i]]]] = Second[i];

			swap(First, Second);

			Pst = 1;
			First[Sa[0]] = 0;
			for (int i = 1; i < n; ++i)
				First[Sa[i]] = (Second[Sa[i - 1]] >= Second[Sa[i]] &&
					Second[Sa[i - 1] + k] == Second[Sa[i] + k]) ? Pst - 1 : Pst++;

			if (Pst >= n) break;
			Limit = Pst;
		}

		Output();
	}
};

int main(void)
{
	delete new Main();

	return 0;
}
