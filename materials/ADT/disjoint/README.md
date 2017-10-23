# 并查集

若干元素分布在数个不相交的集合内，支持 3 种操作：

1. 合并两个集合；
2. 查询一个元素属于某个集合；
3. 查询两个元素是否属于同一集合。

```c++
struct Disjoint {
	int Ancestor[MAXN],
		Count[MAXN];  // 用以存放集合中元素个数

	int GetAst(int x) {
		if (Ancestor[x] == x) return x;
		else return Ancestor[x] = GetAst(Ancestor[x]);
	}

	bool Query(int x, int y) // 以祖先为集合判等依据
	{
		return GetAst(x) == GetAst(y);
	}

	void Merge(int x, int y) // 将 y 合并到 x
	{
		int xAst = GetAst(x),
			yAst = GetAst(y);

		if (xAst == yAst) // 处于同一集合，无需合并
			return;

		Count[xAst] += Count[yAst];
		Ancestor[yAst] = xAst;
	}

	int AmtElement(int x) // 返回 x 所在集合元素个数
	{
		return Count[GetAst(x)];
	}

	Disjoint(int Amount)
	{
		for (int i = 0; i < Amount; ++i) {
			Ancestor[i] = i; // 初始化，指向自己
			Count[i] = 1; // 元素个数为 1
		}
	}
};
```

另有，多重并查集的题目，[食物链](https://www.luogu.org/problemnew/show/2024)。在此贴出代码：

```c++
struct Main {
	int n, k, Foe, Self, Target,
		Set[MAXN * 3];

	inline void Init(void)
	{
		for (int i = 0; i <= 3 * n; ++i)
			Set[i] = i;
		Foe = 0;
		Self = n;
		Target = 2 * n;
	}

	int GetSet(int x)
	{
		if (Set[x] == x) return x;
		return Set[x] = GetSet(Set[x]);
	}

	inline void Merge(int x, int y)
	{
		int xSet = GetSet(x),
			ySet = GetSet(y);

		Set[xSet] = ySet;
	}

	Main(void)
	{
		scanf("%d %d", &n, &k);

		Init();

		int Cnt = 0;
		while (k--) {
			int Type, x, y;
			scanf("%d %d %d", &Type, &x, &y);

			if (x > n || y > n) {
				++Cnt;
				continue;
			}

			if (Type == 1) {
				if (x == y) continue;

				if (GetSet(x + Target) == GetSet(y + Self) ||
					GetSet(x + Foe) == GetSet(y + Self)) {
					++Cnt;
					continue;
				}

				Merge(x + Foe, y + Foe);
				Merge(x + Self, y + Self);
				Merge(x + Target, y + Target);
			} else {
				if (GetSet(x + Self) == GetSet(y + Self) ||
					GetSet(x + Foe) == GetSet(y + Self)) {
					++Cnt;
					continue;
				}

				Merge(x + Self, y + Foe);
				Merge(x + Target, y + Self);
				Merge(x + Foe, y + Target);
			}
		}

		printf("%d\n", Cnt);
	}
};
```
