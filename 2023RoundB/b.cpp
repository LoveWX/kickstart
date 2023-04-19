#include <bits/stdc++.h>
using namespace std;

//Extended Euclidean algorithm to calculate s,t,gcd(a,b) while as+bt=gcd(a,b)
//input:{r0,r1}={a,b}; output:{s,t,gcd(a,b)}
array<int64_t,3> ExtendedEuclidean(int64_t r0,int64_t r1)
{
    int64_t s0=1,s1=0;
    int64_t t0=0,t1=1;
    for(;r1!=0;)
    {
        int64_t q=r0/r1;
        int64_t tmpr=r0-r1*q;
        r0=r1;
        r1=tmpr;
        int64_t tmps=s0-q*s1;
        s0=s1;
        s1=tmps;
        int64_t tmpt=t0-q*t1;
        t0=t1;
        t1=tmpt;
    }
    return {s0,t0,r0};
}

//The General Solution of Bezouts Equation ax+by=m is {x0+k*b/gcd(a,b),y=y0-k*a/gcd(a,b)}
//output:{x0,b,y0,a}; or empty if no solution
vector<int64_t> BezoutsEquation(int64_t a,int64_t b,int64_t m)
{
    auto coef=ExtendedEuclidean(a,b);
    if(m%coef[2]!=0) return {};
    m/=coef[2];
    return {m*coef[0],b/coef[2],m*coef[1],a/coef[2]};
}

int W,N,D;

long long Calc(int a,int b)
{
    long long ans=LLONG_MAX;
    long long n=N/gcd(D,N);
    auto a1=BezoutsEquation(D,N,a-b);
    if(!a1.empty())
    {
        ans=min(ans,(a1[0]%n+n)%n);
    }
    auto a2=BezoutsEquation(D,-N,b-a);
    if(!a2.empty())
    {
        ans=min(ans,(a2[0]%n+n)%n);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>W>>N>>D;
        vector<int> wheel(W);
        for(int &i:wheel)
        {
            cin>>i;
            i-=1;
        }
        long long ans=0;
        for(int i=0,j=W-1;i<j;++i,--j)
        {
            long long tans=Calc(wheel[i],wheel[j]);
            if(tans==LLONG_MAX)
            {
                ans=-1;
                break;
            }
            ans+=tans;
        }
        if(ans<0)
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
        }
        else
        {
            cout<<"Case #"<<icase<<": "<<ans<<endl;
        }
    }
    return 0;
}
