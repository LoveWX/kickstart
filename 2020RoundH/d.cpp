#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
using namespace std;

const int SIZE=50000;
int A[SIZE+1];
int N,Q;
vector<int> edge;

void ShortestDist(int src,vector<int> &vd)
{
    queue<pair<int,int>> q;
    vd[src]=0;
    q.push({src,0});
    while(!q.empty())
    {
        auto [curr,step]=q.front();
        q.pop();
        step+=1;
        for(int i=0;i<26;++i)
        {
            if((edge[curr]&(1<<i))!=0 && vd[i]==-1)
            {
                vd[i]=step;
                q.push({i,step});
            }
        }
    }
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>Q;
        edge.assign(26,0);
        for(int i=1;i<=N;++i)
        {
            string s;
            cin>>s;
            int a=0;
            for(char c:s)
            {
                a|=1<<(c-'A');
            }
            A[i]=a;
            for(char c:s)
            {
                edge[c-'A']|=a;
            }
        }
        
        vector<vector<int>> dist(26,vector<int>(26,-1));
        for(int i=0;i<26;++i)
        {
            ShortestDist(i,dist[i]);
        }
        cout<<"Case #"<<icase<<':';
        for(;Q>0;--Q)
        {
            int a,b;
            cin>>a>>b;
            int ans=INT_MAX;
            for(int i=0;i<26;++i)
            {
                if((A[a]&(1<<i))==0) continue;
                for(int j=0;j<26;++j)
                {
                    if((A[b]&(1<<j))==0) continue;
                    ans=min(ans,dist[i][j]);
                }
            }
            if(ans!=-1) ans+=2;
            cout<<' '<<ans;
        }
        cout<<endl;
    }
    return 0;
}
