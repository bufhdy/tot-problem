# flower

The first one in Height must be counted.

To prove this, set an array from [1] to [k], and we'll choose one, Array[i], in that range as the first one. However, if Array[i] > Array[1], Array[1] can be the trough because there's no more element before Array[1]; also, Array[1] is a peak if Array[i] < Array[1]. And if Array[1] = Array[i], we can choose whatever we like, so just choose Array[1].

Define enumerated Status: Begin, Peak and Trough. Set Status as Begin at first, and circlulate finding peak and Trough by changing its status.

Code:

```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int Height[MAXN];

enum Status {
	Begin, Peak, Trough
};

int main(void)
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; ++i)
		cin >> Height[i];

	int Count = 1, Status = Begin;
	// the first must be counted
	for (int i = 2; i <= n; ++i) {
		if (Height[i] > Height[i - 1]) // find peak
			if (Status != Peak) {
				++Count;
				Status = Peak;
			}
		if (Height[i] < Height[i - 1]) // find trough
			if (Status != Trough) {
				++Count;
				Status = Trough;
			}
	}

	cout << Count << endl;

	return 0;
}
```

