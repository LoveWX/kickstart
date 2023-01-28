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
        int N;
        cin>>N;
        vector<int> A(N+1,0);
        for(int i=1;i<=N;++i)
        {
            cin>>A[i];
        }
        vector<long long> S(N+1,0);
        for(int i=1;i<=N;++i)
        {
            S[i]=S[i-1]+A[i];
        }
        vector<int> vright(N+1,N+1);
        priority_queue<pair<long long,int>> pq;
        pq.push({0,0});
        for(int i=1;i<=N;++i)
        {
            while(!pq.empty() && pq.top().first>S[i])
            {
                vright[pq.top().second+1]=i;
                pq.pop();
            }
            pq.push({S[i],i});
        }
        vector<long long> sumS(N+1,0);
        for(int i=1;i<=N;++i)
        {
            sumS[i]=sumS[i-1]+S[i];
        }
        long long ans=0;
        for(int i=1;i<=N;++i)
        {
            ans+=(sumS[vright[i]-1]-sumS[i-1])-(vright[i]-i)*S[i-1];
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
