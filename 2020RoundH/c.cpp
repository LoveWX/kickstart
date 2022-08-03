#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        vector<int> X(N),Y(N);
        for(int i=0;i<N;++i)
        {
            cin>>X[i]>>Y[i];
        }
        long long ans=0;
        sort(Y.begin(),Y.end());
        int mid=Y[N/2];
        for(int i:Y)
        {
            ans+=abs(i-mid);
        }
        sort(X.begin(),X.end());
        for(int i=0;i<N;++i)
        {
            X[i]-=i;
        }
        sort(X.begin(),X.end());
        mid=X[N/2];
        for(int i:X)
        {
            ans+=abs(i-mid);
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
