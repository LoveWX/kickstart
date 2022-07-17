#include <bits/stdc++.h>
using namespace std;

long long Calc(vector<int> &vi,int cnt)
{
    if(cnt==0) return 0;
    long long ans=LLONG_MAX;
    long long sum=accumulate(vi.begin(),vi.begin()+cnt-1,0LL);
    for(int i=cnt-1;i<vi.size();++i)
    {
        sum+=vi[i];
        ans=min(ans,sum);
        sum-=vi[i-cnt+1];
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,M,K;
        cin>>N;
        vector<int> A(N);
        for(int &i:A)
        {
            cin>>i;
        }
        cin>>M;
        vector<int> B(M);
        for(int &i:B)
        {
            cin>>i;
        }
        cin>>K;
        K=N+M-K;
        long long sum=accumulate(A.begin(),A.end(),0LL)+accumulate(B.begin(),B.end(),0LL);
        long long ans=0;
        for(int i=0;i<=N && i<=K;++i)
        {
            ans=max(ans,sum-(Calc(A,i)+Calc(B,K-i)));
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
