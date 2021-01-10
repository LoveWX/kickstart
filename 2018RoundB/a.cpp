#include <iostream>
#include <cstring>
using namespace std;

int a[19];
long long mem[19][9];

long long dp(int pos, int digitSum, int limit)
{
    if (pos == -1)
    {
        return digitSum == 0 ? 0 : 1;
    }
    if (!limit && mem[pos][digitSum] != -1)
    {
        return mem[pos][digitSum];
    }
    int top = limit ? a[pos] : 9;
    long long ans = 0;
    for (int i = 0; i <= top; ++i)
    {
        if (i == 9) continue;
        ans += dp(pos - 1, (digitSum + i) % 9, limit && i == a[pos]);
    }
    if (!limit)
    {
        mem[pos][digitSum] = ans;
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
    return dp(pos - 1, 0, 1);
}

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        long long F, L;
        cin >> F >> L;
        cout << "Case #" << icase << ": " << Calc(L) - Calc(F - 1) << endl;
    }
    return 0;
}
