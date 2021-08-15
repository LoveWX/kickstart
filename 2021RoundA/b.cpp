#include <iostream>
#include <map>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        long long C;
        cin>>N>>C;
        long long ans=N;
        map<long long,long long> mm;
        for(;N>0;--N)
        {
            long long l,r;
            cin>>l>>r;
            mm[l+1]+=1;
            mm[r]-=1;
        }
        map<long long,long long> mc;
        long long last=0LL,count=0LL;
        for(auto it=mm.begin();it!=mm.end();++it)
        {
            mc[count]+=it->first-last;
            count+=it->second;
            last=it->first;
        }
        for(auto it=mc.rbegin();C>0 && it!=mc.rend();++it)
        {
            long long t=min(C,it->second);
            ans+=t*it->first;
            C-=t;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
