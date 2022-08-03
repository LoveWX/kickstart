#include <iostream>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        long long N,K,S;
        cin>>N>>K>>S;
        long long ans=min(K-1+1+N,K-1+K-S+N-S+1);
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
