# RMQ 问题

给出一个 n 个元素的数组，给出一个 n 个元素的数组，A<sub>1</sub>, A<sub>2</sub>, ... , A<sub>n</sub>，支持操作 Query(l, r)：计算 min{ A<sub>l</sub>, A<sub>l + 1</sub>, ... , A<sub>r</sub> }。

Tarjan 的 Space-Table 算法，预处理的时间为 N log N。

令 F(i, j) 表示从 i 开始的，长度为 2<sup>j</sup> 的一段元素中的最小值，因此，F(i, j) = min{ F(i, j - 1), F(i + 2<sup>j - 1</sup>), j - 1 }。