#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <climits>
using namespace std;

const int SIZE=30000;
int N,Q;
vector<array<int,2>> vp;
vector<int> vx;

bool Check(int need)
{
    for(int i=0;i<Q;++i)
    {
        vx[i]=vp[i][0];
    }
    for(int k=0;k<Q;++k)
    {
        int st=vx[k];
        int right=vp[k][1];
        int ed=vp[k][1];
        int count=0;
        for(int i=k+1;i<Q;++i)
        {
            if(right<=vp[i][0]) break;
            if(vp[i][1]<=right)
            {
                if(vp[i][0]<=st)
                {
                    st=max(st,vp[i][1]);
                }
                else
                {
                    count+=vp[i][0]-st;
                    st=max(st,vp[i][1]);
                    if(count>=need)
                    {
                        ed=vp[i][0]-(count-need);
                        break;
                    }
                }
            }
        }
        if(count<need)
        {
            count+=right-st;
            if(count<need) return false;
            ed=right-(count-need);
        }
        for(int i=k+1;i<Q;++i)
        {
            if(ed<=vp[i][0]) break;
            if(vp[i][1]>right) vx[i]=max(vx[i],right);
        }
    }
    return true;
}

int main()
{
    vp.reserve(SIZE);
    vx.assign(SIZE,0);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>Q;
        vp.resize(Q);
        int minLen=INT_MAX;
        for(int i=0;i<Q;++i)
        {
            cin>>vp[i][0]>>vp[i][1];
            vp[i][1]+=1;
            minLen=min(minLen,vp[i][1]-vp[i][0]);
        }
        sort(vp.begin(),vp.end(),[](array<int,2> &a,array<int,2> &b){
            return a[0]!=b[0] ? a[0]<b[0] : a[1]>b[1];
        });
        
        int left=0,right=minLen+1,mid;
        while(left<right)
        {
            mid=(right-left)/2+left;
            if(Check(mid))
            {
                left=mid+1;
            }
            else
            {
                right=mid;
            }
        }
        cout<<"Case #"<<icase<<": "<<left-1<<endl;
    }
    return 0;
}
