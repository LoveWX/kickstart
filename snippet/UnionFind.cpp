// Ackerman函数定义如下：
// A(1, 0) = 2
// A(0, m) = 1                 ,m >= 0
// A(n, 0) = n + 2             ,n >= 2
// A(n, m) = A(A(n-1, m), m-1) ,n,m >= 1
// Ackerman函数增长极慢，可以想到的n，Ackerman^-1(n)<=5
// 所以带rank数组的并查集查找和合并效率可近似为常数级

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
