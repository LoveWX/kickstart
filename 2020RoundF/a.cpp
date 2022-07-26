#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

const int SIZE = 100000;

int main()
{
    vector<array<int, 2>> vp(SIZE);
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        int N, X;
        cin >> N >> X;
        vp.resize(N);
        for (int i = 0; i < N; ++i)
        {
            cin >> vp[i][0];
            vp[i][1] = i + 1;
            vp[i][0] = vp[i][0] / X + (vp[i][0] % X == 0 ? 0 : 1);
        }
        sort(vp.begin(), vp.end());
        cout << "Case #" << icase << ":";
        for (array<int, 2> &p : vp)
        {
            cout << ' ' << p[1];
        }
        cout << endl;
	}
	return 0;
}
