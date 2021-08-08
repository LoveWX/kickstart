#include <iostream>
#include <map>
using namespace std;

const long long INF=2e18;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,M;
        cin>>N>>M;
        map<long long,long long> m;
        for(;N>0;--N)
        {
            long long A,B;
            cin>>A>>B;
            m[B]=A;
        }
        m[INF]=INF;
        m[-INF]=-INF;
        cout<<"Case #"<<icase<<':';
        for(;M>0;--M)
        {
            long long S;
            cin>>S;
            auto it=m.lower_bound(S);
            if(S<it->second)
            {
                auto it0=prev(it);
                if(S-it0->first<=it->second-S)
                {
                    S=it0->first;
                    it=it0;
                }
                else
                {
                    S=it->second;
                }
            }
            cout<<' '<<S;
            if(it->second==S)
            {
                it->second+=1;
                if(it->second>it->first) m.erase(it);
            }
            else if(S==it->first)
            {
                if(it->second<=S-1) m[S-1]=it->second;
                m.erase(it);
            }
            else
            {
                m[S-1]=it->second;
                it->second=S+1;
            }
        }
        cout<<endl;
    }
    return 0;
}
