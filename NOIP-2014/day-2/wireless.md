# wireless

## reflection

I would like to use `multiset`, and there's no need to memorise the declaring code which is from big to small(s2b is default), just use this to find the biggest with iterator:

```c++
multiset<int>::iterator it = MaxCount.end();
--it;
```

We have also got the `count()`:

```c++
cout << MaxCount.count(*it) << ' ' <<
	*it << endl;
```
