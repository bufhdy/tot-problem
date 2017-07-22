# Kruskal

## 一、最小生成树

最小生成树（Minimum Spanning Tree, MST），为图的生成树中，边权最小的生成树。

结论：**最小生成树中最大边一定是所有生成树的最大变中最小的**。

次小生成树：对于最小生成树在图的每条边，删除某一边，得到 n - 1 棵树，其中最小的一棵为次小生成树。

极差最小生成树……待补。

<br />

## 二、Kruskal 算法

定义赋权无向图 G 的边集合为 E，接着我们定义最小生成树的边集为 T，初始 T = Ø。

过程：

1. 首先将 G 看成一个有 n 棵树的森林，图上每个顶点对应一棵树；
2. 从小到大排序 E；
3. 按边权从小到大的顺序遍历每条边 e = (u, v)，记 u，v 所在的数 T<sub>u</sub>，T<sub>v</sub>。如果 T<sub>u</sub> ≠ T<sub>v</sub>，则将边 e 加入集合 T，合并 T<sub>u</sub> 和 T<sub>v</sub>。

使用快排的总时间复杂度为 O(|E| log |E|)。

记录边：

```c++
struct Arc {
	int u, v;
	long long Weight;

	const bool operator < (const Arc &x) const
	{
		return Weight < x.Weight;
	}
} Graph[200005];
```

算法过程：

```c++
for (int i = 1; i <= AmtArc; ++i)
	cin >> Graph[i].u >> Graph[i].v >> Graph[i].Weight;

sort(Graph + 1, Graph + AmtArc + 1); // 从小到大排序

Kruskal.Resize(AmtVertex);

int LeftSet = AmtVertex;
long long Sum = 0;
for (int i = 1; i <= AmtArc && LeftSet > 1; ++i) {
// 「LeftSet > 1」最后仅剩一个集合，有 AmtVertex 条边
	int u = Graph[i].u,
		v = Graph[i].v;

	if (Kruskal.Query(u, v)) continue;
	// 如果属于同一集合，由于贪心，已经找到了两点之间的最小边，因此不再计算
	else {
		Kruskal.Merge(u, v); // 合并
		--LeftSet;
		Sum += Graph[i].Weight;
	}
}
```





