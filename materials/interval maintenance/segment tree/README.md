# 线段树

## 一、概述

线段数是一种二叉树形数据结构，它用以解决在线的范围最值问题。给出一个 n 个元素的数组，A<sub>1</sub>, A<sub>2</sub>, ... , A<sub>n</sub> ，支持以下两种操作：

1. Edit(x, v)：把 A<sub>x</sub> 修改为 v；
2. QryMaxMin(f, t)：计算 min{ A<sub>f</sub>, A<sub>f + 1</sub>, ... , A<sub>t</sub> }。

线段数组是一棵二叉树，每一个**节点表示了一个区间 [a, b]**，对于每一个**非叶节点**，其**左儿子表示的区间为 [a, (a + b) / 2]**，**右儿子表示的区间为 [(a + b) / 2 + 1, b]**。叶子节点的长度为 1，不能够再分，它的个数等于区间的长度，设叶节点的数目为 n，则线段树的总节点数为 2 * n - 1。

根节点对应区间为 [a, b]，那么它的**深度为 ceil(log2(b - a + 1) + 1)**，

<br />

## 二、基本操作

首先是类型的构建，使用二叉完全树的数组方式构建，一般 MAXN * 4 就够了：

```c++
struct Interval {
	int From, To;
	int MinValue, MaxValue;

	int Half(void)
	{
		return (From + To) / 2;
	}

	Interval(void) :
		From(OutOfRange), To(OutOfRange),
		MaxValue(INT_MIN), MinValue(INT_MAX) {}
} Tree[MAXN * 4];
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
		Build(Left(Current), From, Tree[Current].Half());
		Build(Right(Current), Tree[Current].Half() + 1, To);
	}
}
```

插入／编辑操作：

```c++
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

	if (Index <= Tree[Current].Half())
		Edit(Left(Current), Index, Value);
	else Edit(Right(Current), Index, Value);
}
```

查询操作，包括最大值和最小值：

```c++
void QryMaxMin(int Current, int From, int To)
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

	int Half = Tree[Current].Half();
	if (To <= Half)
		QryMaxMin(Left(Current), From, To);
	else if (From > Half)
		QryMaxMin(Right(Current), From, To);
	else {
		QryMaxMin(Left(Current), From, Half);
		QryMaxMin(Right(Current), Half + 1, To);
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

关于线段树的更多操作（动态算法）：

1. Add(f, t, v)：将 A<sub>f</sub>, A<sub>f + 1</sub>, ... , A<sub>t</sub> 增加 v；
2. QrySum(f, t), 计算 A<sub>f</sub> + A<sub>f + 1</sub> + ... + A<sub>t</sub>。

设计线段树结构，一般保存的个数是 MAXN * 2：

```c++
struct Interval {
	int From, To;
	long long Sum, Extra;
	// Sum 保存原来的和，Extra 保存增加的值

	Interval *Left, *Right;

	int Half(void)
	{
		return (From + To) / 2;
	}

	int Length(void) // 区间长度
	{
		return To - From + 1;
	} 

	Interval(void) :
		From(OutOfRange), To(OutOfRange),
		Sum(0), Extra(0),
		Left(NULL), Right(NULL) {}
} Tree[MAXN * 2];
```

使用 for 循环建树：

```c++
int CrtIndex = 0; // 连续保存
void Build(Interval *Current, int From, int To)
{
	Current->From = From;
	Current->To = To;

	if (From != To) {
		Current->Left = Tree + ++CrtIndex; // &Tree[++CrtIndex]
		Current->Right = Tree + ++CrtIndex;

		Build(Current->Left, From, Current->Half());
		Build(Current->Right, Current->Half() + 1, To);
	}
}
```

插入值：

```c++
void Insert(Interval *Current, int Index, int Value)
{
	if (Current->From == Index && Current->To == Index) {
	// 叶节点
		Current->Sum = Value;
		return;
	}

	Current->Sum += Value; // 注意不要写成「=」

	if (Index <= Current->Half())
		Insert(Current->Left, Index, Value);
	else Insert(Current->Right, Index, Value);
}
```

以上，在 main() 中的代码为：

```c++
Build(Tree, 1, n); // 直接写 Tree 为根节点

for (int i = 1; i <= n; ++i) {
	int x;
	cin >> x;
		
	Insert(Tree, i, x);
}
```

增加操作：

```c++
void Add(Interval *Current, int From, int To, long long Value)
{
	if (Current->From == From && Current->To == To) {
	// 刚好范围相同，更新 Extra 值
		Current->Extra += Value;
		return;
	}

	Current->Sum += (To - From + 1) * Value;
	// 增加的范围要小一些，更新 Sum，注意不要写成「=」
	
	int Half = Current->Half();
	if (To <= Half) // 增加的范围在左半边
		Add(Current->Left, From, To, Value);
	else if (From >= Half + 1) // 增加的范围在右半边
		Add(Current->Right, From, To, Value);
	else { // 增加的范围在中间，分别添加
		Add(Current->Left, From, Half, Value);
		Add(Current->Right, Half + 1, To, Value);
	}
}
```

查询操作：

```c++
long long QrySum(Interval *Current, int From, int To)
{
	if (Current->From == From && Current->To == To)
	//  刚好范围相同，Extra 和 Sum 值全部返回
		return (long long)Current->Length() * Current->Extra + 
			Current->Sum;

	// 将 Extra 的值转移到 Sum，注意「+=」
	Current->Sum += Current->Length() * Current->Extra;
	int Half = Current->Half();
	Add(Current->Left, Current->From, Half, Current->Extra);
	Add(Current->Right, Half + 1, Current->To, Current->Extra);
	Current->Extra = 0;
	
	if (To <= Half) // 增加的范围在左半边
		return QrySum(Current->Left, From, To);
	else if (From >= Half + 1) // 增加的范围在右半边
		return QrySum(Current->Right, From, To);
	else // 增加的范围在中间，分别查询
		return QrySum(Current->Left, From, Half) +
			QrySum(Current->Right, Half + 1, To);
}
```

<br />

## 四、离散化

以后再补 😛。

题目：

1. [POJ 2528 Mayor's posters](http://poj.org/problem?id=2528)
2. [POJ 1151 Atlantis](http://poj.org/problem?id=1151)