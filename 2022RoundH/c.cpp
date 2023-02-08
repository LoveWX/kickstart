#include <bits/stdc++.h>
using namespace std;

const int SIZE=200000;
int A[SIZE];
vector<vector<int>> edge;
vector<int> mem;

int dp(int curr)
{
    if(mem[curr]!=-1) return mem[curr];
    int ans=1;
    for(int i:edge[curr])
    {
        ans+=dp(i);
    }
    return mem[curr]=ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        for(int i=0;i<N;++i)
        {
            cin>>A[i];
        }
        edge.assign(N,vector<int>());
        for(int i=1,x,y;i<N;++i)
        {
            cin>>x>>y;
            x-=1;
            y-=1;
            if(A[x]>A[y]) edge[x].push_back(y);
            else if(A[x]<A[y]) edge[y].push_back(x);
        }
        int ans=0;
        mem.assign(N,-1);
        for(int i=0;i<N;++i)
        {
            ans=max(ans,dp(i));
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
