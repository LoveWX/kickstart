#include <iostream>
#include <cstring>
using namespace std;

const int SIZE=15;
const int MAXSIZE=1<<SIZE;
int edge[SIZE];
unsigned int L[SIZE],R[SIZE],A[SIZE];
unsigned int sum[MAXSIZE];
long long mem[MAXSIZE];
int N,M;
unsigned int K;

long long dp(int curr)
{
    if(mem[curr]!=-1) return mem[curr];
    long long ans=0LL;
    for(int i=0;i<N;++i)
    {
        if((curr&(1<<i))==0) continue;
        int prev=curr^(1<<i);
        if((prev&edge[i])!=0 && L[i]<=sum[prev] && sum[prev]<=R[i])
        {
            ans+=dp(prev);
        }
    }
    return mem[curr]=ans;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>M>>K;
        int maxn=1<<N;
        for(int i=0;i<N;++i)
        {
            cin>>L[i]>>R[i]>>A[i];
        }
        memset(mem,-1,sizeof(long long)*maxn);
        for(int i=0;i<N;++i)
        {
            mem[1<<i]=1;
        }
        for(int i=1;i<maxn;++i)
        {
            unsigned long long psum=0ULL;
            for(int j=0;j<N;++j)
            {
                if((i&(1<<j))==0) continue;
                psum+=A[j];
            }
            if(psum<=K)
            {
                sum[i]=psum;
            }
            else
            {
                sum[i]=K+1;
                mem[i]=0;
            }
        }
        memset(edge,0,sizeof(edge));
        for(int i=0;i<M;++i)
        {
            int x,y;
            cin>>x>>y;
            edge[x]|=(1<<y);
            edge[y]|=(1<<x);
        }

        long long ans=0LL;
        for(int i=1;i<maxn;++i)
        {
            if(sum[i]==K)
            {
                ans+=dp(i);
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
