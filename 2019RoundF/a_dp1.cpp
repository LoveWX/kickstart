#include <iostream>
#include <vector>
#include <map>
#include <set>
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
        for (int &i : vs)
        {
            cin >> i;
        }
        
        vector<vector<int>> R(N, vector<int>(N, INT_MAX >> 1));
        for (int i = 0; i < N; ++i)
        {
            map<int, int> mi;
            multiset<int> si;
            for (int j = i; j < N; ++j)
            {
                auto it = mi.find(vs[j]);
                if (it == mi.end())
                {
                    mi[vs[j]] = 1;
                    si.insert(1);
                }
                else
                {
                    si.erase(si.find(it->second));
                    it->second += 1;
                    si.insert(it->second);
                }
                R[i][j] = j - i + 1 - *si.rbegin();
            }
        }
        vector<vector<int>> F(N, vector<int>(K + 1, 0));
        for (int x = 1; x < N; ++x)
        {
            F[x][0] = R[0][x];
            for (int k = 1; k <= K; ++k)
            {
                int ans = INT_MAX;
                for (int i = 0; i < x; ++i)
                {
                    ans = min(ans, F[i][k - 1] + R[i + 1][x]);
                }
                F[x][k] = ans;
            }
        }
        cout << "Case #" << icase << ": " << F[N - 1][K] << endl;
    }
    return 0;
}
