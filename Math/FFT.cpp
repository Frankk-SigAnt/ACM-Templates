#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <complex>

using namespace std;

namespace fft
{
    typedef complex<double> cd;

    const int MAXL = 3600180;
    const double PI = acos(-1.0);

    cd a[MAXL], b[MAXL];

    int rev[MAXL];

    inline void getrev(int bit)
    {
        for (int i = 0; i < (1<<bit); i++)
        {
            rev[i] = (rev[i>>1]>>1) | ((i&1)<<(bit-1));
        }
    }

    inline void fft(cd * a, int n, int dft)
    {
        for (int i = 0; i < n; i++)
        {
            if (i < rev[i])
            {
                swap(a[i], a[rev[i]]);
            }
        }
        for (int step = 1; step < n; step <<= 1)
        {
            cd omega = exp(cd(0, dft*PI/step));
            for (int j = 0; j < n; j += (step<<1))
            {
                cd omk(1, 0);
                for (int k = j; k < j+step; k++)
                {
                    cd x = a[k];
                    cd y = omk * a[k+step];
                    a[k] = x + y;
                    a[k+step] = x - y;
                    omk *= omega;
                }
            }
        }
        if (dft == -1)
        {
            for (int i = 0; i < n; i++)
            {
                a[i] /= n;
            }
        }
    }

    inline void init()
    {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(rev, 0, sizeof(rev));
    }

    inline void getconv(int * arr1, int len1, int * arr2, int len2)
    {
        init();
        int bit = 1;
        while ((1<<bit) < len1+len2-1) bit++;
        int s = 1 << bit;
        for (int i = 0; i < len1; i++)
        {
            a[i] = double(arr1[i]);
        }
        for (int i = 0; i < len2; i++)
        {
            b[i] = double(arr2[i]);
        }
        getrev(bit);
        fft(a, s, 1);
        fft(b, s, 1);
        for (int i = 0; i < s; i++)
        {
            a[i] *= b[i];
        }
        fft(a, s, -1);
    }

    inline int * getans(int * ans, int st, int ed)
    {
        for (int i = st; i < ed; i++)
        {
            ans[i-st] = int(a[i].real() + 0.5);
        }
        return ans;
    }
}
