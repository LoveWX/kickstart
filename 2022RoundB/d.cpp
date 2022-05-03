#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char c;
    int block[2][2];
    Node()
    {
        block[0][0]=0;
        block[0][1]=1;
        block[1][1]=2;
        block[1][0]=3;
    }
};

int R,C;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
vector<vector<Node>> m;

bool InBoard(int x,int y)
{
    return 0<=x && x<R && 0<=y && y<C;
}

void dfs(int lastx,int lasty,int currx,int curry,int lastd)
{
    if(!InBoard(currx,curry) || m[currx][curry].c!='*') return;
    m[currx][curry].c='A';
    if(lastd==0)
    {
        m[lastx][lasty].block[0][1]=0;
        m[currx][curry].block[1][0]=2;
    }
    else if(lastd==1)
    {
        m[lastx][lasty].block[1][1]=1;
        m[currx][curry].block[0][0]=3;
    }
    else if(lastd==2)
    {
        m[lastx][lasty].block[1][0]=2;
        m[currx][curry].block[0][1]=0;
    }
    else
    {
        m[lastx][lasty].block[0][0]=3;
        m[currx][curry].block[1][1]=1;
    }
    for(int d=0;d<4;++d)
    {
        dfs(currx,curry,currx+dx[d],curry+dy[d],d);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>R>>C;
        m.assign(R,vector<Node>(C));
        for(vector<Node> &vn:m)
        {
            string s;
            cin>>s;
            for(int j=0;j<C;++j)
            {
                vn[j].c=s[j];
            }
        }
        m[0][0].c='A';
        dfs(0,0,0,1,0);
        dfs(0,0,1,0,1);
        vector<vector<int>> m2(R*2,vector<int>(C*2,-1));
        bool err=false;
        for(int i=0;i<R;++i)
        {
            for(int j=0;j<C;++j)
            {
                if(m[i][j].c=='*')
                {
                    err=true;
                    i=R;
                    break;
                }
                m2[i*2][j*2]=m[i][j].block[0][0];
                m2[i*2][j*2+1]=m[i][j].block[0][1];
                m2[i*2+1][j*2+1]=m[i][j].block[1][1];
                m2[i*2+1][j*2]=m[i][j].block[1][0];
            }
        }
        cout<<"Case #"<<icase<<": ";
        if(err)
        {
            cout<<"IMPOSSIBLE"<<endl;
            continue;
        }
        string s="ESWN";
        int x=0,y=0;
        do
        {
            int d=m2[x][y];
            cout<<s[d];
            x+=dx[d];
            y+=dy[d];
        } while (x!=0 || y!=0);
        cout<<endl;
    }
    return 0;
}
