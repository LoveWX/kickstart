#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

map<vector<int>, int> tiles;

void cut(int s)
{
    auto it = tiles.lower_bound({ s,s });
    int l1 = (it->first)[0];
    int l2 = (it->first)[1];
    it->second -= 1;
    if (it->second == 0)
    {
        tiles.erase(it);
    }
    for (vector<int> &vi : vector<vector<int>>({ { l1 - s,s },{ l2 - s,s },{ l1 - s,l2 - s } }))
    {
        if (vi[0] > vi[1])
        {
            swap(vi[0], vi[1]);
        }
        if (vi[0] != 0)
        {
            tiles[vi] += 1;
        }
    }
}

int main()
{
	int ncase;
	cin >> ncase;
    int n, m;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> n >> m;
        vector<int> tocut(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> tocut[i];
        }
        sort(tocut.begin(), tocut.end(), greater<int>());
        tiles.clear();
        tiles[{m, m}] = 1000;
        for (int i : tocut)
        {
            cut(1 << i);
        }
        cout << "Case #" << icase << ": " << 1000 - tiles[{m, m}] << endl;
	}
	return 0;
}
