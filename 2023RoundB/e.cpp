#include <bits/stdc++.h>
using namespace std;

const int SIZE=100000;
vector<int> D(SIZE+1);
vector<int> indeg(SIZE+1);
vector<long long> inCnt(SIZE+1);
vector<long long> outCnt(SIZE+1);

void dfs(int curr,long long &ans)
{
    indeg[curr]=-1;
    if(inCnt[curr]<outCnt[curr])
    {
        ans+=outCnt[curr]-inCnt[curr];
    }
    inCnt[D[curr]]+=outCnt[curr];
    if((--indeg[D[curr]])==0)
    {
        dfs(D[curr],ans);
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
        int N;
        cin>>N;
        indeg.assign(N+1,0);
        for(int i=1;i<=N;++i)
        {
            cin>>D[i];
            indeg[D[i]]+=1;
        }
        for(int i=1;i<=N;++i)
        {
            cin>>outCnt[i];
        }

        long long ans=0;
        inCnt.assign(N+1,0);
        for(int i=1;i<=N;++i)
        {
            if(indeg[i]==0)
            {
                dfs(i,ans);
            }
        }

        vector<vector<int>> vcircle;
        for(int i=1;i<=N;++i)
        {
            if(indeg[i]<0) continue;
            vector<int> c(1,i);
            indeg[i]=-1;
            for(int j=D[i];j!=i;j=D[j])
            {
                c.push_back(j);
                indeg[j]=-1;
            }
            vcircle.push_back(move(c));
        }
        for(vector<int> &c:vcircle)
        {
            int n=c.size();
            c.push_back(c[0]);
            long long sum=0;
            for(int i=1;i<=n;++i)
            {
                sum+=max(outCnt[c[i]]-(outCnt[c[i-1]]+inCnt[c[i]]),0LL);
            }
            long long tans=LLONG_MAX;
            for(int i=1;i<=n;++i)
            {
                tans=min(tans,sum-max(outCnt[c[i]]-(outCnt[c[i-1]]+inCnt[c[i]]),0LL)+max(outCnt[c[i]]-inCnt[c[i]],0LL));
            }
            ans+=tans;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
