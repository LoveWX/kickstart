#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int num;
map<string, int> mnum;
vector<vector<int>> edge;
vector<int> indegree;
vector<bool> visited;

int GetNum(const string &s)
{
    auto it = mnum.find(s);
    if (it == mnum.end())
    {
        edge.emplace_back(vector<int>());
        indegree.emplace_back(0);
        mnum[s] = num++;
        return num - 1;
    }
    return it->second;
}

void dfs(int curr)
{
    if (visited[curr]) return;
    visited[curr] = true;
    for (int i : edge[curr])
    {
        indegree[i] -= 1;
        if (indegree[i] == 0)
        {
            dfs(i);
        }
    }
}

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        int n;
        cin >> n;
        string s;
        num = 0;
        mnum.clear();
        edge.clear();
        indegree.clear();
        GetNum("");
        for (int i = 0; i<n; ++i)
        {
            cin >> s;
            int dst = GetNum(s.substr(0, s.find('=')));
            s = s.substr(s.find('(') + 1);
            s.back() = ',';
            for (unsigned int j = 0; j<s.size();)
            {
                unsigned int t = s.find(',', j);
                edge[GetNum(s.substr(j, t - j))].push_back(dst);
                indegree[dst] += 1;
                j = t + 1;
            }
        }
        visited.assign(num, false);
        dfs(0);
        bool good = true;
        for (bool b : visited)
        {
            if (!b)
            {
                good = false;
                break;
            }
        }
        cout << "Case #" << icase << ": " << (good ? "GOOD" : "BAD") << endl;
    }
    return 0;
}
