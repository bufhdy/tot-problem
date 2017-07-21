# 线段树

## 一、概述

线段数是一种二叉树形数据结构，它用以解决在线的范围最值问题。给出一个 n 个元素的数组，A<sub>1</sub>, A<sub>2</sub>, ... , A<sub>n</sub> ，支持以下两种：

1. Update(x, v)：把 A<sub>x</sub> 修改为 v；
2. Query(l, r)：计算 min{ A<sub>l</sub>, A<sub>l + 1</sub>, ... , A<sub>r</sub> }。

线段数组是一棵二叉树，每一个**节点表示了一个区间 [a, b]**，对于每一个**非叶节点**，其**左儿子表示的区间为 [a, (a + b) / 2]**，**右儿子表示的区间为 [(a + b) / 2 + 1, b]**。叶子节点的长度为 1，不能够再分，它的个数等于区间的长度，设叶节点的数目为 n，则线段树的总节点数为 2 * n - 1。

根节点对应区间为 [a, b]，那么它的**深度为 ceil(log2(b - a + 1) + 1)**，

<br />

## 二、基本操作

首先是类型的构建，使用二叉完全树的数组方式构建：

```c++
struct Segment {
	int From, To;
	int MinValue, MaxValue;

	int Middle(void)
	{
		return (From + To) / 2;
	}

	Segment(void) :
		From(OutOfRange), To(OutOfRange),
		MaxValue(INT_MIN), MinValue(INT_MAX) {}
} Tree[MAXN];
```

定义两个函数，查找左节点和右节点的下标：

```c++
int Left(int x)
{
	return 2 * x;
}

int Right(int x)
{
	return 2 * x + 1;
}
```

建树操作：

```c++
void Build(int Current, int From, int To)
{
	Tree[Current].From = From;
	Tree[Current].To = To;

	if (From != To) { // 递归进行
		Build(Left(Current), From, Tree[Current].Middle());
		Build(Right(Current), Tree[Current].Middle() + 1, To);
	}
}
```

编辑操作：

```c++
// Current for construction, Index for judgement
void Edit(int Current, int Index, int Value)
{
	if (Tree[Current].From == Tree[Current].To) {
		Tree[Current].MinValue = Tree[Current].MaxValue = Value;
		return;
	}

	if (Value < Tree[Current].MinValue)
		Tree[Current].MinValue = Value;

	if (Value > Tree[Current].MaxValue)
		Tree[Current].MaxValue = Value;

	if (Index <= Tree[Current].Middle())
		Edit(Left(Current), Index, Value);
	else Edit(Right(Current), Index, Value);
}
```

查询操作，包括最大值和最小值：

```c++
void Query(int Current, int From, int To)
{
	if (Tree[Current].MinValue >= CrtMinValue &&
		Tree[Current].MaxValue <= CrtMaxValue)
		return;

	if (Tree[Current].From == From &&
		Tree[Current].To == To) {
		if (Tree[Current].MinValue < CrtMinValue)
			CrtMinValue = Tree[Current].MinValue;
		if (Tree[Current].MaxValue > CrtMaxValue)
			CrtMaxValue = Tree[Current].MaxValue;
		
		return;
	}

	int Middle = Tree[Current].Middle();
	if (To <= Middle)
		Query(Left(Current), From, To);
	else if (From > Middle)
		Query(Right(Current), From, To);
	else {
		Query(Left(Current), From, Middle);
		Query(Right(Current), Middle + 1, To);
	}
}
```

记得每次查询时更改最值初值：

```c++
CrtMaxValue = INT_MIN;
CrtMinValue = INT_MAX;
```

<br />

## 三、进阶操作

```c++
struct Segment {
	int From, To;
	long long EstSum, Delta;
	// EstSum + Delta * (To - From + 1)

	Segment *Left, *Right;

	int Middle(void)
	{
		return (From + To) / 2;
	}

	Segment(void) :
		From(OutOfRange), To(OutOfRange),
		EstSum(0), Delta(0),
		Left(NULL), Right(NULL) {}
} Tree[MAXN * 2];

int CrtIndex = 0;
void Build(Segment *Current, int From, int To)
{
	Current->From = From;
	Current->To = To;

	if (From != To) {
		Current->Left = Tree + ++CrtIndex;
		Current->Right = Tree + ++CrtIndex;

		Build(Current->Left, From, Current->Middle());
		Build(Current->Right, Current->Middle() + 1, To);
	}
}

// Current for construction, Index for judgement
void Edit(Segment *Current, int Index, int Value)
{
	if (Current->From == Index && Current->To == Index) {
		Current->EstSum = Value;
		return;
	}

	Current->EstSum += Value;

	if (Index <= Current->Middle())
		Edit(Current->Left, Index, Value);
	else Edit(Current->Right, Index, Value);
}
```



