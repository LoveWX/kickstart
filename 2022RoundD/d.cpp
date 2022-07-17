#include <bits/stdc++.h>
using namespace std;

int limit;
vector<vector<int>> edge;

void dfs(int curr,set<int> &visited)
{
    if(visited.count(curr)!=0) return;
    visited.insert(curr);
    if(visited.size()>limit) return;
    for(int i:edge[curr])
    {
        dfs(i,visited);
        if(visited.size()>limit) break;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,M;
        cin>>N>>M>>limit;
        edge.assign(N+1,vector<int>());
        for(int a,b;M>0;--M)
        {
            cin>>a>>b;
            edge[b].push_back(a);
        }

        int ans=0;
        for(int i=1;i<=N;++i)
        {
            set<int> visited;
            dfs(i,visited);
            if(visited.size()>limit) ans+=1;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
