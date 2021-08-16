#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

struct Node
{
    int prev;
    vector<int> next;
    Node():prev(0) {}
};

void dfs(vector<Node> &t0,vector<Node> &t1,vector<vector<int>> &mprev,int curr,int idx,int mod)
{
    if(!mprev[idx].empty())
    {
        int prev=mprev[idx].back();
        t1[prev].next.push_back(curr);
        t1[curr].prev=prev;
    }
    mprev[idx].push_back(curr);
    for(int i:t0[curr].next)
    {
        dfs(t0,t1,mprev,i,(idx+1)%mod,mod);
    }
    mprev[idx].pop_back();
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,A,B;
        cin>>N>>A>>B;
        vector<Node> tree(N+1);
        for(int i=2;i<=N;++i)
        {
            int p;
            cin>>p;
            tree[p].next.push_back(i);
        }

        //build A-tree and B-tree
        vector<Node> tA(N+1),tB(N+1);
        vector<vector<int>> tma(A);
        dfs(tree,tA,tma,1,0,A);
        vector<vector<int>> tmb(B);
        dfs(tree,tB,tmb,1,0,B);

        //count each node in N situation
        vector<long long> countA(N+1,1LL),countB(N+1,1LL);
        for(int k=N;k>0;--k)
        {
            for(int i:tA[k].next)
            {
                countA[k]+=countA[i];
            }
        }
        for(int k=N;k>0;--k)
        {
            for(int i:tB[k].next)
            {
                countB[k]+=countB[i];
            }
        }

        //calc intersections
        vector<long long> countAB(N+1,0LL);
        for(int k=1;k<=N;++k)
        {
            countAB[k]=countAB[tA[k].prev]+countB[k];
        }

        long long sumA=accumulate(countA.begin()+1,countA.end(),0LL)*(long long)N;
        long long sumB=accumulate(countB.begin()+1,countB.end(),0LL)*(long long)N;
        long long sumAB=accumulate(countAB.begin()+1,countAB.end(),0LL);
        long double ans=(long double)(sumA+sumB-sumAB)/((long long)N*N);
        cout<<"Case #"<<icase<<": "<<setiosflags(ios::fixed)<<setprecision(8)<<ans<<endl;
    }
    return 0;
}
