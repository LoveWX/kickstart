#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE = 100000;
int x[SIZE], y[SIZE];
int r[SIZE], s[SIZE];
int A[SIZE], B[SIZE];
int N, K, c, d, e1, e2, f;
int apresum[SIZE], bpresum[SIZE];
int amax[SIZE], amin[SIZE];
int bmax[SIZE], bmin[SIZE];
int n; // bit used
long long bit[SIZE + 3];

void update(int idx, long long diff)
{
    while (idx <= n)
    {
        bit[idx] += diff;
        idx += (idx & -idx);
    }
}

long long prefixSum(int idx)
{
    long long sum = 0;
    while (idx != 0)
    {
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

long long rangeSum(int idx1, int idx2)
{
    return prefixSum(idx2) - prefixSum(idx1 - 1);
}

long long CountGreater(map<int,int> &m, int *P, int X)
{
    memset(bit, 0, (n + 1) * sizeof(long long));
    long long ans = 0;
    for (int i = N - 1; i >= 0; --i)
    {
        ans += rangeSum(m.upper_bound(P[i] + X)->second, n);
        update(m[P[i]], 1);
        if (P[i] > X)
        {
            ++ans;
        }
    }
    return ans;
}

void CalcKMaxSubarraySum(int *P, int *vmax)
{
    map<int, int> m1;
    for (int i = 0; i < N; ++i)
    {
        m1[P[i]];
    }
    m1[0x7FFFFFFF];
    n = 1;
    for (auto it = m1.begin(); it != m1.end(); ++it)
    {
        it->second = n++;
    }
    int left = -100000000, right = 100000001, mid;
    while (left < right)
    {
        mid = (right - left) / 2 + left;
        if (CountGreater(m1, P, mid) >= K)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    int count = 0;
    for (int i = 0; i<N; ++i)
    {
        if (P[i] > left)
        {
            vmax[count++] = P[i];
        }
    }
    map<int, int> m;
    for (int i = N - 1; i >= 0 && count < K; --i)
    {
        for (auto it = m.upper_bound(P[i] + left); it != m.end(); ++it)
        {
            for (int j = it->second; j > 0; --j)
            {
                vmax[count++] = it->first - P[i];
            }
        }
        m[P[i]] += 1;
    }
    for (; count < K; ++count)
    {
        vmax[count] = left;
    }
}

long long CountGreaterProduct(int *a, int *b, int len, long long X)
{
    long long ans = 0;
    for (int i = 0; i < len; ++i)
    {
        long long ai = a[i];
        if (ai >= 0)
        {
            int left = 0, right = len, mid;
            while (left < right)
            {
                mid = (right - left) / 2 + left;
                if (ai * b[mid] > X)
                {
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }
            ans += len - left;
        }
        else
        {
            int left = 0, right = len, mid;
            while (left < right)
            {
                mid = (right - left) / 2 + left;
                if (ai * b[mid] > X)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid;
                }
            }
            ans += left;
        }
    }
    return ans;
}

long long CalcLarge()
{
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
    long long left = -10000000000000000LL, right = 10000000000000001LL, mid;
    while (left < right)
    {
        mid = (right - left) / 2 + left;
        if (CountGreaterProduct(amax, bmax, K, mid) + CountGreaterProduct(amin, bmin, K, mid) >= K)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}

long long CalcSmall()
{
    int len = N * (N + 1) / 2;
    int count = 0;
    for (int i = 0; i < N; ++i)
    {
        amax[count++] = apresum[i];
        for (int j = i + 1; j < N; ++j)
        {
            amax[count++] = apresum[j] - apresum[i];
        }
    }
    sort(amax, amax + count);
    count = 0;
    for (int i = 0; i < N; ++i)
    {
        bmax[count++] = bpresum[i];
        for (int j = i + 1; j < N; ++j)
        {
            bmax[count++] = bpresum[j] - bpresum[i];
        }
    }
    sort(bmax, bmax + count);
    long long left = -10000000000000000LL, right = 10000000000000001LL, mid;
    while (left < right)
    {
        mid = (right - left) / 2 + left;
        if (CountGreaterProduct(amax, bmax, len, mid) >= K)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
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
        apresum[0] = A[0];
        bpresum[0] = B[0];
        for (int i = 1; i < N; ++i)
        {
            x[i] = (c*x[i - 1] + d*y[i - 1] + e1) % f;
            y[i] = (d*x[i - 1] + c*y[i - 1] + e2) % f;
            r[i] = (c*r[i - 1] + d*s[i - 1] + e1) % 2;
            s[i] = (d*r[i - 1] + c*s[i - 1] + e2) % 2;
            A[i] = (r[i] % 2 == 0 ? x[i] : -x[i]);
            B[i] = (s[i] % 2 == 0 ? y[i] : -y[i]);
            apresum[i] = apresum[i - 1] + A[i];
            bpresum[i] = bpresum[i - 1] + B[i];
        }
        long long ans;
        if(N < 200 || (long long)N * (N + 1) / 2 <= 2 * K)
        {
            ans = CalcSmall();
        }
        else
        {
            ans = CalcLarge();
        }
        cout << "Case #" << icase << ": " << ans << endl;
    }
    return 0;
}
