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

