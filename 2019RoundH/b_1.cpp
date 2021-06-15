#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = INT_MAX >> 10;
const int SIZE = 100;
int N;
int m0[SIZE][SIZE], m1[SIZE][SIZE];

void FlipDiagonal0(int(*m)[SIZE], int x, int y)
{
    for (int i = x + 1, j = y + 1; i < N && j < N; ++i, ++j)
    {
        m[i][j] = 1 - m[i][j];
    }
    for (int i = x, j = y; i >= 0 && j >= 0; --i, --j)
    {
        m[i][j] = 1 - m[i][j];
    }
}

int CheckDiagonal0(int(*m)[SIZE], int x, int y)
{
    int count[2] = { 0, 0 };
    for (int i = x + 1, j = y + 1; i < N && j < N; ++i, ++j)
    {
        count[m[i][j]] += 1;
    }
    for (int i = x, j = y; i >= 0 && j >= 0; --i, --j)
    {
        count[m[i][j]] += 1;
    }
    if (count[0] != 0 && count[1] != 0) return -1;
    return count[0] != 0 ? 0 : 1;
}

void FlipDiagonal1(int(*m)[SIZE], int x, int y)
{
    for (int i = x + 1, j = y - 1; i < N && j >= 0; ++i, --j)
    {
        m[i][j] = 1 - m[i][j];
    }
    for (int i = x, j = y; i >= 0 && j < N; --i, ++j)
    {
        m[i][j] = 1 - m[i][j];
    }
}

int CheckDiagonal1(int(*m)[SIZE], int x, int y)
{
    int count[2] = { 0, 0 };
    for (int i = x + 1, j = y - 1; i < N && j >= 0; ++i, --j)
    {
        count[m[i][j]] += 1;
    }
    for (int i = x, j = y; i >= 0 && j < N; --i, ++j)
    {
        count[m[i][j]] += 1;
    }
    if (count[0] != 0 && count[1] != 0) return -1;
    return count[0] != 0 ? 0 : 1;
}

int Calc0(int(*m)[SIZE], bool flip)
{
    int ans = 0;
    if (flip)
    {
        ans = 1;
        FlipDiagonal0(m, 0, 0);
    }
    for (int i = 0; i < N; ++i)
    {
        if (m[i][i] == 1)
        {
            ans += 1;
            FlipDiagonal1(m, i, i);
        }
    }
    for (int i = 2; i < N; i += 2)
    {
        int t = CheckDiagonal0(m, i, 0);
        if (t == -1) return INF;
        ans += t;
    }
    for (int j = 2; j < N; j += 2)
    {
        int t = CheckDiagonal0(m, 0, j);
        if (t == -1) return INF;
        ans += t;
    }
    return ans;
}

int Calc1(int(*m)[SIZE], bool flip)
{
    int ans = 0;
    if (flip)
    {
        ans = 1;
        FlipDiagonal1(m, N % 2, N - 1);
    }
    for (int i = N % 2, j = N - 1; i < N; ++i, --j)
    {
        if (m[i][j] == 1)
        {
            ans += 1;
            FlipDiagonal0(m, i, j);
        }
    }
    for (int i = N % 2 + 2; i < N; i += 2)
    {
        int t = CheckDiagonal1(m, i, N - 1);
        if (t == -1) return INF;
        ans += t;
    }
    for (int j = 1; j < N; j += 2)
    {
        int t = CheckDiagonal1(m, 0, j);
        if (t == -1) return INF;
        ans += t;
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
                m0[i][j] = m1[i][j] = (s[j] == '#' ? 0 : 1);
            }
        }
        int ans0 = min(Calc0(m0, false), Calc0(m1, true));
        int ans1 = min(Calc1(m0, false), Calc1(m1, true));
        cout << "Case #" << icase << ": " << ans0 + ans1 << endl;
	}
	return 0;
}
