#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;

void dfs_val(vector<unordered_map<int, long long>> &edge, unordered_map<int, long long> &mval, int i, long long val)
{
    for (pair<int, long long> p : edge[i])
    {
        if (mval.count(p.first) == 0)
        {
            mval[p.first] = p.second - val;
            dfs_val(edge, mval, p.first, p.second - val);
        }
    }
}

void dfs(vector<unordered_map<int, long long>> &edge, int n, int start)
{
    vector<int> visited(n, 0);
    visited[start] = 1;
    unordered_map<int, long long> m1 = edge[start], m2;
    for (pair<int, long long> p : m1)
    {
        visited[p.first] = 1;
    }
    while (!m1.empty())
    {
        for (pair<int, long long> p1 : m1)
        {
            for (pair<int, long long> p2 : edge[p1.first])
            {
                if(visited[p2.fisrt])
            }
        }
    }
}

int main()
{
	int ncase,n;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int count = 0,t,a,b;
        unordered_map<string, int> msi;
        unordered_map<int, long long> mval;
        vector<unordered_map<int, long long>> edge;
        cin >> n;
        string sa, sb;
        for (int i = 0; i < n; ++i)
        {
            cin >> sb;
            int pluspos = sb.find('+');
            int equpos = sb.find('=');
            sa = sb.substr(0, pluspos);
            t = stoi(sb.substr(equpos + 1));
            sb = sb.substr(pluspos + 1, equpos - pluspos - 1);
            if (msi.count(sa) == 0)
            {
                msi[sa] = count++;
                edge.push_back(unordered_map<int, long long>());
            }
            if (msi.count(sb) == 0)
            {
                msi[sb] = count++;
                edge.push_back(unordered_map<int, long long>());
            }
            a = msi[sa];
            b = msi[sb];
            if (a == b)
            {
                mval[a] = t;
            }
            else
            {
                edge[a][b] = t * 2;
                edge[b][a] = t * 2;
            }
        }
        vector<pair<int, long long>> vil(mval.begin(), mval.end());
        for (pair<int, long long> &p : vil)
        {
            dfs_val(edge, mval, p.first, p.second);
        }
        vector<int> visited(count, 0);
        for (int i = 0; i < count; ++i)
        {
            if (mval.count(i) == 0)
            {
                dfs(i);
            }
        }
	}
	return 0;
}
