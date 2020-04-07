#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<long long>> mem;
long long maxv = 2e18;

long long add(long long a, long long b)
{
    return min(maxv, a + b);
}

long long dp(int n, int m)
{
    if (n < 0)
    {
        return 0;
    }
    if (n == 0)
    {
        return 1;
    }
    if (n > m)
    {
        return 0;
    }
    if (mem[n][m] != -1)
    {
        return mem[n][m];
    }
    return mem[n][m] = add(dp(n - 1, m), dp(n, m - 1));
}

int main()
{
    mem.assign(101, vector<long long>(101, -1));
	int ncase;
	cin >> ncase;
    int n, m;
    long long k;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> n >> k;
        if (k > dp(n, n))
        {
            cout << "Case #" << icase << ": Doesn't Exist!" << endl;
            continue;
        }
        string ans;
        m = n;
        while (m != 0 || n != 0)
        {
            if (k <= dp(n - 1, m))
            {
                ans += '(';
                --n;
            }
            else
            {
                k -= dp(n - 1, m);
                ans += ')';
                --m;
            }
        }
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}
