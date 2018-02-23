inline int Pow(long long a, int b)
// 1 <= a, b, MOD <= 10^9
// O(log b)
{
	long long Ans = 1;
	while (b) {
		if (b & 1)
			Ans = Ans * a % MOD;
		
		a = a * a % MOD;
		b >>= 1;
	}
	
	return Ans;
}

inline long long Mul(long long a, long long b)
// 1 <= a, b, MOD <= 10^18
// O(log b)
{
	long long Ans = 0;
	while (b) {
		if (b & 1)
			Ans = (Ans + a) % MOD;
		
		a = a * 2 % MOD;
		b >>= 1;
	}
	
	return Ans;
}