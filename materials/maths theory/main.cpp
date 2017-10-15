#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

/*
	It's the basis of maths theory, 
		all I wanna do is to take the notes and to get more familiar.
 */
struct Main {
	enum Type { A, B };

	int n;

	// Eratoshenes()
	bool IsNoPrime[MAXN];
	void Eratoshenes(Type x)
	{
		memset(IsNoPrime, false, sizeof IsNoPrime);
		if (x == A)
			for (int i = 2; i <= n; ++i)
				for (int j = i * 2; j <= n; j += i)
					IsNoPrime[j] = true;
		else { // better algorithm
			int m = sqrt(n + 0.5);
			for (int i = 2; i <= m; ++i) // i <= m is different
				for (int j = i * i; j <= n; j += i) // j = i * i is different
					IsNoPrime[j] = true;
		}
	}

	// Gcd(), Lcm() and GcdEx()
	int Gcd(int a, int b)
	{
		return b == 0 ? a : Gcd(b, a % b);
	}

	int Lcm(int a, int b)
	{
		return a * b / Gcd(a, b);
	}

	void GcdEx(int a, int b,
		int &d, int &x, int &y)
	{
		if (b == 0) { d = a; x = 1; y = 0; }
		else {
			GcdEx(b, a % b, d, y, x); // exchange at 2 places
			y -= x * (a / b); // get exchanged first and then do minus
		}
	}

	/*
		mod rules:
			(a + b) % n == (a % n + b % n) % n;
			int((long long)a * b % n) == 
				int((long long)a % n * b % n % n);
			(a - b) % n == (a % n - b % n + n) % n;
	 */
	// BigIntMod(): solve n % m. n <= 1e100, m <= 1e9
	int BigIntMod(char n[], int Lgt, int m)
	{
		int Answer = 0;
		for (int i = 0; i < Lgt; ++i)
			Answer = int(((long long)
				Answer * 10 + n[i] - '0') % m);
		return Answer;
	}

	// PowerMod(): solve a^n % m. a, n, m <= 1e9
	int PowerMod(int a, int n, int m)
	{
		if (n == 0) return 1;

		long long Part = PowerMod(a, n / 2, m);

		return Part * Part % m * (n % 2 ? a : 1) % m;
	}

	// CalculateC()
	int C[MAXN][MAXN];
	void CalculateC(int n)
	{
		memset(C, 0, sizeof(C));
		
		C[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			C[i][0] = C[i][i] = 1;

			for (int j = 1; j < i; ++j)
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}

	// CalculateC_n()
	int C_n[MAXN];
	void CalculateC_n(int n)
	{
		C_n[0] = 1;
		for (int i = 1; i <= n; ++i)
			C_n[i] = C_n[i - 1] * (n - i + 1) / i;
	}

	
	Main(void) : IsNoPrime()
	// initialise the IsNoPrime array with false
	{
		/*
			an example of Eratoshenes():

			n = 100;
			Eratoshenes(B);
			for (int i = 2; i <= 100; ++i)
				if (!IsNoPrime[i])
					cout << i << endl;
		 */

		/*
			an example of BigIntMod() and PowerMod():

			char n[10] = "268492";
			cout << BigIntMod(n, strlen(n), 45) << endl;

			cout << PowerMod(2, 10, 3) << endl;
		 */

		/*		
			an example of CalculateC():

			CalculateC(10);

			for (int i = 0; i <= 10; ++i) {
				for (int j = 0; j <= 10; ++j) {
					cout << C[i][j] << ' ';
					if (C[i][j] == 0) break;
				}

				puts("");
			}
			
			an example of CalulateC_n():

			CalculateC_n(10);

			for (int i = 0; i <= 10; ++i)
				cout << C_n[i] << ' ';

		 */

		
	}	
};


int main(void)
{
	delete new Main();

	return 0;
}