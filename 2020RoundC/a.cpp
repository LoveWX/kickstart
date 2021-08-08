#include <iostream>
#include <vector>
#include <string>
using namespace std;

const long long MOD=1000000007;
const int SIZE=50000;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,K;
        string S;
        cin>>N>>K>>S;
        long long ans=0LL,powK=1LL;
        for(int i=(N-1)/2;i>=0;--i)
        {
            ans=(ans+powK*(S[i]-'a'))%MOD;
            powK=(powK*K)%MOD;
        }
        string s=S;
        for(int i=0,j=N-1;i<j;++i,--j)
        {
            s[j]=S[i];
        }
        if(s<S)
        {
            ans=(ans+1LL)%MOD;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
