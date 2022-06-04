#include <bits/stdc++.h>
using namespace std;

const long long mod=1e9+7;
const int SIZE=400;
long long fact[SIZE+1];
long long invFact[SIZE+1];
string s;
long long mem[SIZE][SIZE][SIZE+1];

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

inline long long Inv(long long a,long long p=mod-2)
{
    return PowerMod(a,p);
}

void Init()
{
    fact[0]=fact[1]=1;
    invFact[0]=invFact[1]=1;
    for(int i=2;i<=SIZE;++i)
    {
        fact[i]=fact[i-1]*i%mod;
        invFact[i]=Inv(fact[i]);
    }
}

long long dp(int left,int right,int len)
{
    if(len==0) return 1;
    if(left>right) return 0;
    long long &ans=mem[left][right][len];
    if(ans!=-1) return ans;
    ans=0;
    if(s[left]==s[right])
    {
        if(left==right) ans=(len==1 ? 1 : 0);
        else ans=dp(left+1,right-1,len-2);
    }
    ans+=dp(left+1,right,len)+dp(left,right-1,len)-dp(left+1,right-1,len);
    ans=(ans%mod+mod)%mod;
    return ans;
}

int main()
{
    Init();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N>>s;
        memset(mem,-1,sizeof(mem));
        long long ans=0;
        for(int len=0;len<N;++len)
        {
            ans+=dp(0,N-1,len)*fact[len]%mod*fact[N-len]%mod;
        }
        ans%=mod;
        ans=ans*invFact[N]%mod;
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
