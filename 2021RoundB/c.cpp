#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN=31623;//sqrt(10^9)
const int PRIMECOUNT=3401;
vector<int> primes;

void CalcPrimes()
{
    vector<bool> isPrime(MAXN,true);
    for(int i=2;i<MAXN;++i)
    {
        if(isPrime[i]) primes.push_back(i);
        for(int j=0;j<primes.size() && i*primes[j]<MAXN;++j)
        {
            isPrime[i*primes[j]]=false;
            if(i%primes[j]==0) break;
        }
    }
}

bool IsPrime(int num)
{
    if(num<=primes.back())
    {
        return binary_search(primes.begin(),primes.end(),num);
    }
    int n=upper_bound(primes.begin(),primes.end(),sqrt(num))-primes.begin();
    for(int i=0;i<n;++i)
    {
        if(num%primes[i]==0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    primes.reserve(PRIMECOUNT);
    CalcPrimes();
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        long long Z,ans;
        cin>>Z;
        int n=(int)sqrt(Z);
        int p0,p1,p2;
        for(p1=n;!IsPrime(p1);--p1);
        for(p2=n+1;!IsPrime(p2);++p2);
        ans=(long long)p1*p2;
        if(ans>Z)
        {
            for(p0=p1-1;!IsPrime(p0);--p0);
            ans=(long long)p1*p0;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
