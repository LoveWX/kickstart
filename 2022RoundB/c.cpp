#include <bits/stdc++.h>
using namespace std;

constexpr int SIZE=400;
int N,D;
vector<int> vi;
vector<vector<vector<long long>>> mem;

int Calc(int src,int dst)
{
    int d=abs(src-dst);
    return min(d,D-d);
}

long long dp(int le,int ri,int end)
{
    long long &ans=mem[le][ri][end];
    if(ans!=-1) return ans;
    if(end==0)
    {
        ans=min(dp(le+1,ri,0)+Calc(vi[le+1],vi[le]),dp(le+1,ri,1)+Calc(vi[ri],vi[le]));
    }
    else
    {
        ans=min(dp(le,ri-1,0)+Calc(vi[le],vi[ri]),dp(le,ri-1,1)+Calc(vi[ri-1],vi[ri]));
    }
    return ans;
}

int main()
{
    vi.assign(SIZE,0);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>D;
        for(int i=0;i<N;++i)
        {
            cin>>vi[i];
        }
        mem.assign(N,vector<vector<long long>>(N,vector<long long>(2,-1)));
        for(int i=0;i<N;++i)
        {
            mem[i][i][0]=mem[i][i][1]=0;
        }
        long long ans1=dp(0,N-1,0)+Calc(vi[0],0);
        long long ans2=dp(0,N-1,1)+Calc(vi[N-1],0);
        cout<<"Case #"<<icase<<": "<<min(ans1,ans2)<<endl;
    }
    return 0;
}
