#include <iostream>
#include <vector>
using namespace std;

long long mod = 1e9 + 7;
vector<vector<long long>> c;
vector<vector<long long>> f;

long long C(int n, int m)
{
    if (m > n)
    {
        return 0;
    }
    if (m == 0 || m == n)
    {
        return 1;
    }
    if (c[n][m] != -1)
    {
        return c[n][m];
    }
    return c[n][m] = (C(n - 1, m - 1) + C(n - 1, m)) % mod;
}

long long F(int n, int m)
{
    if (m == 1)
    {
        return 1;
    }
    if (f[n][m] != -1)
    {
        return f[n][m];
    }
    if (n == m)
    {
        return f[n][n] = F(n - 1, n - 1) * n % mod;
    }
    long long ans = 0;
    for (int i = n - 1, j = m - 1; i >= j; --i)
    {
        ans = (ans + F(i, j) * C(n, i)) % mod;
    }
    return f[n][m] = ans;
}

int main()
{
    c.assign(101, vector<long long>(101, -1));
    f.assign(101, vector<long long>(101, -1));
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int n, m;
        cin >> m >> n;
        cout << "Case #" << icase << ": " << F(n, m) << endl;
	}
	return 0;
}
