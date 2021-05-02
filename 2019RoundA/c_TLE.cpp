#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <climits>
using namespace std;

const int SIZE=30000;

int main()
{
    vector<array<int,3>> vq0,vq1;
    vq0.reserve(SIZE);
    vq1.reserve(SIZE);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,Q;
        cin>>N>>Q;
        vq0.resize(Q);
        vq1.resize(Q);
        for(int i=0;i<Q;++i)
        {
            cin>>vq0[i][0]>>vq0[i][1];
            vq0[i][1]+=1;
            vq1[i][1]=vq0[i][0];
            vq1[i][0]=vq0[i][1];
            vq0[i][2]=vq1[i][2]=1;
        }
        sort(vq0.begin(),vq0.end());
        sort(vq1.begin(),vq1.end());
        vector<bool> used(Q,false);
        int ans=INT_MAX,count;
        int i0=0,i1=0;
        for(int select=0;select<Q;++select)
        {
            vector<array<int,2>> vcurr;
            vector<int> vcount(Q,0);
            for(i0=0;i0<Q && vq0[i0][2]==0;++i0);
            for(i1=0;i1<Q && vq1[i1][2]==0;++i1);
            int lasti=0,count=0;
            while(i0<Q || i1<Q)
            {
                int curri;
                if(i0==Q) curri=vq1[i1][0];
                else if(i1==Q) curri=vq0[i0][0];
                else curri=min(vq0[i0][0],vq1[i1][0]);
                if(count==1)
                {
                    int k=0;
                    for(;k<vcurr.size() && vcurr[k][0]<curri;++k);
                    vcurr[0]=vcurr[k];
                    vcurr.resize(1);
                    vcount[vcurr[0][1]]+=curri-lasti;
                }
                for(;i0<Q && vq0[i0][0]==curri;++i0)
                {
                    if(vq0[i0][2]!=0)
                    {
                        vcurr.push_back({vq0[i0][1],i0});
                        count+=1;
                    }
                }
                for(;i1<Q && vq1[i1][0]==curri;++i1)
                {
                    if(vq1[i1][2]!=0)
                    {
                        count-=1;
                    }
                }
                for(;i0<Q && vq0[i0][2]==0;++i0);
                for(;i1<Q && vq1[i1][2]==0;++i1);
                lasti=curri;
            }
            int i=max_element(vcount.begin(),vcount.end())-vcount.begin();
            ans=min(ans,vcount[i]);
            vq0[i][2]=0;
            (*lower_bound(vq1.begin(),vq1.end(),array<int,3>({vq0[i][1],vq0[i][0],1})))[2]=0;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
