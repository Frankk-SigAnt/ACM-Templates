#include <cstdio>

using namespace std;

namespace miller_rabin
{
    typedef long long ll;
    typedef long double ld;

    // Number of attempts
    const ll primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    const int __S = sizeof(primes) / sizeof(ll);

    inline ll mmul(ll a, ll b, ll MOD)
    {
        ll ans = 0;
        a %= MOD;
        while (b > 0)
        {
            if (b & 1)
            {
                ans = (ans + a) % MOD;
                b--;
            }
            b >>= 1;
            a = (a + a) % MOD;
        }
        return ans;
    }

    inline ll mpow(ll a, ll b, ll MOD)
    {
        ll ans = 1;
        while (b > 0)
        {
            if (b & 1) ans = mmul(ans, a, MOD);
            a = mmul(a, a, MOD);
            b >>= 1;
        }
        return ans % MOD;
    }

    inline bool check(ll p)
    {
        for (int i = 0; i < __S; i++)
        {
            if (p == primes[i]) return true;
        }
        if (p < primes[__S-1]) return false;
        if (!(p&1)) return false;

        ll pp = p - 1;
        while (!(pp&1)) pp >>= 1;
        for (int i = 0; i < __S; i++)
        {
            ll a = primes[i];
            ll x = mpow(a, pp, p);
            ll y = x;
            ll tp = pp;
            while (tp < p)
            {
                y = mmul(x, x, p);
                if (y == 1 && x != 1 && x != p-1) return false;
                x = y;
                tp <<= 1;
            }
            if (x != 1) return false;
        }
        return true;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int cnt = 0;
    while (n--)
    {
        long long num;
        scanf("%lld", &num);
        if (miller_rabin::check(num)) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}
