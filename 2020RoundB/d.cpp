#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <climits>
using namespace std;

struct Node
{
    int L;
    long long A;
    vector<int> vchild;
    vector<array<int,2>> vquery;
    bool queried;
};

const int SIZE=50000;
Node city[SIZE+1];
vector<vector<tuple<int,int,long long>>> edge;
long long ans[SIZE+SIZE];
int N,Q;
int n;
vector<long long> bit;

void Build(int parent,int curr,int L,long long A,map<int,int> &mLimit)
{
    city[curr].L=mLimit[L];
    city[curr].A=A;
    for(auto [next,Li,Ai]:edge[curr])
    {
        if(parent==next) continue;
        city[curr].vchild.push_back(next);
        Build(curr,next,Li,Ai,mLimit);
    }
}

bool ContainQuery(Node &curr)
{
    curr.queried=!curr.vquery.empty();
    for(int i:curr.vchild)
    {
        if(ContainQuery(city[i]))
        {
            curr.queried=true;
        }
    }
    return curr.queried;
}

long long gcd(long long a,long long b)
{
    while(b!=0LL)
    {
        long long c=a%b;
        a=b;
        b=c;
    }
    return a;
}

long long prefixGCD(int idx)
{
    long long ans=0LL;
    while(idx!=0)
    {
        ans=gcd(bit[idx],ans);
        idx-=(idx & -idx);
    }
    return ans;
}

void update(vector<pair<int,long long>> &vp,int idx,long long val)
{
    while(idx<=n)
    {
        vp.push_back({idx,bit[idx]});
        bit[idx]=gcd(val,bit[idx]);
        idx+=(idx & -idx);
    }
}

void Calc(Node &curr)
{
    if(!curr.queried) return;
    vector<pair<int,long long>> vp;
    update(vp,curr.L,curr.A);
    for(array<int,2> &q:curr.vquery)
    {
        ans[q[0]]=prefixGCD(q[1]);
    }
    for(int i:curr.vchild)
    {
        Calc(city[i]);
    }
    for(pair<int,long long> &p:vp)
    {
        bit[p.first]=p.second;
    }
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>Q;
        edge.assign(N+1,vector<tuple<int,int,long long>>());
        map<int,int> mLimit;
        for(int i=1;i<N;++i)
        {
            int X,Y,L;
            long long A;
            cin>>X>>Y>>L>>A;
            edge[X].push_back({Y,L,A});
            edge[Y].push_back({X,L,A});
            mLimit[L];
        }

        mLimit[INT_MAX];
        n=1;
        for(auto it=mLimit.begin();it!=mLimit.end();++it)
        {
            it->second=n++;
        }
        Build(-1,1,INT_MAX,0LL,mLimit);

        for(int i=0;i<Q;++i)
        {
            int c,w;
            cin>>c>>w;
            city[c].vquery.push_back({i,mLimit.upper_bound(w)->second-1});
        }
        ContainQuery(city[1]);

        bit.assign(n,0LL);
        for(int i:city[1].vchild)
        {
            Calc(city[i]);
        }

        cout<<"Case #"<<icase<<':';
        for(int i=0;i<Q;++i)
        {
            cout<<' '<<ans[i];
        }
        cout<<endl;
        for(int i=1;i<=N;++i)
        {
            city[i].vchild.clear();
            city[i].vquery.clear();
        }
    }
    return 0;
}
