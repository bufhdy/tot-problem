void Initialise(vector<int> &Array)
{
	int Length = (int)Array.size();

	for (int i = 0; i < Length; ++i) F[i][0] = Array[i];
	
	for (int j = 1; (1 << j) <= Length; ++j)
		for (int i = 0; i + (1 << j) - 1 < Length; ++i)
			F[i][j] = min(
				F[i][j - 1], F[i + (1 << (j - 1))][j - 1]
			); // mininum of two halves
}

int Query(int Left, int Right)
{
	int i = 0;
	
	while (1 << (i + 1) <= Right - Left + 1) ++i;
	
	return min(
		F[Left][i], F[Right - (1 << i) + 1][i]
	);
}
