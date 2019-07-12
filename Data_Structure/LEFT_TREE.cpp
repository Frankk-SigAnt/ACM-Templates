#include <cstdio>
#include <cstring>
#include <algorithm>

#define clr(x) memset(x, 0, sizeof(x))
#define clrm1(x) memset(x, -1, sizeof(x))
#define clrinf(x) memset(x, 0x3f, sizeof(x))

using namespace std;

const int MAXN = 100010;

struct node
{
    int val;
    int fa;
    int ls, rs;
    int rdis;
} ltree[MAXN<<1];

inline int getroot(int x)
{
    while (ltree[x].fa != x) x = ltree[x].fa;
    return x;
}

inline void nodeinit(int x, int v = 0)
{
    ltree[x].ls = ltree[x].rs = ltree[x].dis = 0;
    ltree[x].fa = x;
    ltree[x].val = v;
}

int merge(int a, int b)
{
    if (a == 0 || b == 0) return a | b;
    
    if (ltree[a].val < ltree[b].val) swap(a, b);
    
    int & lson = ltree[a].ls;
    int & rson = ltree[a].rs;
    rson = merge(rson, b);
    ltree[rson].fa = a;
    
    if (ltree[lson].dis < ltree[rson].dis) swap(lson, rson);
    ltree[a].dis = rson==0 ? 0 : ltree[rson].dis+1;
    
    return a;
}

inline int del(int x)
{
    int l = ltree[x].ls;
    int r = ltree[x].rs;
    
    nodeinit(x);
    
    ltree[l].fa = l;
    ltree[r].fa = r;
    
    return merge(l, r);
}

