#include <cstring>

using std::memset;

const int MAXN = 20; // `long long` has no more than 19 digits.
const int STATUS_NUM; // Possible statuses of the number.

int digit[MAXN]; // Store every digit of the number.

long long dp[MAXN][STATUS_NUM]; // Initially set to -1.

/**
 *           pos: Current digit position, 
 *                from the highest (n-1) to the lowest (0).
 *        status: Current status of the number,
 *                from STATUS_NUM-1 to 0,
 *                representing different statuses.
 * is_restricted: Indicates if the range of digits
 *                are restricted by the maximum value.
 *                If so, the range of position `pos` is
 *                [0, digit[pos]].
 *         (...): May have other restrictions, depending 
 *                on the problem.
 */
long long dfs(int pos, int status, bool is_restricted, ...)
{
    if (pos < 0) return _DEFAULT_RETURN_VALUE;
    if (!is_restricted && dp[pos][status] != -1) // Memorized search.
        return dp[pos][status];
    
    long long ans = 0;
    int max_digit = is_restricted ? digit[pos] : 9;
    for (int d = 0; d <= max_digit; ++d)
    {
        // (status transformation omitted...)
        ans += dfs(pos-1, _NEW_STATUS, is_restricted&&(i==max_digit));
    }
    
    if (!is_restricted)
        dp[pos][status] = ans; // The answer can be used more than once.
    
    return ans;
}

long long digital_dp(long long N)
{
    // Initialize.
    memset(digit, 0, sizeof(digit));
    memset(dp, -1, sizeof(dp));
    
    // Pre-process digits.
    int cnt = 0;
    while (N > 0)
    {
        digit[cnt++] = N % 10;
        N /= 10;
    }
    
    return dfs(cnt-1, _INITIAL_STATUS, true);
}
