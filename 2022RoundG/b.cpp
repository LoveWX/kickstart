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
        int Rs,Rh,N,M;
        cin>>Rs>>Rh>>N;
        int limit=(Rs+Rh)*(Rs+Rh);
        vector<pair<int,int>> vp;
        for(int i=0;i<N;++i)
        {
            int x,y;
            cin>>x>>y;
            x=x*x+y*y;
            if(x<=limit) vp.push_back({x,0});
        }
        cin>>M;
        for(int i=0;i<M;++i)
        {
            int x,y;
            cin>>x>>y;
            x=x*x+y*y;
            if(x<=limit) vp.push_back({x,1});
        }
        sort(vp.begin(),vp.end());
        int cnt[2]={0,0};
        for(auto [dis,team]:vp)
        {
            if(cnt[1-team]!=0) break;
            cnt[team]+=1;
        }
        cout<<"Case #"<<icase<<": "<<cnt[0]<<' '<<cnt[1]<<endl;
    }
    return 0;
}
