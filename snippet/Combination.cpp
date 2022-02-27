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

//也可以使用公式:C(n,m)=n!/(m!*(n-m)!) 直接计算
//需要使用费马小定理和乘法逆元来处理其中的除法
const long long mod=1e9+7;
const int SIZE=1000000;
long long fact[SIZE+1];// fact[i] = i! % mod
long long invFact[SIZE+1]; // invFact[SIZE+1] = (i!)^(-1) % mod

//求a^b%mod
long long PowerMod(long long a,int b)
{
    long long ans=1;
    while(b!=0)
    {
        if((b&1)!=0)
        {
            ans=ans*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}

//利用费马小定理a^(p-1)=1 mod p 可知：a^(-1) = a^(p-2) mod p
inline long long Inv(long long a,int p=mod-2)
{
    return PowerMod(a,p);
}

void Init()
{
    fact[0]=1;
    fact[1]=1;
    invFact[0]=1;
    invFact[1]=1;
    for(int i=2;i<=SIZE;++i)
    {
        fact[i]=fact[i-1]*i%mod;
        invFact[i]=Inv(fact[i]);
    }
}

inline long long C(int n,int m)
{
    return fact[n]*invFact[m]%mod*invFact[n-m]%mod;
}
