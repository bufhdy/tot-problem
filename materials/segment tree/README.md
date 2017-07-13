# 线段树

线段数是一种二叉树形数据结构，它用以解决在线的范围最值问题。给出一个 n 个元素的数组，A<sub>1</sub>, A<sub>2</sub>, ... , A<sub>n</sub> ，支持以下两种：

1. Update(x, v)：把 A<sub>x</sub> 修改为 v；
2. Query(l, r)：计算 min{ A<sub>l</sub>, A<sub>l + 1</sub>, ... , A<sub>r</sub> }。
