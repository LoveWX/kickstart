#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
#include <algorithm>
using namespace std;

int N, P, H;
int obstacle[10][2];

double f(double R, double a, int xi, int yi, double x)
{
    return (x - xi)*(x - xi) + (a*x*(x - P) - yi)*(a*x*(x - P) - yi) - R*R;
}

double f1(double R, double a, int xi, int yi, double x)
{
    return 2 * (x - xi) + 2 * a*(a*x*(x - P) - yi)*(2 * x - P);
}

bool CheckA(double R, double a, int x, int y)
{
    static const double eps = 1e-9;
    int times = 1000;
    double x0, x1=0;
    do
    {
        x0 = x1;
        x1 = x0 - f(R, a, x, y, x0) / f1(R, a, x, y, x0);
        times -= 1;
    } while (times != 0 && abs(x1 - x0) > eps);
    return times != 0;
}

vector<array<double, 2>> CalcA0(double R, int rx, int ry)
{
    static const double eps = 1e-8;
    vector<array<double, 2>> ans;
    double upbound = 4.0 * H / P / P / eps;
    double upA = 4.0 * (H - R) / P / P / eps;
    double midA = (double)ry / rx / (rx - P)/(-eps);
    int left = midA, right = upbound, mid;
    while (left < right)
    {
        mid = (right - left) / 2 + left;
        if (CheckA(R, -mid*eps, rx, ry))
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    if (left/4*eps*P*P+R<H && -upA<-left)
    {
        ans.push_back({ -upA*eps, -left*eps });
    }
    if (ry - R >= 0)
    {
        int left = 0, right = midA, mid;
        while (left < right)
        {
            mid = (right - left) / 2 + left;
            if (CheckA(R, -mid*eps, rx, ry))
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        ans.push_back({ -(left)*eps,0 });
    }
    return ans;
}

bool CheckR0(double R)
{
    vector<array<double, 2>> tans = CalcA0(R, obstacle[0][0], obstacle[0][1]);
    for (int i = 1; i < N && !tans.empty(); ++i)
    {
        vector<array<double, 2>> va = move(tans);
        vector<array<double, 2>> vb = CalcA0(R, obstacle[i][0], obstacle[i][1]);
        for (array<double, 2> &a : va)
        {
            for (array<double, 2> &b : vb)
            {
                if (a[0] <= b[1] && b[0] <= a[1])
                {
                    tans.push_back({ max(a[0],b[0]),min(a[1],b[1]) });
                }
            }
        }
    }
    return !tans.empty();
}

array<double, 2> CalcA(double R, int rx, int ry)
{
    static const double eps = 1e-8;
    array<double, 2> ans;
    double upbound = 4.0 * H / P / P / eps;
    // double upA = 4.0 * (H - R) / P / P / eps;
    double centerA = (double)ry / rx / (rx - P)/(-eps);

    long long left = centerA, right = upbound, mid;
    while (left < right)
    {
        mid = (right - left) / 2 + left;
        if (CheckA(R, -mid*eps, rx, ry))
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    ans[1]=left*eps;

    left = 0, right = centerA;
    while (left < right)
    {
        mid = (right - left) / 2 + left;
        if (CheckA(R, -mid*eps, rx, ry))
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    if (left==0 && ry - R >= 0)
    {
        left+=1;
    }
    ans[0]=left*eps;
    return ans;
}

bool CheckR(double R)
{
    vector<array<double, 2>> aInterval(N);
    for(int i=0;i<N;++i)
    {
        aInterval[i]=CalcA(R, obstacle[i][0], obstacle[i][1]);
    }
    sort(aInterval.begin(),aInterval.end());
    if(0<aInterval[0][0]) return true;
    array<double, 2> ai=aInterval[0];
    double upA = 4.0 * (H - R) / P / P;
    for(int i=1;i<N;++i)
    {
        if(ai[1]<aInterval[i][0]) return true;
        ai[0]=min(ai[0],aInterval[i][0]);
        ai[1]=max(ai[1],aInterval[i][1]);
    }
    return ai[1]<upA;
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
        }
        int left = 1, right = 1e9, mid;
        while (left < right)
        {
            mid = (right - left) / 2 + left;
            if (CheckR(mid*1e-6))
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        cout << "Case #" << icase << ": " << fixed << setprecision(6) << (left - 1)*1e-6 << endl;
	}
	return 0;
}
