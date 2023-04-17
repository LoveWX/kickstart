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
        int M,R,N;
        cin>>M>>R>>N;
        vector<int> vx(N);
        for(int &i:vx)
        {
            cin>>i;
        }
        int ans=0;
        int right=0;
        for(int i=0;i<N && vx[i]-R<=right && right<M;)
        {
            int j=i+1;
            for(;j<N && vx[j]-R<=right;++j);
            ans+=1;
            right=vx[j-1]+R;
            i=j;
        }
        if(right<M)
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
        }
        else
        {
            cout<<"Case #"<<icase<<": "<<ans<<endl;
        }
    }
    return 0;
}
