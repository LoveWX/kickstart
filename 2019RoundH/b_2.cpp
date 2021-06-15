#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <numeric>
#include <climits>
using namespace std;

const int INF = INT_MAX >> 10;
const int SIZE = 100;
int N;
int grid[SIZE][SIZE];
vector<vector<array<int, 2>>> vdiagonal0, vdiagonal1;
vector<vector<int>> vflip;

void BuildGraph()
{
    vdiagonal0.assign(2 * N - 1, vector<array<int, 2>>());
    vdiagonal1.assign(2 * N - 1, vector<array<int, 2>>());
    for (int k = 0; k < N; ++k)
    {
        for (int i = k, j = 0; i < N; ++i, ++j)
        {
            vdiagonal0[i - j + N - 1].push_back({ i,j });
        }
    }
    for (int k = 1; k < N; ++k)
    {
        for (int i = 0, j = k; j < N; ++i, ++j)
        {
            vdiagonal0[i - j + N - 1].push_back({ i,j });
        }
    }
    for (int k = 0; k < N; ++k)
    {
        for (int i = 0, j = k; j >= 0; ++i, --j)
        {
            vdiagonal1[i + j].push_back({ i,j });
        }
    }
    for (int k = 1; k < N; ++k)
    {
        for (int i = k, j = N - 1; i < N; ++i, --j)
        {
            vdiagonal1[i + j].push_back({ i,j });
        }
    }
}

void dfs(int d, int idx, int flip)
{
    if (vflip[d][idx] != -1)
    {
        if (vflip[d][idx] != flip)
        {
            vflip[d][idx] = INF;
        }
        return;
    }
    vflip[d][idx] = flip;
    if (d == 0)
    {
        for (array<int, 2> &p : vdiagonal0[idx])
        {
            dfs(1, p[0] + p[1], grid[p[0]][p[1]] == 0 ? flip : 1 - flip);
        }
    }
    else
    {
        for (array<int, 2> &p : vdiagonal1[idx])
        {
            dfs(0, p[0] - p[1] + N - 1, grid[p[0]][p[1]] == 0 ? flip : 1 - flip);
        }
    }
}

int Calc0(int flip)
{
    vflip.assign(2, vector<int>(2 * N - 1, -1));
    dfs(1, 0, flip);
    int ans = 0;
    for (int i = 1 - N % 2; i < 2 * N - 1; i += 2)
    {
        ans += vflip[0][i];
    }
    for (int i = 0; i < 2 * N - 1; i += 2)
    {
        ans += vflip[1][i];
    }
    return ans;
}

int Calc1(int flip)
{
    vflip.assign(2, vector<int>(2 * N - 1, -1));
    dfs(1, 1, flip);
    int ans = 0;
    for (int i = N % 2; i < 2 * N - 1; i += 2)
    {
        ans += vflip[0][i];
    }
    for (int i = 1; i < 2 * N - 1; i += 2)
    {
        ans += vflip[1][i];
    }
    return ans;
}

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> N;
        for (int i = 0; i < N; ++i)
        {
            string s;
            cin >> s;
            for (int j = 0; j < N; ++j)
            {
                grid[i][j] = (s[j] == '#' ? 0 : 1);
            }
        }
        BuildGraph();
        int ans0 = min(Calc0(0), Calc0(1));
        int ans1 = min(Calc1(0), Calc1(1));
        cout << "Case #" << icase << ": " << ans0 + ans1 << endl;
	}
	return 0;
}
