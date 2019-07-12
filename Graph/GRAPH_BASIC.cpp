#include <cstdio>
#include <cstring>

#define clr(x) memset(x, 0, sizeof(x))
#define clrm1(x) memset(x, -1, sizeof(x))
#define clrinf(x) memset(x, 0x3f, sizeof(x))

using namespace std;

const int MAXN;
const int MAXE;

int head[MAXN];
int nxt[MAXN];
int dest[MAXN];
int weight[MAXN];
int ecnt = 0;

inline void adde(int u, int v, int w)
{
    nxt[ecnt] = head[u];
    head[u] = ecnt;
    dest[ecnt] = v;
    weight[ecnt++] = w;
}

inline void init()
{
    clrm1(head);
    clrm1(nxt);
    ecnt = 0;
}
