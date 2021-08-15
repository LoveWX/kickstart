#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE=300000;
int A[SIZE],D[SIZE];
int N;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N;
        for(int i=0;i<N;++i)
        {
            cin>>A[i];
        }
        for(int i=1;i<N;++i)
        {
            D[i]=A[i]-A[i-1];
        }
        vector<pair<int,int>> vp;
        for(int i=1;i<N;)
        {
            int j;
            for(j=i+1;j<N && D[i]==D[j];++j);
            vp.push_back({i,j-1});
            i=j;
        }
        int ans=2;
        for(int i=0;i<vp.size();++i)
        {
            auto [l,r]=vp[i];
            int len=r-l+1;
            if(r+1<N)
            {
                len+=1;
                if(r+2<N)
                {
                    if(int d2=A[r+2]-(A[r]+D[r]);D[r]==d2)
                    {
                        len+=1;
                        if(r+3<N && D[r]==D[r+3])
                        {
                            auto it=lower_bound(vp.begin(),vp.end(),pair<int,int>(r+3,0));
                            len+=it->second-it->first+1;
                        }
                    }
                }
            }
            ans=max(ans,len+1);
        }
        for(int i=vp.size()-1;i>=0;--i)
        {
            auto [l,r]=vp[i];
            int len=r-l+1;
            if(l-1>0)
            {
                len+=1;
                if(l-2>0)
                {
                    if(int d2=A[l-1]-D[l]-A[l-3];D[l]==d2)
                    {
                        len+=1;
                        if(l-3>0 && D[l]==D[l-3])
                        {
                            auto it=lower_bound(vp.begin(),vp.end(),pair<int,int>(l-3,0));
                            len+=it->second-it->first+1;
                        }
                    }
                }
            }
            ans=max(ans,len+1);
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;;
    }
    return 0;
}
