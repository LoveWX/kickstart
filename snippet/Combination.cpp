//用DP的方法计算组合数，中间计算过程不会溢出，中间结果可以求余
//C(n,m)=C(n-1,m-1)+C(n-1,m)
long long mod = 1e9 + 7;
vector<vector<long long>> c(N,vector<long long>(N,-1));

long long C(int n, int m)
{
    if (m > n)
    {
        return 0;
    }
    if (m == 0 || m == n)
    {
        return 1;
    }
    if (c[n][m] != -1)
    {
        return c[n][m];
    }
    return c[n][m] = (C(n - 1, m - 1) + C(n - 1, m)) % mod;
}
