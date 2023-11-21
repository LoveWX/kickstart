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
