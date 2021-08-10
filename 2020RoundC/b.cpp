#include <iostream>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        long long G;
        cin>>G;
        int ans=0;
        for(long long a=1;a*a<=G;++a)
        {
            if(G%a!=0) continue;
            long long b=G/a;
            if(a%2!=0 && b-a/2>=1) ans+=1;
            if(b!=a && b%2!=0 && a-b/2>=1) ans+=1;
            if(a%2!=0 && a/2-b+1>=1) ans+=1;
            if(b!=a && b%2!=0 && b/2-a+1>=1) ans+=1;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
