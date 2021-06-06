#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>
using namespace std;

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        int N, K;
        cin >> N >> K;
        vector<int> vs(N);
        map<int, int> mh;
        for (int &i : vs)
        {
            cin >> i;
            mh[i];
        }
        int count = 0;
        for (auto it = mh.begin(); it != mh.end(); ++it)
        {
            it->second = count++;
        }
        for (int &i : vs)
        {
            i = mh[i];
        }

        vector<vector<int>> curr(K + 1, vector<int>(count, INT_MAX));
        curr[0] = vector<int>(count, 1);
        curr[0][vs[0]] = 0;
        for (int k = 1; k < N; ++k)
        {
            for (int i = min(k, K); i > 0; --i)
            {
                int minv = *min_element(curr[i - 1].begin(), curr[i - 1].end());
                for (int j = 0; j < count; ++j)
                {
                    curr[i][j] = (j == vs[k] ? 0 : 1) + min(curr[i][j], minv);
                }
            }
            for (int j = 0; j < count; ++j)
            {
                curr[0][j] += (j == vs[k] ? 0 : 1);
            }
        }

        int ans = INT_MAX;
        for (vector<int> &vi : curr)
        {
            ans = min(ans, *min_element(vi.begin(), vi.end()));
        }
        cout << "Case #" << icase << ": " << ans << endl;
    }
    return 0;
}
