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
        int N;
        long long D,X;
        map<long long,vector<array<int,2>>> mseed;
        for(cin>>D>>N>>X;N!=0;--N)
        {
            int Q,V;
            long long L;
            cin>>Q>>L>>V;
            if(L>D) continue;
            mseed[L].push_back({V,Q});
        }
        N=mseed.size();
        vector<long long> vd;
        vd.reserve(N+1);
        vector<vector<array<int,2>>> md;
        md.reserve(N);
        for(auto &[d,va]:mseed)
        {
            vd.push_back(d);
            md.push_back(move(va));
        }
        vd.push_back(D);

        priority_queue<array<int,2>> pq;
        long long ans=0;
        for(int i=0;i<N;++i)
        {
            for(array<int,2> seed:md[i])
            {
                pq.push(seed);
            }
            for(long long x=(vd[i+1]-vd[i])*X;x>0 && !pq.empty();)
            {
                int val=pq.top()[0];
                long long cnt=pq.top()[1];
                pq.pop();
                long long t=min(x,cnt);
                ans+=val*t;
                x-=t;
                cnt-=t;
                if(cnt>0) pq.push({val,cnt});
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
