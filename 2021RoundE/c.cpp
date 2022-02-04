#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;

const int SIZE=1000;
vector<string> m;
vector<vector<vector<array<int,2>>>> madj;
int N,M;
int count;

void dfs(int x,int y,char c)
{
    if(m[x][y]!='.') return;
    m[x][y]=c;
    count+=1;
    for(array<int,2> &a:madj[x][y])
    {
        dfs(a[0],a[1],c);
    }
}

int main()
{
    m.assign(SIZE,string());
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>M;
        for(int i=0;i<N;++i)
        {
            cin>>m[i];
        }
        madj.assign(N,vector<vector<array<int,2>>>(M));
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<M;)
            {
                if(m[i][j]=='#')
                {
                    j+=1;
                    continue;
                }
                int k=j+1;
                for(;k<M && m[i][k]!='#';++k);
                for(int l=j,r=k-1;l<r;++l,--r)
                {
                    madj[i][l].push_back({i,r});
                    madj[i][r].push_back({i,l});
                }
                j=k;
            }
        }
        for(int j=0;j<M;++j)
        {
            for(int i=0;i<N;)
            {
                if(m[i][j]=='#')
                {
                    i+=1;
                    continue;
                }
                int k=i+1;
                for(;k<N && m[k][j]!='#';++k);
                for(int u=i,d=k-1;u<d;++u,--d)
                {
                    madj[u][j].push_back({d,j});
                    madj[d][j].push_back({u,j});
                }
                i=k;
            }
        }
        count=0;
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<M;++j)
            {
                if(isupper(m[i][j]))
                {
                    for(array<int,2> &a:madj[i][j])
                    {
                        dfs(a[0],a[1],m[i][j]);
                    }
                }
            }
        }
        cout<<"Case #"<<icase<<": "<<count<<endl;
        for(int i=0;i<N;++i)
        {
            cout<<m[i]<<endl;
        }
    }
    return 0;
}
