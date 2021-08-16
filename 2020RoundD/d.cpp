#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int SIZE=100000;
const int LOGSIZE=17;
int D[SIZE];
int lchild[SIZE],rchild[SIZE];
int parent[SIZE],countd[SIZE];
int mem[SIZE][LOGSIZE];

int dfs(int pare,int curr)
{
    parent[curr]=pare;
    countd[curr]=1;
    if(lchild[curr]!=-1) countd[curr]+=dfs(curr,lchild[curr]);
    if(rchild[curr]!=-1) countd[curr]+=dfs(curr,rchild[curr]);
    return countd[curr];
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,Q;
        cin>>N>>Q;
        N-=1;
        for(int i=0;i<N;++i)
        {
            cin>>D[i];
        }
        memset(lchild,-1,sizeof(int)*N);
        memset(rchild,-1,sizeof(int)*N);
        vector<int> rstk(1,0);
        for(int i=1;i<N;++i)
        {
            if(D[rstk[0]]<D[i])
            {
                lchild[i]=rstk[0];
                rstk={i};
                continue;
            }
            while(D[rstk.back()]<D[i])
            {
                rstk.pop_back();
            }
            lchild[i]=rchild[rstk.back()];
            rchild[rstk.back()]=i;
            rstk.push_back(i);
        }
        dfs(-1,rstk[0]);
        memset(mem,-1,sizeof(int)*N*LOGSIZE);
        for(int i=0;i<N;++i)
        {
            mem[i][0]=parent[i];
        }
        for(int j=1;j<LOGSIZE;++j)
        {
            for(int i=0;i<N;++i)
            {
                if(mem[i][j-1]!=-1)
                {
                    mem[i][j]=mem[mem[i][j-1]][j-1];
                }
            }
        }

        int S,K;
        cout<<"Case #"<<icase<<':';
        for(;Q>0;--Q)
        {
            cin>>S>>K;
            K-=1;
            int X;
            if(S==1)               X=0;
            else if(S==N+1)        X=N-1;
            else if(D[S-2]<D[S-1]) X=S-2;
            else                   X=S-1;
            if(countd[X]>=K)
            {
                if(X+1<S) cout<<' '<<S-K;
                else      cout<<' '<<S+K;
                continue;
            }
            int Y=X;
            for(int b=LOGSIZE-1;b>=0;--b)
            {
                if(mem[Y][b]!=-1 && countd[mem[Y][b]]<K)
                {
                    Y=mem[Y][b];
                }
            }
            Y=parent[Y];
            if(X<Y) cout<<' '<<Y+1+(K-countd[lchild[Y]]);
            else    cout<<' '<<Y+2-(K-countd[rchild[Y]]);
        }
        cout<<endl;
    }
    return 0;
}
