#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

unsigned int L[5000];
long long num[5000];
long long presum[5000];

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int n, t;
        map<int, int> m;
        for (cin >> n; n > 0; --n)
        {
            cin >> t;
            m[t] += 1;
        }
        n = 0;
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            L[n] = it->first;
            num[n++] = it->second;
        }
        presum[0] = num[0];
        for (int i = 1; i < n; ++i)
        {
            presum[i] = presum[i - 1] + num[i];
        }
        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (num[i] < 2) continue;
            for (int j = 0; j < i; ++j)
            {
                int t = lower_bound(L, L + n, L[j] + L[i] * 2U) - L - 1;
                ans += num[i] * (num[i] - 1) / 2 * num[j] * (presum[t] - presum[j] - num[i]);
            }
            for (int j = i + 1; j < n; ++j)
            {
                int t = lower_bound(L, L + n, L[j] + L[i] * 2U) - L - 1;
                ans += num[i] * (num[i] - 1) / 2 * num[j] * (presum[t] - presum[j]);
            }
            if (num[i] == 2) continue;
            int t = lower_bound(L, L + n, L[i] * 3U) - L - 1;
            ans += num[i] * (num[i] - 1) * (num[i] - 2) / 6 * (presum[t] - num[i]);
        }
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}
