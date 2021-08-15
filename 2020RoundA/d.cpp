#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

const int SIZE=500;
int N;
vector<int> parent;
vector<int> rankr;

int findr(int x)
{
    int r=x,i=x,j;
    for(;r!=parent[r];r=parent[r]);
    while(r!=parent[i])
    {
        j=parent[i];
        parent[i]=r;
        i=j;
    }
    return r;
}

void unionr(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rankr[rx]<rankr[ry])
    {
        parent[rx]=ry;
    }
    else if(rankr[rx]>rankr[ry])
    {
        parent[ry]=rx;
    }
    else
    {
        parent[ry]=rx;
        rankr[rx]+=1;
    }
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N;
        int t;
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                cin>>t;
            }
        }
        vector<array<int,3>> edge;
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                cin>>t;
                if(t!=0)
                {
                    edge.push_back({t,i,j+N});
                }
            }
        }
        for(int i=N+N;i>0;--i)
        {
            cin>>t;
        }

        sort(edge.begin(),edge.end(),greater<array<int,3>>());
        parent.assign(N+N,0);
        for(int i=1;i<N+N;++i)
        {
            parent[i]=i;
        }
        rankr.assign(N+N,0);

        int ans=0;
        for(array<int,3> &e:edge)
        {
            int rx=findr(e[1]);
            int ry=findr(e[2]);
            if(rx!=ry)
            {
                unionr(rx,ry);
            }
            else
            {
                ans+=e[0];
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
