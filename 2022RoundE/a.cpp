#include <bits/stdc++.h>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        int ans=N/5;
        if(N%5>=1) ans+=1;
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
