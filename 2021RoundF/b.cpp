#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <climits>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int D,N,K;
        cin>>D>>N>>K;
        map<int,pair<vector<int>,vector<int>>> m;
        for(int i=0;i<N;++i)
        {
            int h,s,e;
            cin>>h>>s>>e;
            m[s].first.push_back(h);
            m[e+1].second.push_back(h);
        }
        multiset<int> s0,s1;
        s0.insert(INT_MIN);
        long long ans=0LL,h1=0LL;
        for(const auto &p:m)
        {
            for(int i:p.second.second)
            {
                auto it=s0.find(i);
                if(it!=s0.end())
                {
                    s0.erase(it);
                }
                else
                {
                    h1-=i;
                    s1.erase(s1.find(i));
                }
            }
            int tval=*s0.rbegin();
            for(int i:p.second.first)
            {
                if(i<=tval)
                {
                    s0.insert(i);
                }
                else
                {
                    h1+=i;
                    s1.insert(i);
                }
            }
            while(s1.size()>K)
            {
                auto it=s1.begin();
                h1-=*it;
                s0.insert(*it);
                s1.erase(it);
            }
            while(s1.size()<K && s0.size()>1)
            {
                auto it=prev(s0.end());
                h1+=*it;
                s1.insert(*it);
                s0.erase(it);
            }
            ans=max(ans,h1);
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
