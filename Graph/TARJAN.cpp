#include <cstdio>
#include <cstring>
#include <algorithm>

#define clr(x) memset(x, 0, sizeof(x))
#define clrm1(x) memset(x, -1, sizeof(x))
#define clrinf(x) memset(x, 0x3f, sizeof(x))

const int MAXN = 100010;
const int MAXM = MAXN << 2;
const int MAXD = 20;

// #define TARJAN_UNDIRECTED_GRAPH

int head[MAXN];
int nxt[MAXM];
int dest[MAXM];
#ifdef TARJAN_UNDIRECTED_GRAPH
bool vis[MAXM];
#endif
int ecnt;

inline void adde(int u, int v)
{
    nxt[ecnt] = head[u];
    head[u] = ecnt;
    dest[ecnt++] = v;
}

int low[MAXN];
int dfn[MAXN];
int ind;

int stk[MAXN];
bool instk[MAXN];
int scnt;

int belong[MAXN];
int bcnt;

void tarjan(int u)
{
    int v;
    low[u] = dfn[u] = ++ind;
    stk[scnt++] = u;
    instk[u] = true;
    for (int e = head[u]; ~e; e = nxt[e])
    {
#ifdef TARJAN_UNDIRECTED_GRAPH
        if (vis[e]) continue;
        vis[e] = vis[e^1] = true;
#endif
        v = dest[e];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
#ifdef TARJAN_UNDIRECTED_GRAPH
        else
#else
        else if (instk[v])
#endif
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        bcnt++;
        do
        {
            v = stk[--scnt];
            instk[v] = false;
            belong[v] = bcnt;
        } while (v != u);
    }
}

void solve(int N)
{
    for (int i = 1; i <= N; i++)
    {
        if (!dfn[i]) tarjan(i);
    }
}

inline void init()
{
    clrm1(head);
    clr(dfn);
    clr(instk);
#ifndef TARJAN_UNDIRECTED_GRAPH
    clr(vis);
#endif
    ecnt = 0;
    scnt = 0;
    bcnt = 0;
}
