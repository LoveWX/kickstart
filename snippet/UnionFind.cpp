// Ackerman函数定义如下：
// A(1, 0) = 2
// A(0, m) = 1                 ,m >= 0
// A(n, 0) = n + 2             ,n >= 2
// A(n, m) = A(A(n-1, m), m-1) ,n,m >= 1
// Ackerman函数增长极慢，可以想到的n，Ackerman^-1(n)<=5
// 所以带rank数组的并查集查找和合并效率可近似为常数级

//封装
struct UnionFind
{
    vector<int> parent;
    vector<int> rank;
    UnionFind(int n)
    {
        parent.assign(n,0);
        for(int i=1;i<n;++i)
        {
            parent[i]=i;
        }
        rank.assign(n,0);
    }
    int findr(int x)
    {
        int r=x;
        for(;r!=parent[r];r=parent[r]);
        for(int i=x;r!=parent[i];)
        {
            int j=parent[i];
            parent[i]=r;
            i=j;
        }
        return r;
    }
    void unionr(int x,int y)
    {
        int rx=findr(x),ry=findr(y);
        if(rank[rx]<rank[ry])
        {
            parent[rx]=ry;
        }
        else if(rank[rx]>rank[ry])
        {
            parent[ry]=rx;
        }
        else
        {
            parent[ry]=rx;
            rank[rx]+=1;
        }
    }
};

//用集合数代替rank进行合并,可以求出某元素所在集合的大小
struct UnionFind
{
    vector<int> parent;
    vector<int> vcnt;
    void Init(int n)
    {
        parent.assign(n,0);
        for(int i=1;i<n;++i)
        {
            parent[i]=i;
        }
        vcnt.assign(n,1);
    }
    int findr(int x)
    {
        int r=x;
        for(;r!=parent[r];r=parent[r]);
        for(int i=x;r!=parent[i];)
        {
            int j=parent[i];
            parent[i]=r;
            i=j;
        }
        return r;
    }
    void unionr(int x,int y)//合并到大集合中,一样大时合并到x所在集合
    {
        int rx=findr(x),ry=findr(y);
        if(rx==ry) return;
        if(vcnt[rx]<vcnt[ry])
        {
            parent[rx]=ry;
            vcnt[ry]+=vcnt[rx];
        }
        else
        {
            parent[ry]=rx;
            vcnt[rx]+=vcnt[ry];
        }
    }
    int count(int x)
    {
        return vcnt[findr(x)];
    }
};

//散装
int n;
vector<int> parent;
vector<int> rank;
int findr(int x)
{
    int r=x,i=x,j;
    for(;r!=parent[r];r=parent[r]);
    while(r!=parent[i])
    {
        j=parent[i];
        parent[i]=r;
        i=j;
    }
    return r;
}
void unionr(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rank[rx]<rank[ry])
    {
        parent[rx]=ry;
    }
    else if(rank[rx]>rank[ry])
    {
        parent[ry]=rx;
    }
    else
    {
        parent[ry]=rx;
        rank[rx]+=1;
    }
}
parent.assign(n,0);
for(int i=1;i<n;++i)
{
    parent[i]=i;
}
rank.assign(n,0);
