#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<int> vs(401);
vector<vector<double>> vout;
int endL, endN;
double ansin;

double dp(int L, int N)
{
    if (vout[L][N] >= 0.0)
    {
        return vout[L][N];
    }
    int r = upper_bound(vs.begin(), vs.end(), N) - vs.begin() - 1;
    int c = N - vs[r];
    double in = 0.0;
    if (r < L)
    {
        in += dp(L - 1, N);
    }
    if (r - 1 >= 0 && c <= r - 1)
    {
        in += dp(L - 1, vs[r - 1] + c);
    }
    if (r - 1 >= 0 && 0 <= c - 1 && c - 1 <= r - 1)
    {
        in += dp(L - 1, vs[r - 1] + c - 1);
    }
    in *= (1.0 / 3);
    if (L == endL && N == endN)
    {
        ansin = in;
    }
    return vout[L][N] = max(0.0, in - 250.0);
}

int main()
{
    vs[0] = 0;
    for (int i = 1; i <= 400; ++i)
    {
        vs[i] = vs[i - 1] + i;
    }
	int ncase;
	cin >> ncase;
    int B, L, N;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> B >> L >> N;
        vout.assign(L, vector<double>(L*(1 + L) / 2, -1.0));
        vout[0][0] = B * 750 - 250;
        endL = L - 1;
        endN = N - 1;
        dp(endL, endN);
        cout << "Case #" << icase << ": "
            << fixed << setprecision(8) << ansin - vout[endL][endN] << endl;
	}
	return 0;
}
