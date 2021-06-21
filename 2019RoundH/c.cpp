#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        vector<int> vi(10, 0);
        for (int i = 1; i <= 9; ++i)
        {
            cin >> vi[i];
            // vi[i] %= 22;
            // if (vi[i] >= 22)
            // {
            //     vi[i] = 20 + vi[i] % 2;
            // }
            if (vi[i] >= 10)
            {
                vi[i] = 10 + vi[i] % 2;
            }
        }
        vector<vector<bool>> last(1, vector<bool>(11, false));
        last[0][0] = true;
        for (int k = 1; k <= 9; ++k)
        {
            vector<int> curr(vi[k] + 1);
            for (int i = 0; i <= vi[k]; ++i)
            {
                curr[i] = ((i - (vi[k] - i)) * k % 11 + 11) % 11;
            }
            vector<vector<bool>> next(last.size() + curr.size() - 1, vector<bool>(11, false));
            for (int i = 0; i < last.size(); ++i)
            {
                for (int j = 0; j < 11; ++j)
                {
                    if (!last[i][j]) continue;
                    for (int a = 0; a < curr.size(); ++a)
                    {
                        next[i + a][(j + curr[a]) % 11] = true;
                    }
                }
            }
            last = move(next);
        }
        int count = accumulate(vi.begin(), vi.end(), 0);
        cout << "Case #" << icase << (last[(count + 1) / 2][0] ? ": YES" : ": NO") << endl;
	}
	return 0;
}
