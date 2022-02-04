#include <iostream>
#include <array>
#include <vector>
#include <cfloat>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

const int SIZE = 300;
const double dinf = 1e20;
vector<array<int, 2>> p;
double dis[SIZE][SIZE];
//lineSide[i][j]<0: bluePoint is on the left  side of vector pi to pj
//lineSide[i][j]>0: bluePoint is on the right side of vector pi to pj
int lineSide[SIZE][SIZE];
int N;

inline double CalcDistance(array<int, 2> &a, array<int, 2> &b)
{
    return sqrt((long long)(a[0] - b[0])*(a[0] - b[0]) + (long long)(a[1] - b[1])*(a[1] - b[1]));
}

inline array<int, 2> operator - (const array<int, 2> &a, const array<int, 2> &b)
{
    return {a[0] - b[0], a[1] - b[1]};
}

int sign(long long a)
{
    if (a == 0LL) return 0;
    return a > 0LL ? 1 : -1;
}

inline long long CrossProduct(const array<int, 2> &a, const array<int, 2> &b)
{
    return (long long)a[0] * b[1] - (long long)a[1] * b[0];
}

inline long long DotProduct(const array<int, 2> &a, const array<int, 2> &b)
{
    return (long long)a[0] * b[0] + (long long)a[1] * b[1];
}

int main()
{
    p.reserve(SIZE);
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> N;
        p.resize(N);
        for (array<int, 2> &a : p)
        {
            cin >> a[0] >> a[1];
        }
        int x0, y0;
        cin >> x0 >> y0;
        for (array<int, 2> &a : p)
        {
            a[0] -= x0;
            a[1] -= y0;
        }
        for (int i = 0; i < N; ++i)
        {
            dis[i][i] = 0.0;
            for (int j = i + 1; j < N; ++j)
            {
                dis[i][j] = dis[j][i] = CalcDistance(p[i], p[j]);
            }
        }
        for (int i = 0; i < N; ++i)
        {
            lineSide[i][i] = 0;
            for (int j = i + 1; j < N; ++j)
            {
                lineSide[i][j] = -sign(CrossProduct(p[i], p[j] - p[i]));
                lineSide[j][i] = -lineSide[i][j];
            }
        }
        
        double ans = dinf;
        for (int i = 0; i < N; ++i)
        {
            vector<double> vdis(N, dinf);
            vector<int> vpl, vpr, vpm;
            for (int j = 0; j < N; ++j)
            {
                if (i == j) continue;
                if      (lineSide[i][j] < 0) vpr.push_back(j);
                else if (lineSide[i][j] > 0) vpl.push_back(j);
                else if (DotProduct(p[i], p[j]) < 0) vpm.push_back(j);
            }
            for (int a : vpr)
            {
                vdis[a] = dis[i][a];
            }
            for (int b : vpm)
            {
                for (int a : vpr)
                {
                    vdis[b] = min(vdis[b], vdis[a] + dis[a][b]);
                }
            }
            for (int c : vpl)
            {
                for (int b : vpm)
                {
                    vdis[c] = min(vdis[c], vdis[b] + dis[b][c]);
                }
                for (int a : vpr)
                {
                    if (lineSide[a][c] >= 0) continue;
                    vdis[c] = min(vdis[c], vdis[a] + dis[a][c]);
                }
            }
            for (int c : vpl)
            {
                ans = min(ans, vdis[c] + dis[c][i]);
            }
        }
        if (ans >= dinf) cout << "Case #" << icase << ": IMPOSSIBLE" << endl;
        else cout << "Case #" << icase << ": " << fixed << setprecision(8) << ans << endl;
	}
	return 0;
}
