#include <cstdio>
#include <cstring>
#include <algorithm>

#define clr(x) memset(x, 0, sizeof(x))
#define clrm1(x) memset(x, -1, sizeof(x))
#define clrinf(x) memset(x, 0x3f, sizeof(x))

using namespace std;

const int MAXN;
const int MAXD = 20;

int head[MAXN];
int nxt[MAXN*2];
int dest[MAXN*2];
long long weight[MAXN*2];
int ecnt = 0;

inline void adde(int u, int v, long long w = 1)
{
    nxt[ecnt] = head[u];
    head[u] = ecnt;
    dest[ecnt] = v;
    weight[ecnt++] = w;
}

int fa[MAXN][MAXD];
int deg[MAXN];
long long depth[MAXN];

int myqueue[MAXN];
int frnt, rare;

inline void bfs(int rt)
{
    deg[rt] = 0;
    depth[rt] = 0;
    fa[rt][0] = rt;
    myqueue[0] = rt;
    frnt = 0, rare = 1;
    while (frnt < rare)
    {
        int u = myqueue[frnt++];
        for (int i = 1; i < MAXD; i++)
        {
            fa[u][i] = fa[fa[u][i-1]][i-1];
        }
        for (int e = head[u]; ~e; e = nxt[e])
        {
            int v = dest[e];
            long long w = weight[e];
            if (v == fa[u][0]) continue;
            deg[v] = deg[u] + 1;
            depth[v] = depth[u] + w;
            fa[v][0] = u;
            myqueue[rare++] = v;
        }
    }
}

inline int lca(int u, int v)
{
    if (deg[u] > deg[v]) swap(u, v);
    int hu = deg[u], hv = deg[v];
    int tu = u, tv = v;
    for (int det = hv-hu, i = 0; det; det >>= 1, i++)
    {
        if (det & 1)
        {
            tv = fa[tv][i];
        }
    }
    if (tv == tu) return tu;
    for (int i = MAXD-1; i >= 0; i--)
    {
        if (fa[tu][i] == fa[tv][i]) continue;
        tu = fa[tu][i];
        tv = fa[tv][i];
    }
    return fa[tu][0];
}

inline void init()
{
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

