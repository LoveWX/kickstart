#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void calcx(vector<vector<int>> &vp, vector<long long> &ans)
{
	int n = vp.size();
	sort(vp.begin(), vp.end(), [](vector<int> &a, vector<int> &b) {
		return a[0] < b[0];
	});
	long long sum = 0, t = vp[0][0];
	for (vector<int> &vi : vp)
	{
		sum += vi[0] - t;
	}
	ans[vp[0][2]] = sum;
	for (int i = 1; i < n; ++i)
	{
		sum += (long long)(vp[i][0] - vp[i - 1][0])*(i + i - n);
		ans[vp[i][2]] = sum;
	}
}

void calcy(vector<vector<int>> &vp, vector<long long> &ans)
{
	int n = vp.size();
	sort(vp.begin(), vp.end(), [](vector<int> &a, vector<int> &b) {
		return a[1] < b[1];
	});
	long long sum = 0, t = vp[0][1];
	for (vector<int> &vi : vp)
	{
		sum += vi[1] - t;
	}
	ans[vp[0][2]] = sum;
	for (int i = 1; i < n; ++i)
	{
		sum += (long long)(vp[i][1] - vp[i - 1][1])*(i + i - n);
		ans[vp[i][2]] = sum;
	}
}

int main()
{
	int ncase, n;
	cin >> ncase;
	int x1, y1, x2, y2;
	for (int icase = 1; icase <= ncase; ++icase)
	{
		int count = 0;
		vector<vector<int>> vp;
		cin >> n;
		while (n--)
		{
			cin >> x1 >> y1 >> x2 >> y2;
			for (int i = x1; i <= x2; ++i)
			{
				for (int j = y1; j <= y2; ++j)
				{
					vp.push_back({ i,j,count++ });
				}
			}
		}
		vector<long long> sumx(count), sumy(count);
		calcx(vp, sumx);
		calcy(vp, sumy);
		long long minv = 0x7FFFFFFFFFFFFFFFLL, t;
		for (vector<int> &vi : vp)
		{
			t = sumx[vi[2]] + sumy[vi[2]];
			if (t < minv)
			{
				minv = t;
				x1 = vi[0];
				y1 = vi[1];
			}
			else if (t == minv)
			{
				if (vi[0] < x1 || (vi[0] == x1 && vi[1] < y1))
				{
					x1 = vi[0];
					y1 = vi[1];
				}
			}
		}
		cout << "Case #" << icase << ": " << x1 << ' ' << y1 << ' ' << minv << endl;
	}
	return 0;
}
