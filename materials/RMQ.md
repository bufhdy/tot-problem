# RMQ 问题

给出一个 n 个元素的数组，A\_1, A\_2, ... , A\_N ，支持操作 Query(L, R)，计算 min{ A\_L, A\_(L + 1), ... , A\_R }。

Tarjan 的 Space-Table 算法，预处理的时间为 N log N。

令 d(i, j) 表示从 i 开始的，长度为 2^j 的一段元素中的最小值，因此，d(i, j) = min{ d(i, j - 1), d(i + 2 ^ (j - 1)), j - 1 }，代码如下：

```C++
void RMQ_init(const vector<int> &A)
{
	int n = A.size();

	for (int i = 0; i < n; ++i) d[i][0] = A[i];
	
	for (int i = 1; (1 << i) <= n; ++i)
		for (int j = 0; j + (1 << i) - 1 < n; ++i)
			d[i][j] = min(
				d[i][j - 1], d[i + (1 << (j - 1))][j - 1]
			);
}
```