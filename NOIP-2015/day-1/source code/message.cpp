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
const int MAXN = 200005;

int To[MAXN], Indegree[MAXN];
bool IsVisited[MAXN];

int main(void)
{
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; ++i) {
        cin >> To[i];
        ++Indegree[To[i]];
    }
    
    stack<int> Travel; 
    for (int i = 1; i <= n; ++i)
        if (Indegree[i] == 0) {
            Travel.push(i);
            IsVisted[i] = true;
        }
    
    while(!Travel.empty()) {
        int x = Travel.top();
        Travel.pop();
        
        if (--Indegree[To[x]] == 0) {
            IsVisited[To[x]] = true;
            
            Travel.push(To[x]);
        }
    }
    
    int MinLength = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        if (!IsVisited[i]) {
            IsVisited[i] = true;
            
            int Current = To[i], Length = 1;
            while(!IsVisited[Current]) {
                ++Length;
                Current = To[Current];
                IsVisited[Current] = true;
            }
            
            if (Length < MinLength)
                MinLength = Length;
        }
    }
    
    cout << MinLength << endl;
    
    return 0;
}