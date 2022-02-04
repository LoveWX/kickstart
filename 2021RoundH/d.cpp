#include <iostream>
#include <vector>
#include <array>
#include <cstring>
using namespace std;

const long long MOD=1000000007LL;
const int SIZE=200001;
const int LOGSIZE=18;
vector<array<long long,2>> PO;//probility of event i occupied
vector<array<long long,2>> PN;//probility of event i not occupied
vector<array<long long,2>> PA;//probility of event i occupied if its parent occupied
vector<array<long long,2>> PB;//probility of event i occupied if its parent not occupied
vector<vector<int>> edge;
vector<int> height;
int anc[SIZE][LOGSIZE];
vector<vector<array<long long,2>>> mPA;
vector<vector<array<long long,2>>> mPB;

long long powermod(long long a,long long b)
{
    long long ans=1;
    long long k=a;
    while(b!=0)
    {
        if(b%2!=0)
        {
            ans=ans*k%MOD;
        }
        b>>=1;
        k=k*k%MOD;
    }
    return ans;
}

inline long long Inv(long long a,long long p=MOD)
{
    return powermod(a,p-2);
}

array<long long,2> operator *(const array<long long,2> &a,const array<long long,2> &b)
{
    return {a[0]*b[0]%MOD,a[1]*b[1]%MOD};
}

array<long long,2> operator +(const array<long long,2> &a,const array<long long,2> &b)
{
    return {(a[0]*b[1]+a[1]*b[0])%MOD,a[1]*b[1]%MOD};
}

array<long long,2> comp(const array<long long,2> &a)
{
    return {(a[1]-a[0]+MOD)%MOD,a[1]};
}

void dfs(int parent,int curr,int h)
{
    height[curr]=h;
    PO[curr]=PA[curr]*PO[parent]+PB[curr]*PN[parent];
    PN[curr]=comp(PO[curr]);
    for(int i:edge[curr])
    {
        dfs(curr,i,h+1);
    }
}

int findLCA(int u,int v)
{
    if(height[u]<height[v]) swap(u,v);
    for(int b=LOGSIZE-1;b>=0;--b)
    {
        if(anc[u][b]>=0 && height[anc[u][b]]>=height[v])
        {
            u=anc[u][b];
        }
    }
    if(u==v) return u;
    for(int b=LOGSIZE-1;b>=0;--b)
    {
        if(anc[u][b]!=anc[v][b])
        {
            u=anc[u][b];
            v=anc[v][b];
        }
    }
    return anc[u][0];
}

void CalcProb(int a,int i,array<long long,2> &pA,array<long long,2> &pB)
{
    vector<int> vi,vb;
    for(int b=LOGSIZE-1;b>=0 && i!=a;--b)
    {
        if(anc[i][b]>=0 && height[anc[i][b]]>=height[a])
        {
            vi.push_back(i);
            vb.push_back(b);
            i=anc[i][b];
        }
    }
    pA=mPA[vi[0]][vb[0]];
    pB=mPB[vi[0]][vb[0]];
    for(int k=1;k<vi.size();++k)
    {
        array<long long,2> tA=pA*mPA[vi[k]][vb[k]]+pB*comp(mPA[vi[k]][vb[k]]);
        array<long long,2> tB=pA*mPB[vi[k]][vb[k]]+pB*comp(mPB[vi[k]][vb[k]]);
        pA=move(tA);
        pB=move(tB);
    }
}

int main()
{
    PO.assign(SIZE,array<long long,2>());
    PN.assign(SIZE,array<long long,2>());
    PA.assign(SIZE,array<long long,2>());
    PB.assign(SIZE,array<long long,2>());
    edge.reserve(SIZE);
    height.assign(SIZE,-1);
    mPA.assign(SIZE,vector<array<long long,2>>(LOGSIZE));
    mPB.assign(SIZE,vector<array<long long,2>>(LOGSIZE));
    const long long d1m=1000000LL;
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,Q;
        cin>>N>>Q>>PO[1][0];
        PN[1][0]=d1m-PO[1][0];
        PO[1][1]=PN[1][1]=d1m;
        PA[1]=PO[1];
        PB[1]={0,1};
        edge.assign(N+1,vector<int>());
        memset(anc,-1,sizeof(int)*(N+1)*LOGSIZE);
        for(int i=2;i<=N;++i)
        {
            int p;
            cin>>p>>PA[i][0]>>PB[i][0];
            edge[p].push_back(i);
            PA[i][1]=PB[i][1]=d1m;
            anc[i][0]=p;
        }
        height[1]=0;
        for(int i:edge[1])
        {
            dfs(1,i,1);
        }

        for(int i=1;i<=N;++i)
        {
            mPA[i][0]=PA[i];
            mPB[i][0]=PB[i];
        }
        for(int j=1;j<LOGSIZE;++j)
        {
            for(int i=1;i<=N;++i)
            {
                int b=anc[i][j-1];
                if(b==-1) continue;
                anc[i][j]=anc[b][j-1];
                mPA[i][j]=mPA[i][j-1]*mPA[b][j-1]+mPB[i][j-1]*comp(mPA[b][j-1]);
                mPB[i][j]=mPA[i][j-1]*mPB[b][j-1]+mPB[i][j-1]*comp(mPB[b][j-1]);
            }
        }

        cout<<"Case #"<<icase<<":";
        for(;Q>0;--Q)
        {
            int i,j;
            cin>>i>>j;
            int a=findLCA(i,j);
            array<long long,2> ans;
            if(i!=a && j==a)
            {
                array<long long,2> pa,pb;
                CalcProb(a,i,pa,pb);
                ans=pa*PO[a];
            }
            else if(i==a && j!=a)
            {
                array<long long,2> pa,pb;
                CalcProb(a,j,pa,pb);
                ans=pa*PO[a];
            }
            else
            {
                array<long long,2> pia,pib,pja,pjb;
                CalcProb(a,i,pia,pib);
                CalcProb(a,j,pja,pjb);
                ans=pia*pja*PO[a]+pib*pjb*PN[a];
            }
            cout<<' '<<ans[0]*Inv(ans[1])%MOD;
        }
        cout<<endl;
    }
    return 0;
}
