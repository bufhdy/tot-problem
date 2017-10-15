```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
using namespace std;
const int MAXN = 1e2 + 5;

/*
    「这是一个很显然的DAG，那么可以考虑拓扑排序。」
 */

struct Vtx {
    Vtx *Next;
    int To, Wgt;

    Vtx(void) : Next(NULL) {}
};

struct VtxHead : Vtx {
    Vtx *Head;
    int C, U, InDegree, OutDegree;

    void Grow (int To, int Wgt)
    {
        if (!Head) {
            Next = new Vtx();
            Next->To = To;
            Next->Wgt = Wgt;
            Head = Next;
        }
        else {
            Next->Next = new Vtx();
            Next = Next->Next;
            Next->To = To;
            Next->Wgt = Wgt;
        }
    }

    VtxHead(void) : Head(NULL),
        InDegree(0), OutDegree(0) {}
} Graph[MAXN];

struct Main {
    int n, p;

    void Toposort(void)
    {
        queue<int> Travel;
        for (int i = 1; i <= n; ++i)
            if (Graph[i].InDegree == 0)
                Travel.push(i);

        while (!Travel.empty()) {
            int x = Travel.front();
            Travel.pop();

            if (Graph[x].C <= 0)
                for (Vtx *i = Graph[x].Head;
                    i; i = i->Next) 
                    if (--Graph[i->To].InDegree == 0)
                        Travel.push(i->To);
            else 
                for (Vtx *i = Graph[x].Head;
                    i; i = i->Next) {
                    Graph[i->To].C +=
                        Graph[x].C * i->Wgt;

                    if (--Graph[i->To].InDegree == 0)
                        Travel.push(i->To);
                }
        }
    }

    Main(void)
    {
        scanf("%d %d", &n, &p);

        for (int i = 1; i <= n; ++i)
            scanf("%d %d",
                &Graph[i].C, &Graph[i].U);

        for (int i = 1; i <= n; ++i)
            if (Graph[i].C == 0)
                Graph[i].C -= Graph[i].U;

        for (int i = 1; i <= p; ++i) {
            int u, v, Wgt;
            scanf("%d %d %d", &u, &v, &Wgt);

            Graph[u].Grow(v, Wgt);
            ++Graph[u].OutDegree;
            ++Graph[v].InDegree;
        }

        Toposort();

        bool IsOut = false;
        for (int i = 1; i <= n; ++i)
            if (Graph[i].OutDegree == 0 &&
                Graph[i].C > 0) {
                printf("%d %d\n", i, Graph[i].C);
                IsOut = true;
            }

        if (!IsOut)
            puts("NULL");
    }
};

int main(void)
{
    delete new Main();

    return 0;
}
```
