//Prim算法的每一步都会为一棵生长中的树添加一条边，该树最开始只有一个顶点，然后会添加V-1个边。
//每次总是添加生长中的树和树中除该生长的树以外的部分形成的切分的具有最小权值的横切边。
//Prim算法的时间复杂度为O(E+VlogV)。
struct cmp
{
    bool operator ()(const vector<int> &a,const vector<int> &b)
    {
        return a[1]==b[1] ? a[0]>b[0] : a[1]>b[1];
    }
};

int MinimumSpanningTree(int n,vector<vector<vector<int>>> &edge)
{
    vector<bool> visited(n,false);
    priority_queue<vector<int>,vector<vector<int>>,cmp> pq;
    pq.push({0,0});//可从任意结点开始,这里从第0点开始
    int count=0,ans=0;
    while(count<n && !pq.empty())
    {
        int dst=pq.top()[0];
        int dis=pq.top()[1];
        pq.pop();
        if(!visited[dst])
        {
            visited[dst]=true;
            ans+=dis;//处理当前边
            count++;
            for(vector<int> &vi:edge[dst])
            {
                if(!visited[vi[0]])
                {
                    pq.push(vi);
                }
            }
        }
    }
    return ans;
}
//按照边的权重顺序（从小到大）将边加入生成树中，但是若加入该边会与生成树形成环则不加入该边。直到树中含有V-1条边为止。
//Kruskal算法的时间复杂度为O(ElogE)。
//可以利用并查集来查找是否成环：当边的两个顶点的根节点不同，则该边可以加入最小生成树。
sort(connections.begin(),connections.end(),[](vector<int> &a,vector<int> &b){
    return a[2]<b[2];
});
int ans=0;
for(vector<int> &vi:connections)
{
    int rx=findr(vi[0]);
    int ry=findr(vi[1]);
    if(rx!=ry)
    {
        ans+=vi[2];
        unionr(rx,ry);
    }
}
int r=findr(1);
for(int i=2;i<n;++i)
{
    if(findr(i)!=r)
    {
        return -1;
    }
}
return ans;
