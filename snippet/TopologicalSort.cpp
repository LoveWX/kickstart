// Topological Sort
// 对一个有向无环图(Directed Acyclic Graph, DAG)G进行拓扑排序，是将G中所有顶点排成一个线性序列，
// 使得图中任意一条边<u,v>∈E(G)，点u在线性序列中出现在点v之前。
// 通常，这样的线性序列称为满足拓扑次序(Topological Order)的序列，简称拓扑序列。
// 简单的说，由某个集合上的一个偏序得到该集合上的一个全序，这个操作称之为拓扑排序。

// 先从入度为0的点开始，将该结点加入结果序列，
// 去掉该结点所有的出边，即将该结点所有的直接子结点的入度减1,
// 如果某个直接子结点入度为0，则重复这一过程，直到所有点都加入结果序列。
// 如果仍有入度不为0的点，说明这些点中有环/原图不为DAG。

// 1.dfs
int n;
vector<int> indegree;
vector<bool> visited;
vector<int> ans;
void dfs(int curr)
{
    if(visited[curr]) return;
    visited[curr]=true;
    ans.push_back(curr);
    for(int i:edge[curr])
    {
        indegree[i]--;
        if(indegree[i]==0)
        {
            dfs(i);
        }
    }
}
// 计算每个点的入度
for(vector<int> &vi:edges)
{
    indegree[vi[1]]+=1;
}
for(int i=0;i<n;++i)
{
    if(indegree[i]==0)
    {
        dfs(i);
    }
}
for(bool b:visited)
{
    if(!b)
    {
        // 有点未访问到
    }
}

// 也可以在dfs过程中更新indegree，并替代visited数组。
// 但是注意这样需要把起始入度为0的点先收集好
int n;
vector<int> indegree;
vector<int> ans;
void dfs(int curr)
{
    if((--indegree[curr])<=0)
    {
        ans.push_back(curr);
        for(int i:adjedges[curr])
        {
            dfs(i);
        }
    }
}
// 计算每个点的入度
for(vector<int> &vi:edges)
{
    indegree[vi[1]]+=1;
}
vector<int> toDFS;
for(int i=0;i<n;++i)
{
    if(indegree[i]==0)
    {
        toDFS.push_back(i);
    }
}
for(int i:toDFS)
{
    dfs(i);
}
for(int i:indegree)
{
    if(i>0)
    {
        // 有点未访问到
    }
}

// 2.bfs
vector<int> indegree(n,0);
vector<int> ans;
// 计算每个点的入度
for(vector<int> &vi:edges)
{
    indegree[vi[1]]+=1;
}
queue<int> q;
for(int i=0;i<n;++i)
{
    if(indegree[i]==0)
    {
        q.push(i);
    }
}
while(!q.empty())
{
    int curr=q.front();
    q.pop();
    ans.push_back(curr);
    for(int i:adjedges[curr])
    {
        if((--indegree[i])==0)
        {
            q.push(i);
        }
    }
}
for(int i:indegree)
{
    if(i>0)
    {
        // 有点未访问到
    }
}

// 3.dfs 逆向访问
// 如果对DAG中指定的某些点作为根的子图进行拓扑排序，
// 可以修改dfs，在当前递归函数结束前将当前结点加入结果序列
// step 1.从指定的某个结点开始进行深度优先搜索；
// step 2.递归搜索当前结点所有未访问的子结点
// step 3.将当前节点加入结果序列
// step 4.搜索结束后，倒转结果序列即得到一种拓扑排序
// 这种方法相当于将所有单向边逆转方向求拓扑排序再逆转得到结果。
// 利用了沿单向边产生的递归来模拟逆转图后的某个结点正向递归的过程。
// 原图正向递归时没有未访问子结点的结点在逆转图中正是当时入度为0的点，
// 递归结束之前再入栈当前结点，对应于逆转图中递归入度为0的点时遍历其子结点。
// 利用回溯法维护一个递归起点到当前结点的路径，可以检测出遇到的环，注意这里的路径不同于visited数组
// 如果不判断环，那么结果序列中仍会包含环中的结点，但是丢失了环上某些边，相当于去掉这些边来“破环”
// 所以对于普通的拓扑排序而言，这种方法不能检测环，不好选取递归起点，因此并不好用
int n;
vector<bool> visited;
vector<int> ans;
void dfs(int curr)
{
    if(visited[curr]) return;
    visited[curr]=true;
    for(int i:adjedges[curr])
    {
        dfs(i);
    }
    ans.push_back(curr);
}
// 计算每个点的入度
for(vector<int> &vi:edges)
{
    indegree[vi[1]]+=1;
}
for(int i=0;i<n;++i)
{
    if(indegree[i]==0)
    {
        dfs(i);
    }
}
reverse(ans.begin(),ans.end());
for(bool b:visited)
{
    if(!b)
    {
        return false;
    }
}
