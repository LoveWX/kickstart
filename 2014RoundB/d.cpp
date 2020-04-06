#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long c[201][101] = { 1 };
long long catalan[37] = { 1,1 };
vector<vector<long long>> mem;

long long C(int n, int m)
{
    if (m == 0 || m == n)
    {
        return 1;
    }
    if (c[n][m] != 0)
    {
        return c[n][m];
    }
    return c[n][m] = C(n - 1, m) + C(n - 1, m - 1);
}

long long dp(int n, int m)
{
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
    return mem[n][m] = dp(n - 1, m) + dp(n, m - 1);
}

int main()
{
    for (int i = 2; i <= 35; ++i)
    {
        catalan[i] = C(i + i, i) - C(i + i, i - 1);
    }
    catalan[0] = 0;
    catalan[36] = 0x7FFFFFFFFFFFFFFFLL;
    mem.assign(101, vector<long long>(101, -1));
	int ncase;
	cin >> ncase;
    int n, m;
    long long k;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> n >> k;
        if (catalan[n] < k)
        {
            cout << "Case #" << icase << ": Doesn't Exist!" << endl;
            continue;
        }
        //int t = lower_bound(catalan, catalan + 37, k) - catalan;
        string ans;
        m = n;
        while (true)
        {
            long long t = dp(n - 1, m);
            if (t == k)
            {
                ans += '(';
                ans += string(m - (n - 1), ')');
                for (int i = 0; i < n - 1; ++i)
                {
                    ans += "()";
                }
                break;
            }
            if (t > k)//(
            {
                ans += '(';
                --n;
            }
            else
            {
                k -= t;
                ans += ')';
                --m;
            }
        }
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}
https://stackoverflow.com/questions/26437223/dynamic-programming-calculating-kth-parentheses-sequence
