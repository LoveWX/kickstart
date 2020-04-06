#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int n, k;
vector<int> vi;
unordered_map<int,vector<int>> mindex;
vector<vector<int>> mem;

int dp(int left, int right)
{
    if (left > right)
    {
        return 0;
    }
    if (right - left + 1 < 3)
    {
        return 0;
    }
    if (mem[left][right] != -1)
    {
        return mem[left][right];
    }
    int ans = dp(left + 1, right);
    vector<int> &v1 = mindex[vi[left] + k];
    vector<int> &v2 = mindex[vi[left] + k + k];
    for (int i1 = upper_bound(v1.begin(), v1.end(), left) - v1.begin();
         i1 < v1.size() && v1[i1] < right; ++i1)
    {
        int c1 = v1[i1] - left - 1;
        if (c1 % 3 != 0 || dp(left + 1, v1[i1] - 1) != c1)
        {
            continue;
        }
        for (int i2 = upper_bound(v2.begin(), v2.end(), v1[i1]) - v2.begin();
             i2 < v2.size() && v2[i2] <= right; ++i2)
        {
            int c2 = v2[i2] - v1[i1] - 1;
            if (c2 % 3 != 0 || dp(v1[i1] + 1, v2[i2] - 1) != c2)
            {
                continue;
            }
            mem[left][v2[i2]] = v2[i2] - left + 1;
            ans = max(ans, v2[i2] - left + 1 + dp(v2[i2] + 1, right));
        }
    }
    return mem[left][right] = ans;
}

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        mindex.clear();
        cin >> n >> k;
        vi.assign(n, 0);
        for (int i = 0; i < n; ++i)
        {
            cin >> vi[i];
            mindex[vi[i]].push_back(i);
        }
        mem.assign(n, vector<int>(n, -1));
        cout << "Case #" << icase << ": " << n - dp(0, n - 1) << endl;
	}
	return 0;
}
