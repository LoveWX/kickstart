#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

int n;

int bfs(vector<vector<pair<int, int>>> &edge, int start, int end)
{
    vector<vector<bool>> visited(2, vector<bool>(n, false));
    queue<vector<int>> q;
    q.push({ start,0,0 });
    while (!q.empty())
    {
        int curr = q.front()[0];
        int val = q.front()[1];
        int odd = q.front()[2];
        q.pop();
        if (visited[odd][curr])
        {
            continue;
        }
        visited[odd][curr] = true;
        int newodd = 1 - odd;
        for (pair<int, int> p : edge[curr])
        {
            int newval = (odd == 0 ? val + p.second : val - p.second);
            if (p.first == end && newodd == 1)
            {
                return newval;
            }
            if (!visited[newodd][p.first])
            {
                q.push({ p.first,newval,newodd });
            }
        }
    }
    return 0x7FFFFFFF;
}

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int count, a, b, t;
        n = 0;
        vector<vector<pair<int, int>>> edge;
        unordered_map<string, int> msi;
        cin >> count;
        string sa, sb;
        for (int i = 0; i < count; ++i)
        {
            cin >> sb;
            a = sb.find("+");
            b = sb.rfind("=");
            sa = sb.substr(0, a);
            t = stoi(sb.substr(b + 1));
            sb = sb.substr(a + 1, b - a - 1);
            if (msi.count(sa) == 0)
            {
                msi[sa] = n++;
                edge.push_back(vector<pair<int, int>>());
            }
            if (msi.count(sb) == 0)
            {
                msi[sb] = n++;
                edge.push_back(vector<pair<int, int>>());
            }
            a = msi[sa];
            b = msi[sb];
            edge[a].push_back({ b,t });
            edge[b].push_back({ a,t });
        }
        cin >> count;
        cout << "Case #" << icase << ":" << endl;
        for (int i = 0; i < count; ++i)
        {
            cin >> sb;
            a = sb.find("+");
            sa = sb.substr(0, a);
            sb = sb.substr(a + 1);
            if (msi.count(sa) == 0 || msi.count(sb) == 0)
            {
                continue;
            }
            t = bfs(edge, msi[sa], msi[sb]);
            if (t != 0x7FFFFFFF)
            {
                cout << sa << "+" << sb << "=" << t << endl;
            }
        }
	}
	return 0;
}
