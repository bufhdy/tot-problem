int Count = 0;
stact<int> S;

void StrongConnect(int x)
{
	Graph[x].Count = Graph[x].LowLink = Count;
	++Count;

	S.push(x);

	Vertex *Current = Graph[i].Adjacent;
	while (Current != NULL) {
		if (!Graph[Current->Index].IsVisited) {
			StrongConnect(Current->Index);
			if (Graph[Current->Index].Count > Graph[x].Count)
				Graph[x].LowLink = Graph[Current->Index].Count;
		} else if (Current->Index is in Stack)
			if (Graph[Current->Index].Count > Graph[x].LowLink)
				Graph[x].LowLink = Graph[Current->Index].Count;
	}

	if (Graph[x].LowLink == Graph[x].Count)
		
}

void Tarjan(void)
{
	for (int i = 0; i < Amount; ++i)
		if (Graph[i].Count == Undefined)
			StrongConnect(i);
}