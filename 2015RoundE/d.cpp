#include <iostream>
#include <utility>
using namespace std;

int n;
long long a[200001];
long long p[200001] = { 0 };
long long d[200001] = { 0 };

long long CountSmallerOrEqual(long long val)
{
    long long ans = 0, sum = 0;
    int left = 1;
    for (int right = 1; right <= n; ++right)
    {
        sum += a[right];
        while (left <= right && sum>val)
        {
            sum -= a[left++];
        }
        ans += right - left + 1;
    }
    return ans;
}

pair<long long, long long> SumCountSmaller(long long val)
{
    long long ansSum = 0, ansCount = 0, sum = 0;
    int right = n;
    for (int left = n; left > 0; --left)
    {
        sum += a[left];
        while (left <= right && sum >= val)
        {
            sum -= a[right--];
        }
        ansSum += (right + 1) * (p[right] - p[left - 1]) - (d[right] - d[left - 1]);
        ansCount += right - left + 1;
    }
    return {ansSum, ansCount};
}

long long CalcKthSubarraySum(long long k)
{
    long long left = 0, right = p[n] + 1, mid;
    while (left<right)
    {
        mid = (right - left) / 2 + left;
        if (CountSmallerOrEqual(mid)<k)
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

long long CalcFirstKthSum(long long k)
{
    long long Kval = CalcKthSubarraySum(k);
    pair<long long, long long> pSmaller = SumCountSmaller(Kval);
    return pSmaller.first + (k - pSmaller.second)*Kval;
}

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        int q;
        long long x, y;
        cin >> n >> q;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            p[i] = p[i - 1] + a[i];
            d[i] = d[i - 1] + i*a[i];
        }
        cout << "Case #" << icase << ": " << endl;
        for (; q>0; --q)
        {
            cin >> x >> y;
            cout << CalcFirstKthSum(y) - CalcFirstKthSum(x - 1) << endl;
        }
    }
    return 0;
}
