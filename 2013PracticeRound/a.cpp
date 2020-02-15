#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

bool errFound;

void dfs(vector<vector<int>> &edge, vector<int> &vcolor, int curr, int color)
{
	if (errFound)
	{
		return;
	}
	if (vcolor[curr] != 0)
	{
		if (vcolor[curr] != color)
		{
			errFound = true;
		}
		return;
	}
	vcolor[curr] = color;
	for (int i : edge[curr])
	{
		dfs(edge, vcolor, i, 3 - color);
	}
}

int main()
{
	int ncase, nedge;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		cin >> nedge;
		string sa, sb;
		int n = 0;
		unordered_map<string, int> m;
		vector<vector<int>> edge;
		while ((nedge--) != 0)
		{
			cin >> sa >> sb;
			if (m.count(sa) == 0)
			{
				m[sa] = n++;
				edge.push_back(vector<int>());
			}
			if (m.count(sb) == 0)
			{
				m[sb] = n++;
				edge.push_back(vector<int>());
			}
			int ia = m[sa], ib = m[sb];
			edge[ia].push_back(ib);
			edge[ib].push_back(ia);
		}
		errFound = false;
		vector<int> vcolor(n, 0);
		dfs(edge, vcolor, 0, 1);
		cout << "Case #" << icase << ": " << (errFound ? "No" : "Yes") << endl;
	}
	return 0;
}