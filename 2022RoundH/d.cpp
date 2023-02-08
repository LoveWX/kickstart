#include <bits/stdc++.h>
using namespace std;

int N;

vector<int> CalcCircle(vector<int> &vp)
{
    vector<int> ans;
    for(int i=1;i<=N;++i)
    {
        if(vp[i]<0) continue;
        int cnt=0;
        for(int j=i;vp[j]>=0;)
        {
            cnt+=1;
            int t=vp[j];
            vp[j]=-1;
            j=t;
        }
        ans.push_back(cnt);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N;
        vector<int> vi(N+1);
        for(int i=1;i<=N;++i)
        {
            cin>>vi[i];
        }
        vector<int> vc=CalcCircle(vi);
        sort(vc.begin(),vc.end(),greater<int>());
        for(int i=0,lastSum=0;i<vc.size();++i)
        {
            int currSum=lastSum+vc[i];
            vi[currSum]=i;
            for(int j=currSum-1;j>lastSum;--j)
            {
                vi[j]=i+1;
            }
            lastSum=currSum;
        }
        
        vector<int> mem(N+1,INT_MAX/2);
        mem[0]=0;
        map<int,int> mc;
        for(int c:vc)
        {
            mc[c]+=1;
        }
        for(auto [size,cs]:mc)
        {
            for(int i=0;i<size;++i)
            {
                deque<array<int,2>> dq;
                for(int j=i,k=0;j<=N;j+=size,++k)
                {
                    while(!dq.empty() && dq.back()[1]>=k+mem[j])
                    {
                        dq.pop_back();
                    }
                    dq.push_back({k,k+mem[j]});
                    while(dq.front()[0]+cs<k)
                    {
                        dq.pop_front();
                    }
                    mem[j]=min(mem[j],(k-dq.front()[0])+(dq.front()[1]-dq.front()[0]));
                }
            }
        }
        cout<<"Case #"<<icase<<":";
        for(int i=1;i<=N;++i)
        {
            cout<<' '<<min(mem[i]-1,vi[i]);
        }
        cout<<endl;
    }
    return 0;
}
