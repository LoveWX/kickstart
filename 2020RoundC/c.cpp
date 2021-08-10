#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

const int SIZE = 60;
double EVal[SIZE + 1][SIZE + 1][SIZE + 1];
int last[SIZE + 1][SIZE + 1][SIZE + 1];
double W, E;
vector<array<int, 3>> m60;

void Init()
{
    for (int i = 0; i <= SIZE; ++i)
    {
        for (int j = SIZE - i; j >= 0; --j)
        {
            m60.push_back({i, j, SIZE - i - j});
        }
    }
}

double dp(int r, int p, int s)
{
    if (last[r][p][s] != -1) return EVal[r][p][s];
    pair<double, int> ans = {0.0, 0};
    double n_1 = r + p + s - 1;
    if (r != 0) ans = max(ans, {dp(r - 1, p, s) + p / n_1 * W + s / n_1 * E, 0});
    if (p != 0) ans = max(ans, {dp(r, p - 1, s) + s / n_1 * W + r / n_1 * E, 1});
    if (s != 0) ans = max(ans, {dp(r, p, s - 1) + r / n_1 * W + p / n_1 * E, 2});
    EVal[r][p][s] = ans.first;
    last[r][p][s] = ans.second;
    return ans.first;
}

int main()
{
    int ncase, X;
    cin >> ncase >> X;
    Init();
	  for (int icase = 1; icase <= ncase; ++icase)
	  {
        cin >> W >> E;
        memset(last, -1, sizeof(last));
        EVal[1][0][0] = EVal[0][1][0] = EVal[0][0][1] = W / 3.0 + E / 3.0;
        last[1][0][0] = 0;
        last[0][1][0] = 1;
        last[0][0][1] = 2;
        last[0][0][0] = -1;
        tuple<double, int, int, int> maxv = {0.0, 0, 0, 0};
        for (array<int, 3> &a : m60)
        {
            maxv = max(maxv, {dp(a[0], a[1], a[2]), a[0], a[1], a[2]});
        }
        int r = get<1>(maxv), p = get<2>(maxv), s = get<3>(maxv);
        string ans;
        ans.reserve(SIZE);
        for (int curr = last[r][p][s]; curr >= 0; curr = last[r][p][s])
        {
            if (curr == 0)
            {
                ans.push_back('R');
                r -= 1;
            }
            else if (curr == 1)
            {
                ans.push_back('P');
                p -= 1;
            }
            else
            {
                ans.push_back('S');
                s -= 1;
            }
        }
        reverse(ans.begin(), ans.end());
        cout << "Case #" << icase << ": " << ans << endl;
    }
    return 0;
}
