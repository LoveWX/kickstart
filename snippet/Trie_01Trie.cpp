//将整数的各个bit位从高到低看作二进制串,就可以用Trie树来处理记录整数.
//这样的Trie树称为01Trie树,多用于处理区间上的异或最值问题.如在整数集合中找到一个数a使其与给定的x的异或值最大.
//可以通过从高位到低位贪心的方法:如果可以在Trie树中找到x的该bit的翻转,说明集合中可以找到一个数y使得结果的该bit位为1
//那么结果的该bit位就可以取到1,并在Trie树中移动到这个子结点中;否则,只能移动到唯一的子结点.
//要注意的是,一个数和其自身的异或为0,在找最大值时可以添加到被查找集合中.

//带Remove的版本,由于一般不会使用01Trie树进行数的查找操作,因此没有Search接口
//由于此种情况下整数的长度固定,因此也不需要isend域.但是如果需要Remove就需要cnt域来记录结点使用次数
struct TrieNode
{
    int cnt[2];
    TrieNode *p[2];
    TrieNode()
    {
        cnt[0]=cnt[1]=0;
        p[0]=p[1]=nullptr;
    }
};

struct Trie
{
    const int MAXBIT=19;
    TrieNode *root;
    Trie()
    {
        root=new TrieNode;
    }
    void insert(TrieNode *curr,int bit,int a)
    {
        if(bit<0) return;
        int b=(a>>bit) & 1;
        TrieNode *&p=curr->p[b];
        if(p==nullptr) p=new TrieNode;
        curr->cnt[b]+=1;
        insert(p,bit-1,a);
    }
    void Insert(int a)
    {
        insert(root,MAXBIT,a);
    }
    void remove(TrieNode *curr,int bit,int a)
    {
        if(bit<0) return;
        int b=(a>>bit) & 1;
        TrieNode *p=curr->p[b];
        remove(p,bit-1,a);
        curr->cnt[b]-=1;
        if(curr->cnt[b]==0)
        {
            // delete curr->p[b];
            curr->p[b]=nullptr;
        }
    }
    void Remove(int a)
    {
        remove(root,MAXBIT,a);
    }
    void getMaxXOR(TrieNode *curr,int bit,int a,int &ans)
    {
        if(bit<0) return;
        TrieNode *p=nullptr;
        int b=(a>>bit) & 1;
        if(curr->cnt[b^1]!=0)
        {
            ans^=1<<bit;
            p=curr->p[b^1];
        }
        else
        {
            p=curr->p[b];
        }
        getMaxXOR(p,bit-1,a,ans);
    }
    int GetMaxXOR(int a)
    {
        int ans=0;
        getMaxXOR(root,MAXBIT,a,ans);
        return ans;
    }
};
//带Remove的版本end
//也可以写成数组的形式,但是要注意Remove里面不能直接delete结点,而是需要从叶结点向根结点方向删除
struct Trie
{
    const int MAXBIT=19;
    TrieNode *root;
    Trie()
    {
        root=new TrieNode;
    }
    void Insert(int a)
    {
        TrieNode *curr=root;
        for(int i=MAXBIT;i>=0;--i)
        {
            int b=(a>>i) & 1;
            TrieNode *&p=curr->p[b];
            if(p==nullptr) p=new TrieNode;
            curr->cnt[b]+=1;
            curr=p;
        }
    }
    void Remove(int a)
    {
        TrieNode *curr=root;
        for(int i=MAXBIT;i>=0;--i)
        {
            int b=(a>>i) & 1;
            curr->cnt[b]-=1;
            curr=curr->p[b];
        }
    }
    int GetMaxXOR(int a)
    {
        int ans=0;
        TrieNode *curr=root;
        for(int i=MAXBIT;i>=0;--i)
        {
            int b=(a>>i) & 1;
            if(curr->cnt[b^1]!=0)
            {
                ans^=1<<i;
                curr=curr->p[b^1];
            }
            else
            {
                curr=curr->p[b];
            }
        }
        return ans;
    }
};
//带Remove的数组版本end

//如果将每次插入一个结点之后整个Trie的状态单独保存成一个版本,就可以在之后任意读取之前的历史版本.
//但是这样时间和空间都会很大.由于Trie树添加一个结点之后,最多只会增加有限个结点:Trie树中增加的是字符串长度,01Trie树增加的是bit位数
//因此可以"复用"之前的结点来构建"新版本".
//可以新增一个结点作为新的root结点,同时和前一个版本的结点进行递归插入
//对于本次新增的子结点,就新建结点作为子结点;对于之前已有的子结点,就通过前一个版本的对应的子结点,挂到现在的结点下
//这样,新增的结点就可以访问到新建的结点,也可以访问到之前版本的结点
//另外,需要在各个结点中插入版本号,通常就是插入的序号,这样就可以通过对比版本号控制访问的版本区间,就可以在线回答历史版本区间的问题了
//具体到01Trie树上,可以用于在线回答区间异或最大值的问题
//一般预先开辟足够大的空间来存放结点和根结点.注意这里的新增的数从下标1开始
const static int SIZE=100000;

