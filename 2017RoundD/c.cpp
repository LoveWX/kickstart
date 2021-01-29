#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
using namespace std;

int N, P, H;
int obstacle[10][2];

double f(double R, double a, int xi, int yi, double x)
{
    return (x - xi) * (x - xi) + (a*x*(x - P) - yi) * (a*x*(x - P) - yi) - R*R;
}

double f1(double R, double a, int xi, int yi, double x)
{
    return 2 * (x - xi) + 2 * a * (a*x*(x - P) - yi) * (2 * x - P);
}

bool CheckA(double R, double a, int x, int y)
{
    static const double eps = 1e-10;
    int times = 1000;
    double x0, x1 = 0;
    do
    {
        x0 = x1;
        x1 = x0 - f(R, a, x, y, x0) / f1(R, a, x, y, x0);
        times -= 1;
    } while (times != 0 && abs(x1 - x0) > eps);
    return times != 0;
}

vector<array<double, 2>> CalcA(double R, int cx, int cy)
{
    vector<array<double, 2>> ans;
    double upboundA = 4.0 * (H - R) / P / P;
    double centerA = (double)cy / cx / (P - cx);
    if (cx > R)
    {
        double left = centerA, right = upboundA + 1, mid;
        while (right - left>1e-10)
        {
            mid = (left + right) * 0.5;
            if (CheckA(R, -mid, cx, cy))
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }
        if (left < upboundA)
        {
            ans.push_back({left, upboundA});
        }
    }

    if (cy - R >= 0)
    {
        double left = 0, right = centerA, mid;
        while (right - left > 1e-10)
        {
            mid = (left + right) * 0.5;
            if (CheckA(R, -mid, cx, cy))
            {
                right = mid;
            }
            else
            {
                left = mid;
            }
        }
        ans.push_back({0.0, left});
    }
    return ans;
}

bool CheckR(double R)
{
    vector<array<double, 2>> intervals;
    intervals.push_back({0.0, 4.0 * (H - R) / P / P});
    for (int i = 0; i<N && !intervals.empty(); ++i)
    {
        vector<array<double, 2>> next;
        vector<array<double, 2>> curr = CalcA(R, obstacle[i][0], obstacle[i][1]);
        for (array<double, 2> &a : intervals)
        {
            for (array<double, 2> &b : curr)
            {
                if (a[0] <= b[1] && b[0] <= a[1])
                {
                    next.push_back({max(a[0], b[0]), min(a[1], b[1])});
                }
            }
        }
        intervals = move(next);
    }
    return !intervals.empty();
}

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        cin >> N >> P >> H;
        for (int i = 0; i < N; ++i)
        {
            cin >> obstacle[i][0] >> obstacle[i][1];
            if (obstacle[i][0] * 2 > P) obstacle[i][0] = P - obstacle[i][0];
        }
        double left = 0.0, right = H, mid;
        while (right - left > 1e-10)
        {
            mid = (left + right) * 0.5;
            if (CheckR(mid))
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }
        cout << "Case #" << icase << ": " << fixed << setprecision(6) << left << endl;
    }
    return 0;
}
