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
        int n;
        cin>>n;
        vector<pair<string,int>> va(n);//<C,U>
        vector<pair<int,int>> vb(n);//<D,U>
        for(int i=0;i<n;++i)
        {
            cin>>va[i].first>>vb[i].first>>va[i].second;
            vb[i].second=va[i].second;
        }
        sort(va.begin(),va.end());
        sort(vb.begin(),vb.end());
        int ans=0;
        for(int i=0;i<n;++i)
        {
            if(va[i].second==vb[i].second)
            {
                ans+=1;
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
