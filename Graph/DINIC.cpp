#include <cstdio>
#include <cstring>

#define clr(x) memset(x, 0, sizeof(x))
#define clrm1(x) memset(x, -1, sizeof(x))
#define clrinf(x) memset(x, 0x3f, sizeof(x))

using namespace std;

const int MAXN;
const int MAXE;
const int INF = 0x3f3f3f3f;

int head[MAXN];
int nxt[MAXE];
int dst[MAXE];
int weight[MAXE];
int ecnt;

inline void addedge(int u, int v, int w)
{
    nxt[ecnt] = head[u];
    head[u] = ecnt;
    dst[ecnt] = v;
    weight[ecnt++] = w;
}

inline void addedges(int u, int v, int w)
{
    addedge(u, v, w);
    addedge(v, u, 0);
}

int S = 0, T;

int depth[MAXN];
int myqueue[MAXN];
int frnt, rare;

inline bool bfs()
{
    clr(depth);
    
    myqueue[0] = S;
    frnt = 0, rare = 1;
    depth[S] = 1;
    while (front < rare)
    {
        int u = myqueue[frnt++];
        for (int e = head[u]; ~e; e = nxt[e])
        {
            int v = dst[e];
            if (depth[v] == 0 && weight[e] > 0)
            {
                depth[v] = depth[u] + 1;
                myqueue[rare++] = v;
            }
        }
    }
    
    return depth[T] > 0;
}

int cedge[MAXN];

int dfs(int u, int flow)
{
    if (u == T) return flow;
    
    for (int & e = cedge[u]; ~e; e = nxt[e])
    {
        int v = dst[e];
        if (depth[v] == depth[u]+1 && weight[e] != 0)
        {
            int f = dfs(v, min(flow, weight[e]));
            if (f > 0)
            {
                weight[i] -= f;
                weight[i^1] += f;

                return f;
            }
        }
    }
    
    return 0;
}

inline int dinic()
{
    int res = 0;

    while (bfs())
    {
        memcpy(cedge, head, sizeof(head));

        while (int f = dfs(S, INF))
        {
            res += f;
        }
    }

    return res;
}

inline void init(int totn)
{
    clrm1(head);
    clrm1(nxt);
    ecnt = 0;
    
    clr(depth);
    T = totn - 1;
}
