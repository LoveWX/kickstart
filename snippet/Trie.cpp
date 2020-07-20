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
            c[i]=NULL;
        }
    }
};

//插入操作
//insert(root,s,0);
void insert(TrieNode *curr,string &s,int pos)
{
	if(pos==s.length())
	{
		curr->isend=true;
		return;
	}
	TrieNode *&p=curr->c[s[pos]-'a'];
	if(p==NULL)
	{
		p=new TrieNode;
	}
	insert(p,s,pos+1);
}

//查找操作
//search(root,s,0)
bool search(TrieNode *curr,string &s,int pos)
{
	if(curr==NULL) return false;
	if(pos==s.length()) return curr->isend;
	return search(curr->c[s[pos]-'a'],s,pos+1);
}
