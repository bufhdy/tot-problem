# circle

We use *fast power* to compute large positive integer of a number.

Take 10<sup>11</sup> for instance, it can be rewrite in the form of 10<sup>2<sup>0</sup> + 2<sup>1</sup> + 2<sup>3</sup></sup>, and it's actually 1011 in binary notation.

So we may write like:

```c++
long long Answer = 1, Temp = 10;
while (k) { // 10 ^ k
	if (k & 1) // to tell whether the 0-digit is 0 or 1 
		Answer = (Answer * Temp) % Amount;
		// if it's 1 do the calculation else skip
	k >>= 1;
	Temp = ((Temp % Amount) * (Temp % Amount)) % Amount; // put on
}
```

In a normal situation, it's accepted truth below:

```
a * b % c = (a % c) * (b % c) % c
```

There's whole code:

```c++
#include <bits/stdc++.h>
using namespace std;

int main(void)
{
	long long Amount, To, k, x, Answer = 1, Temp = 10;
	cin >> Amount >> To >> k >> x;

	while (k) {
		if (k & 1)
			Answer = (Answer * Temp) % Amount;
		k >>= 1;
		Temp = ((Temp % Amount) * (Temp % Amount)) % Amount;
	}

	cout << (x + (To * Answer) % Amount) % Amount << endl;
	
	return 0;
}

// a*b mod c = (a mod c)*(b mod c) mod c}
```

