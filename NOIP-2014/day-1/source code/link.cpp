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
const int MAXN = 2e5 + 5,
    MOD = 10007;

struct Main {
    struct Vtx {
        Vtx *Next;
        int To;

        Vtx(void) : Next(NULL) {}
    };

    struct VtxHead : Vtx {
        Vtx *Head;

        void operator += (int To)
        {
            if (!Head) {
                Next = new Vtx();
                Next->To = To;
                Head = Next; 
            } else {
                Next->Next = new Vtx();
                Next = Next->Next;
                Next->To = To;
            }
        }

        VtxHead(void) : Head(NULL) {}
    } Graph[MAXN];

    int n,
        Wgt[MAXN];

    Main(void)
    {
        scanf("%d", &n);

        for (int i = 1; i <= n - 1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);

            Graph[u] += v;
            Graph[v] += u;
        }

        for (int i = 1; i <= n; ++i)
            scanf("%d", Wgt + i);
        
        long long Sum = 0;
        int Max = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            int Fst = INT_MIN,
                Sec = INT_MIN;

            vector<int> Pnt;
            long long SumTmp = 0;
            
            for (Vtx *j = Graph[i].Head;
                j; j = j->Next) {
                Pnt.push_back(Wgt[j->To]);
                SumTmp = (SumTmp + Wgt[j->To]) % MOD;
                
                if (Wgt[j->To] > Sec)
                    if (Wgt[j->To] > Fst) {
                        Sec = Fst;
                        Fst = Wgt[j->To];
                    } else Sec = Wgt[j->To];    
            }

            if (Fst * Sec > Max)
                Max = Fst * Sec;

            int Size = Pnt.size();
            for (int i = 0; i < Size; ++i) {
                Sum = (Sum + Pnt[i] * ((SumTmp - Pnt[i]) % MOD + MOD)) % MOD;
            }
        }

        printf("%d %lld\n", Max, Sum);
    }
};

int main(void)
{
    delete new Main();

    return 0;
}
/*
5
1 2
2 3
3 4
4 5
1 5 2 3 10
*/