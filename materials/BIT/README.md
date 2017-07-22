# 树状数组

动态连续和查询问题。给定一个 Amount 个元素的数组 A<sub>1</sub>, A<sub>2</sub>, ... , A<sub>n</sub>，对其进行操作：

1. 让 A<sub>i</sub> 增加 Delta；
2. 计算 A<sub>i</sub> + A<sub>(i + 1)</sub> + ... + A<sub>j</sub>。

定义一个用于计算的函数 LowBit(x)，它返回 x 二进制右数第一位 1，包括 1 右边的 0 位，所对应的数值，这个函数的实现：

```c++
int LowBit(int x)
{
	return x & -x;
}
```

两个操作：

```c++
void Edit(int x, int Delta)
{
	for (int i = x; i <= Amount; i += LowBit(i))
		BIT[i] += Delta;
}

int SumFromBegin(int x)
{
	int Sum = 0;

	for (int i = x; i > 0; i -= LowBit(i))
		Sum += BIT[i];

	return Sum;
}
```

例题参见[火柴排序](https://github.com/bufhdy/tot-problem/blob/master/NOIP-2013/day-1/match.md#match)。