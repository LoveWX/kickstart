#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct cmp
{
	bool operator ()(pair<int, int> &a, pair<int, int> &b)
	{
		return a.second == b.second ? a.first < b.first : a.second > b.second;
	}
};

int ShortestPath(vector<unordered_map<int, int>> &edge, int start, int end)
{
	int n = edge.size();
	vector<int> distance(n, 0x7FFFFFFF);
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	pq.push({ start,0 });
	while (!pq.empty())
	{
		int i = pq.top().first;
		int dis = pq.top().second;
		pq.pop();
		if (distance[i] == 0x7FFFFFFF)
		{
			if (i == end) return dis;
			distance[i] = dis;
			for (pair<int, int> p : edge[i])
			{
				int newdis = dis + p.second;
				if (newdis < distance[p.first])
				{
					pq.push({ p.first,newdis });
				}
			}
		}
	}
	return -1;
}

int main()
{
	int ncase;
	cin >> ncase;
	string str;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		int n, a, b, t = 0;
		cin >> n;
		unordered_map<string, int> mcolor;
		vector<int> vmnode(n + 1);
		for (int i = 1; i <= n; ++i)
		{
			cin >> str;
			if (mcolor.count(str) == 1)
			{
				vmnode[i] = mcolor[str];
			}
			else
			{
				mcolor[str] = t;
				vmnode[i] = t++;
			}
		}

		vector<unordered_map<int, int>> edge(n);
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> a >> b >> t;
			a = vmnode[a];
			b = vmnode[b];
			if (a != b)
			{
				if (edge[a].count(b) == 0 || edge[a][b] > t)
				{
					edge[a][b] = t;
				}
			}
		}

		cout << "Case #" << icase << ":" << endl;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> a >> b;
			cout << ShortestPath(edge, vmnode[a], vmnode[b]) << endl;
		}
	}
	return 0;
}
