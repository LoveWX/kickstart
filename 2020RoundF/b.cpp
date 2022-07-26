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
        int N,K;
        cin>>N>>K;
        vector<array<int,2>> vp(N);
        for(array<int,2> &a:vp)
        {
            cin>>a[0]>>a[1];
        }
        sort(vp.begin(),vp.end());
        int ans=0,right=0;
        for(array<int,2> &a:vp)
        {
            if(right>=a[1])
            {
                continue;
            }
            if(right<=a[0])
            {
                right=a[0];
            }
            else
            {
                a[0]=right;
            }
            int len=a[1]-a[0];
            int cnt=len/K+(len%K==0 ? 0 : 1);
            ans+=cnt;
            right+=cnt*K;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}

