//在无向图中求割边/桥
const int N=100001;
int low[N],dfn[N];
int fa[N];//dfs序下的父结点
int T;//时间戳
vector<vector<int>> edge;//邻接表

memset(dfn,-1,sizeof(dfn));
memset(low,-1,sizeof(low));
memset(subcnt,0,sizeof(subcnt));

void Tarjan(int i,int parent)
{
    fa[i]=parent;
    dfn[i]=low[i]=T++;
    for(int j:edge[i])
    {
        if(dfn[j]<0)
        {
            Tarjan(j,i);
            low[i]=min(low[i],low[j]);
        }
        else if(j!=parent)
        {
            low[i]=min(low[i],dfn[j]);
        }
    }
}

//对于结点i和其父结点p，如果满足
// dfn[p]<low[i]
//则边(p,i)为桥
