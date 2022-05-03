#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        string I,P;
        cin>>I>>P;
        int i=0,p,ans=0;
        for(p=0;i<I.size() && p<P.size();++p)
        {
            if(I[i]==P[p])
            {
                i+=1;
            }
            else
            {
                ans+=1;
            }
        }
        if(i<I.size())
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
        }
        else
        {
            ans+=P.size()-p;
            cout<<"Case #"<<icase<<": "<<ans<<endl;
        }
    }
    return 0;
}
