//字典树，又称单词查找树，Trie树，是一种树形结构，是哈希树的变种。用于统计、排序、查找大量的字符串（但不仅限于字符串），经常被搜索引擎系统用于文本词频统计。
//优点：利用字符串的公共前缀来减少查询时间，最大限度地减少无谓的字符串比较，查询效率比哈希树高。
//性质：根节点不包含字符，除根节点外每一个节点都只包含一个字符；从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串；
//因为Trie树指代了一系列的字符串，当需要将字典中的每个字符串进行操作时，可以使用Trie树中的节点来进行操作，这样可以合并相同前缀的操作。
//具体在Trie树中进行dfs时，既可以传入Trie树节点指代某一字符，也可以传入其父节点指针。

//节点数据结构如下。
//字典树根节点没有字符，可以用来表示空串，其子节点指示非空串的第一个字符
//isend:标识从根节点到该节点的路径所表示的字符串是否为一个合法的(在字典中的)字符串
//c:可继续拓展的下一个节点,这里26表示合法字符为小写字母。可以扩展,需要添加遍历规则
struct TrieNode
{
    bool isend;
    TrieNode *c[26];
    TrieNode()
    {
        isend=false;
        for(int i=0;i<26;++i)
        {
            c[i]=nullptr;
        }
    }
};

//插入操作
//Insert(root,s,0);
void Insert(TrieNode *curr,string &s,int pos)
{
    if(pos==s.size())
    {
        curr->isend=true;
        return;
    }
    TrieNode *&p=curr->c[s[pos]-'a'];
    if(p==nullptr)
    {
        p=new TrieNode;
    }
    Insert(p,s,pos+1);
}

//查找操作
//search(root,s,0)
bool Search(TrieNode *curr,string &s,int pos)
{
    if(curr==nullptr) return false;
    if(pos==s.size()) return curr->isend;
    return Search(curr->c[s[pos]-'a'],s,pos+1);
}

//简化版本end

//也可以使用循环代替递归以减小函数调用开销.以下是封装的循环版本,其中多了StartWith的操作
struct TrieNode
{
    bool isend;
    TrieNode *c[26];
    TrieNode()
    {
        isend=false;
        for(int i=0;i<26;++i)
        {
            c[i]=nullptr;
        }
    }
};

struct Trie
{
    TrieNode *root;
    Trie()
    {
        root=new TrieNode;
    }
    void insert(string &word)
    {
        TrieNode *curr=root;
        for(char c:word)
        {
            TrieNode *&p=curr->c[c-'a'];
            if(p==nullptr) p=new TrieNode;
            curr=p;
        }
        curr->isend=true;
    }
    bool search(string &word)
    {
        TrieNode *curr=root;
        for(char c:word)
        {
            TrieNode *&p=curr->c[c-'a'];
            if(p==nullptr) return false;
            curr=p;
        }
        return curr->isend;
    }
    bool startsWith(string &prefix)
    {
        TrieNode *curr=root;
        for(char c:prefix)
        {
            TrieNode *&p=curr->c[c-'a'];
            if(p==nullptr) return false;
            curr=p;
        }
        return true;
    }
};

//封装的循环版本end

//也可以加入Remove,但是要注意删除操作需要在每个结点中增加cnt域,标识该结点的使用次数/是多少个字符串的前缀
//在成功删除字符串时,相关结点的使用次数均减1.
//可以不用在Remove操作中delete结点,但是这样StartsWith操作也需要判断cnt域才能判断某个前缀是否存在
struct TrieNode
{
    bool isend;
    int cnt;
    TrieNode *c[26];
    TrieNode()
    {
        isend=false;
        cnt=0;
        for(int i=0;i<26;++i)
        {
            c[i]=nullptr;
        }
    }
};

struct Trie
{
    TrieNode *root;
    Trie()
    {
        root=new TrieNode;
    }
    void insert(TrieNode *curr,string &s,int pos)
    {
        curr->cnt+=1;
        if(pos==s.size())
        {
            curr->isend=true;
            return;
        }
        TrieNode *&p=curr->c[s[pos]-'a'];
        if(p==nullptr) p=new TrieNode;
        insert(p,s,pos+1);
    }
    void Insert(string &s)
    {
        insert(root,s,0);
    }
    bool search(TrieNode *curr,string &s,int pos)
    {
        if(curr==nullptr) return false;
        if(pos==s.size()) return curr->isend;
        return search(curr->c[s[pos]-'a'],s,pos+1);
    }
    bool Search(string &s)
    {
        return search(root,s,0);
    }
    bool startsWith(TrieNode *curr,string &s,int pos)
    {
        if(curr==nullptr) return false;
        if(pos==s.size()) return curr->cnt>0;
        return startsWith(curr->c[s[pos]-'a'],s,pos+1);
    }
    bool StartsWith(string &s)
    {
        return startsWith(root,s,0);
    }
    bool remove(TrieNode *curr,string &s,int pos)
    {
        if(curr==nullptr) return false;
        if(pos==s.size())
        {
            bool found=curr->isend;
            curr->isend=false;
            curr->cnt-=1;
            return found;
        }
        bool found=remove(curr->c[s[pos]-'a'],s,pos+1);
        if(found) curr->cnt-=1;
        return found;
    }
    bool Remove(string &s)
    {
        return remove(root,s,0);
    }
    void dfsDel(TrieNode *curr)
    {
        for(TrieNode *p:curr->c)
        {
            if(p!=nullptr)
            {
                dfsDel(p);
            }
        }
        delete curr;
    }
    ~Trie()
    {
        dfsDel(root);
    }
};

//封装版本_带Remove和析构版本end

//也有一种不用指针的写法,可以将vector当作申请的结点,用下标代替指针来给每个字符分配结点
struct Trie
{
    vector<vector<int>> ch;
    vector<bool> isend;
    Trie()
    {
        ch.push_back(vector<int>(26,0));
        isend.push_back(false);
    }
    void insert(string &s)
    {
        int curr=0;
        for(char c:s)
        {
            int &next=ch[curr][c-'a'];
            if(next==0)
            {
                next=(int)ch.size();
                ch.push_back(vector<int>(26,0));
                isend.push_back(false);
            }
            curr=next;
        }
        isend[curr]=true;
    }
    bool search(string &s)
    {
        int curr=0;
        for(char c:s)
        {
            int &next=ch[curr][c-'a'];
            if(next==0) return false;
            curr=next;
        }
        return isend[curr];
    }
    bool startsWith(string &s)
    {
        int curr=0;
        for(char c:s)
        {
            int &next=ch[curr][c-'a'];
            if(next==0) return false;
            curr=next;
        }
        return true;
    }
};

//封装的数组版本end
