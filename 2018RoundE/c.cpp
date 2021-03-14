#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int N, K;
        cin >> N >> K;
        vector<int> vt(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> vt[i];
        }
        sort(vt.begin(), vt.end());
        int ans = 0, d = 0;
        for (int i = 0; i < N;)
        {
            for (; i < N && vt[i] <= d; ++i);
            for (int j = 0; j < K && i < N; ++j, ++i)
            {
                ans += 1;
            }
            d += 1;
        }
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}
