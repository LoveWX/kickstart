#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>
#include <functional>
using namespace std;

const long long INF = 1000000000000LL;

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int N, M, S, R;
        cin >> N >> M >> S >> R;
        vector<vector<int>> edge(N + 1);
        for (int i = 0; i < M; ++i)
        {
            int a, b;
            cin >> a >> b;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }

        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;
        for (int i = 1; i <= N; ++i)
        {
            int a, c;
            for (cin >> a; a > 0; --a)
            {
                cin >> c;
                pq.push({ 0LL, i, c });
            }
        }

        vector<vector<int>> vrecipe(R, vector<int>(4, 0));
        vector<vector<int>> mstone(S + 1);
        for (int i = 0; i < R; ++i)
        {
            int a, c;
            cin >> c;
            set<int> si;
            for (int j = 0; j < c; ++j)
            {
                cin >> a;
                vrecipe[i][j] = a;
                si.insert(a);
            }
            for (int b : si)
            {
                mstone[b].push_back(i);
            }
            cin >> vrecipe[i][3];
        }

        vector<vector<long long>> mdis(N + 1, vector<long long>(S + 1, INF));
        for (int i = 1; i <= N; ++i)
        {
            mdis[i][0] = 0LL;
        }

        while (!pq.empty())
        {
            auto [dis, junc, stone] = pq.top();
            pq.pop();
            if (dis >= mdis[junc][stone]) continue;
            mdis[junc][stone] = dis;
            for (int i : edge[junc])
            {
                if (dis + 1LL < mdis[i][stone])
                {
                    pq.push({ dis + 1LL, i, stone });
                }
            }
            for (int i : mstone[stone])
            {
                vector<int> &r = vrecipe[i];
                long long t = mdis[junc][r[0]] + mdis[junc][r[1]] + mdis[junc][r[2]];
                if (t < mdis[junc][r[3]])
                {
                    pq.push({ t, junc, r[3] });
                }
            }
        }

        long long ans = INF;
        for (int i = 1; i <= N; ++i)
        {
            ans = min(ans, mdis[i][1]);
        }
        if (ans >= INF) ans = -1LL;
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}
