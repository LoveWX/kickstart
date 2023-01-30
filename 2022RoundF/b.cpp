#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,Q;
        cin>>N>>Q;
        vector<vector<int>> edge(N+1,vector<int>());
        for(int i=1;i<N;++i)
        {
            int a,b;
            cin>>a>>b;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        for(int i=0;i<Q;++i)
        {
            int a;
            cin>>a;
        }
        
        vector<bool> visited(N+1,false);
        vector<int> vcnt;
        queue<pair<int,int>> q;
        q.push({1,0});
        while(!q.empty())
        {
            auto [curr,level]=q.front();
            q.pop();
            if(visited[curr]) continue;
            visited[curr]=true;
            if(vcnt.size()==level) vcnt.push_back(0);
            vcnt[level]+=1;
            for(int i:edge[curr])
            {
                if(!visited[i])
                {
                    q.push({i,level+1});
                }
            }
        }
        
        int full=0;
        for(int i=0;i<vcnt.size();++i)
        {
            if(vcnt[i]>Q)
            {
                break;
            }
            full+=vcnt[i];
            Q-=vcnt[i];
        }
        cout<<"Case #"<<icase<<": "<<full<<endl;
    }
    return 0;
}
