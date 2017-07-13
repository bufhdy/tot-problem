# 最近公共祖先

最近公共祖先（lowest common ancestor，LCA）是指在一个树或者有向无环图中同时拥有 x 和 y 作为后代的最深的节点，如图。

![picture_from_wikipeadia](https://upload.wikimedia.org/wikipedia/commons/9/96/Lowest_common_ancestor.svg)

为了计算树中两个节点 x 和 y 之间的距离，可以分别计算由 x 到根节点和 y 到根节点的距离（图中分别为 4 和 6），两者之和减去最近公共祖先到根节点的距离的两倍（2 * 3）即可得到 x 到 y 的距离。