# 4. Median of Two Sorted Arrays

A problem solved by classical binary search. Nothing special but watch out for search edge and dealing with special cases.

We can have a split for both arrays (`i, j`), and combine the smaller or bigger numbers from 2 arrays together with the same size. This condition is restrained as `i + j = n + m - i - j`. So what we need to do now is binary-searching `i` to get the answer. Don't worry. We'll get correspoding `j`.

Another condition to considerate is the mininum value of the bigger numbers should be bigger than the maxinum value of the smaller ones. As the two arrays has been sorted, the only 2 comparisions needed is `N1[i - 1] <= N2[j] and N2[j - 1] <= N1[i]`. And this condition can be used as the exit of search.

I want to mention again, think carefully about special cases, which means to reconsider the meanings of all variables (e.g. `median_i(N1, N2, 0, n)`). Eventually you'll get the code right.
