```c++
#include<cstdio>
#include<cstring>
#define L long long
#define fo(i,a,b)for(i=a;i<=b;i++)
#define max(a,b)((a)>(b)?(a):(b))
using namespace std;
const int Mx=210,Max=1000000001,Ma=100010;
int a,c[Mx],w[Mx],v[Mx],f[2][Ma],d[Ma];
int n,an,ss,sd,l,r,i,j,k,o;
int calc(int x){return f[!o][x*w[i]+j]-x*v[i];}
int main(){
    scanf("%d",&n);
    fo(i,1,n){
        scanf("%d%d%d%d",&a,&c[i],&w[i],&v[i]);
        an+=a*v[i];ss-=a*w[i];c[i]-=a;
    }
    fo(i,1,ss)f[0][i]=-Max;
    fo(i,1,n){o=!o;
        sd+=c[i]*w[i];if(sd>ss)sd=ss;
        fo(j,0,w[i]-1){l=1;r=0;
            fo(k,0,(sd-j)/w[i]){
                while(l<=r && calc(d[r])<calc(k))r--;d[++r]=k;
                if(d[l]+c[i]<k)l++;
                f[o][k*w[i]+j]=f[!o][d[l]*w[i]+j]+(k-d[l])*v[i];
            }
        }
    }
    printf("%d",an+f[o][ss]);
}
```
