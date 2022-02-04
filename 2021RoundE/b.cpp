#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int R,C,K;
int r1,r2,c1,c2;

long long CalcBorder(int le,int ri,int up,int dn)
{
    long long ans=0LL;
    if(c1!=1) ans+=le/K+(le%K==0 ? 0 : 1);
    if(c2!=C) ans+=ri/K+(ri%K==0 ? 0 : 1);
    if(r1!=1) ans+=up/K+(up%K==0 ? 0 : 1);
    if(r2!=R) ans+=dn/K+(dn%K==0 ? 0 : 1);
    return ans;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>R>>C>>K;
        cin>>r1>>c1>>r2>>c2;
        long long n=r2-r1+1,m=c2-c1+1;
        long long ans=INT_MAX;
        ans=min(ans,CalcBorder(r2,n,m,m));
        ans=min(ans,CalcBorder(n,r2,m,m));
        ans=min(ans,CalcBorder(R-r1+1,n,m,m));
        ans=min(ans,CalcBorder(n,R-r1+1,m,m));
        ans=min(ans,CalcBorder(n,n,c2,m));
        ans=min(ans,CalcBorder(n,n,m,c2));
        ans=min(ans,CalcBorder(n,n,C-c1+1,m));
        ans=min(ans,CalcBorder(n,n,m,C-c1+1));
        ans+=n*m-1+((n-1)/K)*((m-1)/K);
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
