#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE = 100;
int x[SIZE], y[SIZE];
int r[SIZE], s[SIZE];
int A[SIZE], B[SIZE];
int N, K, c, d, e1, e2, f;
int apresum[SIZE], bpresum[SIZE];
int amax[SIZE], amin[SIZE];
int bmax[SIZE], bmin[SIZE];
int n; // bit used
int bit[SIZE + SIZE + 1];

void update(int idx, int diff)
{
    while (idx <= n)
    {
        bit[idx] += diff;
        idx += (idx & -idx);
    }
}

int prefixSum(int idx)
{
    int sum = 0;
    while (idx != 0)
    {
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

int rangeSum(int idx1, int idx2)
{
    return prefixSum(idx2) - prefixSum(idx1 - 1);
}

int CalcGreater(int *P, int X)
{
    map<int, int> m;
    for (int i = 0; i < N; ++i)
    {
        m[P[i]];
    }
    for (int i = 0; i < N; ++i)
    {
        m[P[i] + X];
    }
    n = 1;
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        it->second = n++;
    }
    memset(bit, 0, (n + 1) * sizeof(int));
    int ans = 0;
    for (int i = N - 1; i >= 0; --i)
    {
        update(m[P[i]], 1);
        ans += rangeSum(m[P[i] + X] + 1, n);
    }
    return ans;
}

void CalcKMaxSubarraySum(int *P, int *vmax)
{
    int left = -100000000, right = 100000001, mid;
    while (left < right)
    {
        mid = (right - left) / 2 + left;
        if (CalcGreater(apresum, mid) > K - 1)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (P[i] > left)
        {
            vmax[count++] = P[i];
        }
        for (int j = N - 1; j >= 0; --j)
        {
            if (P[j] - P[i] > left)
            {
                vmax[count++] = P[j] - P[i];
            }
            else
            {
                break;
            }
        }
    }
    for (; count < K; ++count)
    {
        vmax[count] = left;
    }
}

long long CalcGreaterProduct(int X)
{
    int ans = 0;
    for (int i = 0; i < K; ++i)
    {

    }
}

void Calc()
{
    apresum[0] = A[0];
    bpresum[0] = B[0];
    for (int i = 1; i < N; ++i)
    {
        apresum[i] = apresum[i - 1] + A[i];
        bpresum[i] = bpresum[i - 1] + B[i];
    }
    CalcKMaxSubarraySum(apresum, amax);
    CalcKMaxSubarraySum(bpresum, bmax);
    sort(amax, amax + K);
    sort(bmax, bmax + K);
    for (int i = 0; i < N; ++i)
    {
        apresum[i] = -apresum[i];
        bpresum[i] = -bpresum[i];
    }
    CalcKMaxSubarraySum(apresum, amin);
    CalcKMaxSubarraySum(bpresum, bmin);
    for (int i = 0; i < K; ++i)
    {
        amin[i] = -amin[i];
        bmin[i] = -bmin[i];
    }
    sort(amin, amin + K);
    sort(bmin, bmin + K);
    for(int i)
}

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> N >> K >> A[0] >> B[0] >> c >> d >> e1 >> e2 >> f;
        x[0] = A[0];
        y[0] = B[0];
        r[0] = 0;
        s[0] = 0;
        for (int i = 1; i < N; ++i)
        {
            x[i] = (c*x[i - 1] + d*y[i - 1] + e1) % f;
            y[i] = (d*x[i - 1] + c*y[i - 1] + e2) % f;
            r[i] = (c*r[i - 1] + d*s[i - 1] + e1) % 2;
            s[i] = (d*r[i - 1] + c*s[i - 1] + e2) % 2;
            A[i] = (r[i] % 2 == 0 ? x[i] : -x[i]);
            B[i] = (s[i] % 2 == 0 ? y[i] : -y[i]);
        }
        
	}
	return 0;
}
