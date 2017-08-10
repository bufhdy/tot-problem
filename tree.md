tree

```c++
stack<int> Index;
for (int i = 1; i <= n; ++i) {
	if (!Index.empty()) {
		int LeftOne = -1;
		while (!Index.empty() &&
			Array[Index.top()] < Array[i]) {
			LeftOne = Index.top();
			Index.pop();
		}
		if (LeftOne == -1) {
			Tree[Index.top()].Right = i;
			Tree[i].Father = Index.top();
		} else {
			Tree[i].Left = LeftOne;
			Tree[LeftOne].Father = i;
		}
	}

	Index.push(i);
	if (Tree[i].Father == 0) Root = i;
}
```

