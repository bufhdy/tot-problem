inline int Pow(long long a, int b)
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