#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int N, M, P;
        cin >> N >> M >> P;
        string s;
        vector<vector<int>> mc(N, vector<int>(P));
        for (int i = 0; i < N; ++i)
        {
            cin >> s;
            for (int j = 0; j < P; ++j)
            {
                mc[i][j] = s[j] - '0';
            }
        }

        vector<pair<int, string>> vcurr(1, { 0, string(P, '0') });
        for (int j = 0; j < P; ++j)
        {
            int count1 = 0;
            for (int i = 0; i < N; ++i)
            {
                count1 += mc[i][j];
            }

            vector<pair<int, string>> vnext;
            vnext.reserve(vcurr.size() * 2);
            for (pair<int, string> &p : vcurr)
            {
                vnext.push_back({p.first + count1, p.second});
            }
            for (pair<int, string> &p : vcurr)
            {
                p.second[j] = '1';
                vnext.push_back({p.first + N - count1, p.second});
            }
            sort(vnext.begin(), vnext.end());
            if (vnext.size() > M + 1)
            {
                vnext.resize(M + 1);
            }
            vcurr = move(vnext);
        }

        set<string> sForbidden;
        for (int i = 0; i < M; ++i)
        {
            cin >> s;
            sForbidden.insert(move(s));
        }
        for (pair<int, string> &p : vcurr)
        {
            if (sForbidden.count(p.second) == 0)
            {
                cout << "Case #" << icase << ": " << p.first << endl;
                break;
            }
        }
	}
	return 0;
}
