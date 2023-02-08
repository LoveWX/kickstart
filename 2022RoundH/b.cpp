#include <bits/stdc++.h>
using namespace std;

const int SIZE=100000;
vector<int> mem;

void Init()
{
    mem.assign(SIZE+1,-1);
    for(int i=0;i<=5;++i)
    {
        mem[i]=i;
    }
}

int dp(int curr)
{
    if(mem[curr]!=-1) return mem[curr];
    int ans=min(curr,dp(curr-1)+1);
    for(int i=2;i*i<=curr;++i)
    {
        if(curr%i!=0) continue;
        ans=min(ans,dp(i)+4+(curr-i)/i*2+(curr-i)%i);
        int j=curr/i;
        ans=min(ans,dp(j)+4+(curr-j)/j*2+(curr-j)%j);
    }
    return mem[curr]=ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Init();
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int L;
        cin>>L;
        cout<<"Case #"<<icase<<": "<<dp(L)<<endl;
    }
    return 0;
}
