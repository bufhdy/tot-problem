# RMQ 问题

给出一个 n 个元素的数组，A<sub>1</sub>, A<sub>2</sub>, ... , A<sub>N</sub> ，支持操作 Query(L, R)，计算 min{ A<sub>L</sub>, A<sub>L</sub> + 1, ... , A<sub>R</sub> }。

Tarjan 的 Space-Table 算法，预处理的时间为 N log N。

令 d(i, j) 表示从 i 开始的，长度为 2^j 的一段元素中的最小值，因此，d(i, j) = min{ d(i, j - 1), d(i + 2 ^ (j - 1)), j - 1 }。