#include <iostream>
#include <cstring>
using namespace std;

int a[20];
long long mem[20][2];

long long dp(int pos, int state, int leading, int limit)
{
    if (pos == -1)
    {
        return 1LL;
    }
    if (!limit && !leading && mem[pos][state] != -1)
    {
        return mem[pos][state];
    }
    int top = limit ? a[pos] : 9;
    long long ans = 0LL;
    if (leading)
    {
        ans += dp(pos - 1, 1, 1, limit && 0 == a[pos]);
        for (int i = 1; i <= top; ++i)
        {
            if (i % 2 == 1)
            {
                ans += dp(pos - 1, 0, 0, limit && i == a[pos]);
            }
        }
    }
    else
    {
        for (int i = 0; i <= top; ++i)
        {
            if (i % 2 == state)
            {
                ans += dp(pos - 1, 1 - state, leading && i == 0, limit && i == a[pos]);
            }
        }
    }
    if (!limit && !leading)
    {
        mem[pos][state] = ans;
    }
    return ans;
}

long long Calc(long long n)
{
    memset(mem, -1, sizeof(mem));
    int pos = 0;
    while (n != 0)
    {
        a[pos++] = n % 10;
        n /= 10;
    }
    return dp(pos - 1, 1, 1, 1);
}

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        long long L, R;
        cin >> L >> R;
        long long ans = Calc(R) - Calc(L - 1LL);
        cout << "Case #" << icase << ": " << ans << endl;
    }
    return 0;
}