struct Trie_P
{
    const static int BIT=30;//2^30
    int n,cnt;
    int root[SIZE];
    int ch[SIZE*(BIT+1)][2];
    int ver[SIZE*(BIT+1)];
    Trie_P()
    {
        root[0]=0;
        n=1;
        ver[0]=-1;
        ch[0][0]=ch[0][1]=0;
        cnt=1;
    }
    void Insert(int val)
    {
        int currver=n;
        int last=root[n-1];
        root[n]=++cnt;
        int curr=root[n++];
        ver[curr]=currver;
        for(int b=BIT;b>=0;--b)
        {
            int c=(val>>b)&1;
            ch[curr][c^1]=ch[last][c^1];
            ch[curr][c]=++cnt;
            curr=ch[curr][c];
            last=ch[last][c];
            ver[curr]=currver;
        }
    }
    int GetMaxXOR(int L,int R,int val)
    {
        int ans=0;
        int curr=root[R];
        for(int b=BIT;b>=0;--b)
        {
            int c=(val>>b)&1;
            if(ver[ch[curr][c^1]]>=L)
            {
                curr=ch[curr][c^1];
                ans^=1<<b;
            }
            else
            {
                curr=ch[curr][c];
            }
        }
        return ans;
    }
};
//预先分配区间版本end
//也可以使用容器来实现这一点,注意如果开始时知道最大尺寸,可以使用reserve来预先分配空间.
//注意这里的新增的数从下标1开始
struct Trie_P
{
    const int BIT=30;
    vector<int> root;
    vector<array<int,2>> ch;
    vector<int> ver;
    Trie_P(int MAXSIZE=0)
    {
        if(MAXSIZE>0)
        {
            ch.reserve((MAXSIZE+1)*BIT);
            ver.reserve((MAXSIZE+1)*BIT);
            root.reserve(MAXSIZE+1);
        }
        ch.push_back({0,0});
        ver.push_back(-1);
        root.push_back(0);
    }
    void Insert(int a)
    {
        int currver=root.size();
        int last=root.back(),curr=ch.size();
        ch.push_back(array<int,2>());
        ver.push_back(currver);
        root.push_back(curr);
        for(int b=BIT;b>=0;--b)
        {
            int c=(a>>b)&1;
            ch[curr][c^1]=ch[last][c^1];
            ch[curr][c]=ch.size();
            ch.push_back(array<int,2>());
            ver.push_back(currver);
            curr=ch[curr][c];
            last=ch[last][c];
        }
    }
    int GetMaxXOR(int L,int R,int val)
    {
        int ans=0;
        int curr=root[R];
        for(int b=BIT;b>=0;--b)
        {
            int c=(val>>b)&1;
            if(ver[ch[curr][c^1]]>=L)
            {
                ans^=1<<b;
                curr=ch[curr][c^1];
            }
            else
            {
                curr=ch[curr][c];
            }
        }
        return ans;
    }
};
//容器版本end
//虽然采用指针临时分配空间可以从下标0开始,也可以节省空间,但是由于新增结点指向之前版本结点,delete时会比较麻烦
struct TrieNode
{
    int ver;
    TrieNode *p[2];
    TrieNode()
    {
        ver=0;
        p[0]=p[1]=nullptr;
    }
};

struct Trie_P
{
    const int BIT=30;
    vector<TrieNode *> vroot;
    void Insert(int a)
    {
        int currver=vroot.size();
        TrieNode *last=(vroot.empty() ? nullptr : vroot.back());
        TrieNode *curr=new TrieNode;
        curr->ver=currver;
        vroot.push_back(curr);
        for(int b=BIT;b>=0;--b)
        {
            int c=(a>>b)&1;
            curr->p[c^1]=(last==nullptr ? nullptr : last->p[c^1]);
            curr->p[c]=new TrieNode;
            if(last!=nullptr) last=last->p[c];
            curr=curr->p[c];
            curr->ver=currver;
        }
    }
    int GetMaxXOR(int L,int R,int val)
    {
        int ans=0;
        TrieNode *curr=vroot[R];
        for(int b=BIT;b>=0;--b)
        {
            int c=(val>>b)&1;
            if(curr->p[c^1]!=nullptr && curr->p[c^1]->ver>=L)
            {
                ans^=1<<b;
                curr=curr->p[c^1];
            }
            else
            {
                curr=curr->p[c];
            }
        }
        return ans;
    }
};
//指针版本end
