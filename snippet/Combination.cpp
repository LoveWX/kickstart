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
const int SIZE=100000;
long long fact[SIZE+1];// fact[i] = i! % mod
long long invf[SIZE+1];
//求a^b%mod
long long PowerMod(long long a,long long b)
{
    long long ans=1;
    for(;b;b>>=1){
        if((b&1)!=0) ans=ans*a%mod;
        a=a*a%mod;
    }
    return ans;
}
//利用费马小定理a^(p-1)=1 mod p 可知：a^(-1) = a^(p-2) mod p
inline long long Inv(long long a,long long p=mod-2)
{
    return PowerMod(a,p);
}
int init=[]{
    fact[0]=1;
    fact[1]=1;
    for(int i=2;i<=SIZE;++i){
        fact[i]=fact[i-1]*i%mod;
    }
    invf[SIZE]=Inv(fact[SIZE]);
    for(int i=SIZE;i>0;--i){
        invf[i-1]=invf[i]*i%mod;
    }
    return 0;
}();
inline long long C(int n,int m)
{
    return fact[n]*invf[m]%mod*invf[n-m]%mod;
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

扩展欧几里得算法（Extended Euclidean algorithm, EXGCD）,常用于求ax+by=gcd(a,b)的一组可行解．
设:
ax1 + by1 = gcd(a, b)
bx2 + (a mod b)y2 = gcd(b, a mod b)
由欧几里德定理可知: gcd(a, b) = gcd(b, a mod b)
所以 ax1 + by1 = bx2 + (a mod b)y2
又因为 a mod b = a - (floor(a/b) * b)
所以 ax1 + by1 = bx2 + (a - floor(a/b) * b)y2
               = ay2 + bx2 - floor(a/b)*by2
               = ay2 + b(x2 - floor(a/b)*y2)
所以x1 = y2, y1 = x2 - floor(a/b)y2
将x2,y2不断带入递归求解直至gcd为0递归x=1,y=0回去求解
值域分析：ax1 + by1 = gcd(a, b)的解有无数个，
若b!=0，扩展欧几里德算法求出的可行解必有|x|<=b,|y|<=a
//函数返回的值为gcd，在这个过程中计算x,y 即可
int ExGCD(int a, int b, int &x, int &y)
{
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int d=ExGCD(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-(a/b)*y;
    return d;
}
也可以用迭代的方法避免递归
int ExGCD(int a, int b, int& x, int& y)
{
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
参考：https://oi-wiki.org/math/number-theory/gcd/#%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95
