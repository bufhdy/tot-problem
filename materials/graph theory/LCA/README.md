# 最近公共祖先

## 一、定义

最近公共祖先（lowest common ancestor，LCA）是指在有根图中同时拥有 x 和 y 作为后代的最深的节点，如图。

![LCA](https://raw.githubusercontent.com/bufhdy/tot-problem/master/materials/LCA/image/lca_1.png)

<br />

## 二、实现

首先声明两个数组：

```c++
int Deepth[MAXN], Ancestor[MAXN][20];
	// Deepth[i] 表示 i 在数中的深度，根节点为 -1
	// Ancestor[i][k] 表示 i 的 2^k 倍祖先节点
```

进行初始化：

```c++
void SchInitialise(int Node) // 递归初始化
{
	Vertex *Current = Graph[Node].Head;
	while (Current != NULL) {
		if (Deepth[Current->Index] == Unknown) {
			Deepth[Current->Index] = Deepth[Node] + 1;
			Ancestor[Current->Index][0] = Node;

			SchInitialise(Current->Index);
		}

		Current = Current->Adjacent;
	}
}

void Initialise(int Root)
{
	memset(Deepth, Unknown, sizeof(Deepth)); // 深度初始为未知

	SchInitialise(Root); // 从根节点开始递归

	for (int Level = 1; (1 << Level) <= n; ++Level)
		for (int i = 1; i <= n; ++i)
			Ancestor[i][Level] =
			Ancestor[
				Ancestor[i][Level - 1]
			][Level - 1]; // 走了两段 2^(Level - 1) 的路程
}
```

求 LCA：

```c++
int LCA(int x, int y)
{
	if (Deepth[x] < Deepth[y]) // 保证 x 深度更大
		swap(x, y);

	int k = 0;
	while ((1 << k) < Deepth[x]) ++k; // 使 2^k >= Deepth[x]

	for (int i = k; i >= 0; --i)
		if (Deepth[x] - (1 << i) >= Deepth[y])
			x = Ancestor[x][i]; // 步步接近

	if (x == y)
		return x;

	for (int i = k; i >= 0; --i)
		if (Ancestor[x][i] != Ancestor[y][i]) {
			x = Ancestor[x][i];
			y = Ancestor[y][i];
		}

	return Ancestor[x][0];
}
```

关于建树方面：

```c++
struct VertexHead : Vertex {
	int Indegree;

	VertexHead(void) : Indegree(0) {}
} Graph[MAXN]; // 保存入度信息，找到根节点（入度为 0）
```

建树在主函数中的代码：

```c++
for (int i = 1; i < n; ++i) {
	int From, To;
	cin >> From >> To;

	Graph[From].Grow(To);
	++Graph[To].Indegree;
}

for (int i = 1; i <= n; ++i)
	if (Graph[i].Indegree == 0) {
		Initialise(i);
		break;
	}
```

