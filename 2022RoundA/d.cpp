#include <bits/stdc++.h>
using namespace std;

const int D=13;
string s;
long long mem[9*D+1][9*D+1][D][2][2];

long long dp(int product,int sum,int pos,bool leading,bool limit)
{
    if(sum<0) return 0;
    if(pos==-1)
    {
        return (product==1 && sum==0) ? 1 : 0;
    }
    long long &ans=mem[product][sum][pos][leading][limit];
    if(ans!=-1) return ans;
    ans=0;
    int top=limit ? s[pos]-'0' : 9;
    for(int i=0;i<=top;++i)
    {
        if(leading && i==0)
        {
            ans+=dp(product,sum-i,pos-1,true,limit && i==top);
        }
        else
        {
            ans+=dp(i==0 ? 1 : product/__gcd(product,i),sum-i,pos-1,false,limit && i==top);
        }
    }
    return ans;
}

long long Calc(long long num)
{
    s=to_string(num);
    reverse(s.begin(),s.end());
    long long ans=0;
    int n=s.size();
    for(int sum=9*n;sum>0;--sum)
    {
        memset(mem,-1,sizeof(mem));
        ans+=dp(sum,sum,n-1,true,true);
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
        long long A,B;
        cin>>A>>B;
        long long ans=Calc(B)-Calc(A-1);
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
