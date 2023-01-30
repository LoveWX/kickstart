#include <bits/stdc++.h>
using namespace std;

struct TimeSlot
{
    int n0,n1;
    int sum0;
    multiset<int> s0,s1;
    TimeSlot(int K,int N,const vector<int> &vi)
    {
        n0=K;
        n1=N-K;
        s0.insert(-1);
        s1.insert(INT_MAX/2);
        vector<int> vt=vi;
        sort(vt.begin(),vt.end());
        s0.insert(vt.begin(),vt.begin()+K);
        sum0=accumulate(vt.begin(),vt.begin()+K,0);
        s1.insert(vt.begin()+K,vt.end());
    }
    int GetSumK()
    {
        return sum0;
    }
    void Change(int a,int b)
    {
        if(auto it=s0.find(a);it!=s0.end())
        {
            s0.erase(it);
            s0.insert(b);
            sum0=sum0-a+b;
        }
        else
        {
            s1.erase(s1.find(a));
            s1.insert(b);
        }
        auto it0=prev(s0.end());
        auto it1=s1.begin();
        a=*it0;
        b=*it1;
        if(a>b)
        {
            sum0=sum0-a+b;
            s0.erase(it0);
            s0.insert(b);
            s1.erase(it1);
            s1.insert(a);
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,K,X,D,M;
        cin>>N>>K>>X>>D>>M;
        vector<vector<int>> mle(D+1),mri(D+1);
        for(;M!=0;--M)
        {
            int P,L,R;
            cin>>P>>L>>R;
            mle[L].push_back(P-1);
            mri[R].push_back(P-1);
        }
        vector<int> vp(N,0);
        for(int i=0;i<X;++i)
        {
            for(int d:mle[i])
            {
                vp[d]+=1;
            }
        }
        TimeSlot s(K,N,vp);
        int ans=s.GetSumK();
        for(int i=1,j=X;j<D;++i,++j)
        {
            for(int d:mle[j])//右端位置为j+1,这样才能包含左端在j的会议
            {
                s.Change(vp[d],vp[d]+1);
                vp[d]+=1;
            }
            for(int d:mri[i])//左端位置为j+1-X
            {
                s.Change(vp[d],vp[d]-1);
                vp[d]-=1;
            }
            ans=min(ans,s.GetSumK());
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
