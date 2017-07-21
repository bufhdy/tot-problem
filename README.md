# tot problem

This is a repository for algorithm contests, e.g. NOIP, so far.

## Issue

### 1. main() structure

Let me set here blocks of code for starting to write a problem:

```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
using namespace std;
const int MAXN = 1005;

int main(void)
{
#ifndef LOCAL
	freopen("main.in", "r", stdin);
	freopen("main.out", "w", stdout);
#endif // LOCAL

	...

	return 0;
}
```

### 2. I/O Parts

In README.md, when it comes to Input and Output parts, just write code below:

```html
<table>
<tr>
<th>输入样例</th>
<th>输出样例</th>	
</tr>
<tr>
<td valign="top">
...<br />
</td>
<td valign="top">...</td>
</tr>
</table>
```

Remember not to type a new line for HTML code in Markdown, that'll be all.

### 3. Images

They can be updated onto GitHub and just use Markdown or HTML syntax to get the hypertext reference.
