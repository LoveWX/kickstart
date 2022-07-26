#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>
using namespace std;

vector<vector<int>> mpos;
vector<vector<int>> edge;
map<tuple<int, int, long long>, int> mem;

void Init()
{
    mpos.push_back(vector<int>());
    mpos.push_back(vector<int>(2));
    mpos.push_back(vector<int>(4));
    mpos.push_back(vector<int>(6));
    mpos.push_back(vector<int>(8));
    mpos.push_back(vector<int>(10));
    mpos.push_back(vector<int>(12));
    int c = 0;
    for (int i = 1; i <= 6; ++i)
    {
        for (int j = 1; j<mpos[i].size(); ++j)
        {
            mpos[i][j] = c++;
        }
    }
    edge.assign(36, vector<int>());
    for (int i = 2; i <= 6; ++i)
    {
        for (int j = 2; j<mpos[i].size(); ++j)
        {
            edge[mpos[i][j - 1]].push_back(mpos[i][j]);
            edge[mpos[i][j]].push_back(mpos[i][j - 1]);
        }
    }
    for (int i = 1; i<6; ++i)
    {
        for (int j = 1; j<mpos[i].size(); j += 2)
        {
            edge[mpos[i][j]].push_back(mpos[i + 1][j + 1]);
            edge[mpos[i + 1][j + 1]].push_back(mpos[i][j]);
        }
    }
}

int dp(int selfPos, int opptPos, long long status, bool opptStay)
{
    auto it = mem.find({ selfPos,opptPos,status });
    if (it != mem.end()) return it->second;
    int ans = INT_MIN;
    bool needStay = true;
    for (int i : edge[selfPos])
    {
        if ((status&(1LL << i)) == 0)
        {
            needStay = false;
            break;
        }
    }
    if (needStay && opptStay)
    {
        ans = 0;
    }
    else if (needStay)
    {
        ans = -dp(opptPos, selfPos, status, true);
    }
    else if (opptStay)
    {
        for (int i : edge[selfPos])
        {
            if ((status&(1LL << i)) != 0) continue;
            ans = max(ans, 1 + dp(i, opptPos, status ^ (1LL << i), true));
        }
    }
    else //(!needStay && !opptStay)
    {
        for (int i : edge[selfPos])
        {
            if ((status&(1LL << i)) != 0) continue;
            ans = max(ans, 1 - dp(opptPos, i, status ^ (1LL << i), false));
        }
    }
    mem[{selfPos, opptPos, status}] = ans;
    return ans;
}

int main()
{
    Init();
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        int S, RA, PA, RB, PB, C;
        cin >> S >> RA >> PA >> RB >> PB >> C;
        long long status = (1LL << mpos[RA][PA]) ^ (1LL << mpos[RB][PB]);
        for (; C>0; --C)
        {
            int i, j;
            cin >> i >> j;
            status ^= (1LL << mpos[i][j]);
        }
        //for (int i = S + 1; i <= 6; ++i)
        //{
        //    for (int j = 1; j<mpos[i].size(); ++j)
        //    {
        //        status ^= (1LL << mpos[i][j]);
        //    }
        //}
        status ^= (1LL << 36) - (1LL << (mpos[S].back() + 1));
        int ans = dp(mpos[RA][PA], mpos[RB][PB], status, false);
        cout << "Case #" << icase << ": " << ans << endl;
        mem.clear();
    }
    return 0;
}
