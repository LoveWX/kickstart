//Dijkstra算法求单源最短路径。从起点到终点的最短路径可在循环中提前返回，时间复杂度O(V+ElogV)
//维持各点到目标点的距离，每次选择到目标点距离最短的点，标记为已访问，并用该点更新各点到目标点的距离
vector<vector<vector<int>>> edge; // edge[i]={{j,dis(i,j)}, ...}
void ShortestPathDijkstra(vector<int> &vdis,int src)
{
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;
    pq.push({0,src});
    while(!pq.empty())
    {
        int dis=pq.top()[0];
        int dst=pq.top()[1];
        pq.pop();
        if(dis>=vdis[dst])
        {
            continue;
        }
        vdis[dst]=dis;
        for(vector<int> &vi:edge[dst])
        {
            if(dis+vi[1]<vdis[vi[0]])
            {
                pq.push({dis+vi[1],vi[0]});
            }
        }
    }
}

//如果需要记录最短路径有多少条，则使用map来模拟priority_queue使得相同的路径归并在一起计算
vector<vector<vector<int>>> edge; // edge[i]={{j,dis(i,j)}, ...}
void ShortestPathDijkstra(vector<long long> &vdis,vector<int> &vcnt,int src)
{
    map<pair<long long,int>,int> m;
    m[{0,src}]=1;
    while(!m.empty())
    {
        auto it=m.begin();
        auto [dis,dst]=it->first;
        int cnt=it->second;
        m.erase(it);
        if(dis>vdis[dst])
        {
            continue;
        }
        if(dis==vdis[dst])
        {
            vcnt[dst]=(vcnt[dst]+cnt)%mod;
            continue;
        }
        vdis[dst]=dis;
        vcnt[dst]=cnt;
        for(vector<int> &vi:edge[dst])
        {
            if(dis+vi[1]<vdis[vi[0]])
            {
                m[{dis+vi[1],vi[0]}]=(m[{dis+vi[1],vi[0]}]+cnt)%mod;
            }
        }
    }
}

//FloydWarshall算法计算全源最短路径，时间复杂度O(n^3)
//使用邻接矩阵,将直连的边作为两点之间距离记录
//尝试新增每一个点k,如果dis(i,k)+dis(k,j)<dis(i,j)，就将dis(i,j)更新为dis(i,k)+dis(k,j)
void ShortestPathFloydWarshall(vector<vector<int>> &m)
{
    for(int i=0;i<N;++i)
    {
        m[i][i]=0;
    }
    for(int k=0;k<N;++k)
    {
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                m[i][j]=min(m[i][j],m[i][k]+m[k][j]);
            }
        }
    }
}
