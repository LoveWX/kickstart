#include <bits/stdc++.h>
using namespace std;

const long long NINF=LLONG_MIN/2;
const long long NLIMIT=LLONG_MIN/16;
int N,P,M;

vector<vector<int>> cmat;
vector<vector<int>> mmat;

struct MoveType
{
    MoveType(vector<pair<char,int>> &vop)
    {
        op.reserve(4);
        for(auto [currop,num]:vop)
        {
            if(currop=='+')
            {
                op.push_back([=](long long c){
                    if(c<=NLIMIT) return NINF;
                    return c+num;
                });
            }
            else if(currop=='-')
            {
                op.push_back([=](long long c){
                    if(c<=NLIMIT) return NINF;
                    return c-num;
                });
            }
            else if(currop=='*')
            {
                op.push_back([=](long long c){
                    if(c<=NLIMIT) return NINF;
                    return c*num;
                });
            }
            else//if(currop=='/')
            {
                op.push_back([=](long long c){
                    if(c<=NLIMIT) return NINF;
                    if(c>=0) return c/num;
                    if(c%num==0) return c/num;
                    return c/num-1;
                });
            }
        }
    }
    long long MoveStep(int dir,long long curr)
    {
        return op[dir](curr);
    }
    vector<function<long long(long long)>> op;//[North, East, West, South]
};

inline bool InBoard(int x,int y)
{
    return 0<=x && x<N && 0<=y && y<N;
}

inline void Update(long long &a,long long b)
{
    a=max(a,b);
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int sx,sy;
        cin>>N>>P>>M>>sx>>sy;
        vector<pair<char,int>> vop(4);
        for(int i=0;i<4;++i)
        {
            cin>>vop[i].first>>vop[i].second;
        }
        MoveType Move(vop);
        cmat.assign(N,vector<int>(N,0));
        mmat.assign(N,vector<int>(N,0));
        for(int i=0;i<P;++i)
        {
            int a,b,c;
            cin>>a>>b>>c;
            cmat[a-1][b-1]=c;
            mmat[a-1][b-1]=(1<<i);
        }
        
        vector<vector<vector<long long>>> last(N,vector<vector<long long>>(N,vector<long long>(1<<P,NINF)));
        last[sx-1][sy-1][(1<<P)-1]=0;
        for(;M!=0;--M)
        {
            vector<vector<vector<long long>>> curr=last;
            for(int i=0;i<N;++i)
            {
                for(int j=0;j<N;++j)
                {
                    {
                        for(int a=(1<<P)-1;a>=0;--a)
                        {
                            if(InBoard(i-1,j)) Update(curr[i][j][a],Move.MoveStep(3,last[i-1][j][a]));
                            if(InBoard(i+1,j)) Update(curr[i][j][a],Move.MoveStep(0,last[i+1][j][a]));
                            if(InBoard(i,j-1)) Update(curr[i][j][a],Move.MoveStep(1,last[i][j-1][a]));
                            if(InBoard(i,j+1)) Update(curr[i][j][a],Move.MoveStep(2,last[i][j+1][a]));
                        }
                    }
                    if(cmat[i][j]!=0)
                    {
                        for(int a=(1<<P)-1;a>=0;--a)
                        {
                            if((a&mmat[i][j])==0) continue;
                            int b=a^mmat[i][j];
                            if(InBoard(i-1,j)) Update(curr[i][j][b],Move.MoveStep(3,last[i-1][j][a])+cmat[i][j]);
                            if(InBoard(i+1,j)) Update(curr[i][j][b],Move.MoveStep(0,last[i+1][j][a])+cmat[i][j]);
                            if(InBoard(i,j-1)) Update(curr[i][j][b],Move.MoveStep(1,last[i][j-1][a])+cmat[i][j]);
                            if(InBoard(i,j+1)) Update(curr[i][j][b],Move.MoveStep(2,last[i][j+1][a])+cmat[i][j]);
                        }
                    }
                }
            }
            last=move(curr);
        }
        long long ans=NINF;
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                ans=max(ans,last[i][j][0]);
            }
        }
        if(ans<=NLIMIT)
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
        }
        else
        {
            cout<<"Case #"<<icase<<": "<<ans<<endl;
        }
    }
    return 0;
}
