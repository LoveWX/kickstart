#include <iostream>
#include <string>
using namespace std;

long long fac5[20];

long long Calc(const string &s)
{
    long long ans = 0LL;
    for (int i = s.size() - 1; i > 0; --i)
    {
        ans += fac5[i];
    }
    int p = s.size() - 1;
    int odd = 1;
    for (char c : s)
    {
        int d = c - '0';
        if (d % 2 != odd)
        {
            ans += (d - odd + 1) / 2 * fac5[p--];
            break;
        }
        ans += (d - odd) / 2 * fac5[p--];
        odd = 1 - odd;
    }
    return ans;
}

int main()
{
    fac5[0] = 1LL;
    for (int i = 1; i < 20; ++i)
    {
        fac5[i] = fac5[i - 1] * 5LL;
    }
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        long long L, R;
        cin >> L >> R;
        long long ans = Calc(to_string(R + 1)) - Calc(to_string(L));
        cout << "Case #" << icase << ": " << ans << endl;
    }
    return 0;
}
