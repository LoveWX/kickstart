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
        int M,N,P;
        cin>>M>>N>>P;
        vector<vector<int>> mstep(N,vector<int>(M+1,0));
        for(int i=1;i<=M;++i)
        {
            for(int j=0;j<N;++j)
            {
                cin>>mstep[j][i];
            }
        }
        int ans=0;
        for(vector<int> &vstep:mstep)
        {
            ans+=*max_element(vstep.begin(),vstep.end())-vstep[P];
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
