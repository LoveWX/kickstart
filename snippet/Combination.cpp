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

//求a^b%mod
long long PowerMod(long long a,long long b)
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
inline long long Inv(long long a,long long p=mod-2)
{
    return PowerMod(a,p);
}

void Init()
{
    fact[0]=1;
    fact[1]=1;
    for(int i=2;i<=SIZE;++i)
    {
        fact[i]=fact[i-1]*i%mod;
    }
}

inline long long C(int n,int m)
{
    return fact[n]*Inv(fact[m])%mod*Inv(fact[n-m])%mod;
}

当模数不太大(mod~10^6)时,可以使用Lucas定理求解组合数.
更准确地说,只要模数的唯一分解中所有素数幂的和在10^6规模时就可以使用该方法,因为算法的预处理大致相当于这一规模．
注意这里可以用于非素数模数时求解组合数
Lucas定理:对于素数p,有:
C(n, k) = C(floor(n/p), floor(k/p)) * C(n%p, k%p) % p
其中,当 n<k 时,二项式系数C(n, k)规定为0.

long long Lucas(long long n,long long k,long long p)
{
	if(k==0) return 1LL;
	return C(n%p,k%p,p)*Lucas(n/p,k/p,p)%p;
}

其中函数C(n,k,p)表示预处理得到的小规模的组合数
递归至多进行log_p n次，因而算法的复杂度为O(f(p)+g(p)log_p n),
其中,f(p)为预处理组合数的复杂度; g(p)为单次计算组合数的复杂度．
