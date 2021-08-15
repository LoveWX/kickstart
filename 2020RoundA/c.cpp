#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int SIZE=300;
int grid[SIZE][SIZE];
int R,C;

inline bool InBoard(int x,int y)
{
    return 0<=x && x<R && 0<=y && y<C;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>R>>C;
        priority_queue<tuple<int,int,int>> pq;
        for(int i=0;i<R;++i)
        {
            for(int j=0;j<C;++j)
            {
                cin>>grid[i][j];
                pq.push({grid[i][j],i,j});
            }
        }
        long long ans=0LL;
        while(!pq.empty())
        {
            auto [hh,xx,yy]=pq.top();
            pq.pop();
            if(grid[xx][yy]<0) continue;
            if(grid[xx][yy]<hh) ans+=hh-grid[xx][yy];
            hh=max(grid[xx][yy],hh)-1;
            grid[xx][yy]=-1;
            if(InBoard(xx-1,yy) && grid[xx-1][yy]>=0) pq.push({hh,xx-1,yy});
            if(InBoard(xx+1,yy) && grid[xx+1][yy]>=0) pq.push({hh,xx+1,yy});
            if(InBoard(xx,yy-1) && grid[xx][yy-1]>=0) pq.push({hh,xx,yy-1});
            if(InBoard(xx,yy+1) && grid[xx][yy+1]>=0) pq.push({hh,xx,yy+1});
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
