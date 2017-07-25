# 欧拉回路

## 一、概念

图 G 中存在一条路径，是它恰好通过 G 中每条边一次，则称其为**欧拉路经（对应半欧拉图）**。若该路径是一个环路，则称为**欧拉回路（对应欧拉图）**。

<br />

## 二、性质

无向图存在欧拉路径的条件：

1. **连通**；
2. **有 0 个（欧拉回路）或 2 个奇顶点（以两个顶点为欧拉路径的端点）**。

有向图存在欧拉路径的条件：

1. **弱连通**；
2. **所有顶点入度和出度相等（欧拉回路）**；
3. **有一个顶点出入度之差为 1，有一个顶点出入度之差为 -1，其余所有顶点入度和出度相等（作为端点）**。

<br />

## 三、无向图欧拉路径

```c++
const int MAX_N = 100;
int mat[MAX_N][MAX_N];
int match[MAX_N];  // 表示顶点剩余的度
int n;  // 顶点个数
void solve(int u) {
    if (match[u] > 0) {
        for (int i = 0; i < n; ++i) {
            if (mat[u][i]) {
                mat[u][i]--;
                mat[i][u]--;
                solve(i);
            }
        }
    }
    cout << "visiting " << u << endl;
}
```

<br />

## 四、有向图欧拉路径

```c++
const int MAX_N = 100;
const int MAX_M = 10000;
int mat[MAX_N][MAX_N];
int match[MAX_N];  // 表示顶点剩余的度
int n;  // 顶点个数
int stk[MAX_M], top = 0;  // 用数组 stk 来模拟一个栈
void solve(int u) {
    if (match[u] > 0) {
        for (int i = 0; i < n; ++i) {
            if (mat[u][i]) {
                mat[u][i]--;
                solve(i);
            }
        }
    }
    stk[top++] = u;  // 将顶点 u 插入栈中
}
```

<br />

## 五、判断连通

因为是弱连通，因此将有向图转化为无向图进行遍历，当然可以用邻接表进行重构：

```c++
bool IsVisited[MAXN] = { false };
int Count = 1;
void Search(int Start)
{
	queue<int> Travel;
	Travel.push(Start);
	IsVisited[Start] = true;

	while (!Travel.empty()) {
		int From = Travel.front();
		Travel.pop();

		for (int i = 1; i <= VertexAmount; ++i) {
			if (IsConnected[From][i] && 
				!IsVisited[i]) {
				IsVisited[i] = true;
				++Count;

				Travel.push(i);
			}
		}
	}
}
```

如果 Count = VertexAmount，即为连通的。