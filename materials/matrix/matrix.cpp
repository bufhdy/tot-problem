struct Matrix {
	int Row, Column;
	vector<vector<int> > Map;

	void Assign(void)
	{
        for (int i = 0; i < Row; ++i)
        	for (int j = 0; j < Column; ++j)
        		cin >> Map[i][j];
	}

	void Print(void)
	{
		for (int i = 0; i < Row; ++i) {
        	for (int j = 0; j < Column; ++j)
        		cout << Map[i][j] << ' ';
			puts("");
		}
	}

	// multiply
	Matrix operator * (Matrix &x)
	{
		// assume that they can be multiplied (Column == x.Row)

		Matrix y(Row, x.Column);
		int n = x.Row;

		for (int i = 0; i < y.Row; ++i)
			for (int j = 0; j < y.Column; ++j) {
                y.Map[i][j] = 0;
                for (int k = 0; k < n; ++k)
                	y.Map[i][j] += Map[i][k] * x.Map[k][j];
			}

		return y;
	}

	// power
	void Power(int n)
	{
		// assume that it can ne powered (Row == Column)

		Matrix &x = *this,
			y(Row, Column);

		for (int i = 0; i < Row; ++i)
			y.Map[i][i] = 1;

		while (n) {
			if (n & 1)
				y = x * y;
			n >>= 1;
			x = x * x;
		}

		x = y;
	}

	Matrix(int Row, int Column) {
		this->Row = Row;
		this->Column = Column;

		Map.resize(Row);

		for (int i = 0; i < Row; ++i)
			Map[i].resize(Column);
	}
};