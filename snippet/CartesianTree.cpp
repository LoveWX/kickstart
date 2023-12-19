笛卡尔树是一种特定的二叉树数据结构，可由数列构造，在范围最值查询、范围top k查询（range top k queries）等问题上有广泛应用。
笛卡尔树是一种二叉搜索树，每一个结点由一个键值二元组(k,w)构成。其中k满足二叉搜索树的性质，一般就代表数组下标；而w满足堆的性质。
一个有趣的事实是，如果笛卡尔树的 k,w 键值确定，且 k 互不相同， w 互不相同，那么这个笛卡尔树的结构是唯一的。
无相同元素的数列构造出的笛卡尔树具有下列性质：
1.结点一一对应于数列元素。即数列中的每个元素都对应于树中某个唯一结点，树结点也对应于数列中的某个唯一元素
2.中序遍历笛卡尔树即可得到原数列。即任意树结点的左子树结点所对应的数列元素下标比该结点所对应元素的下标小，右子树结点所对应数列元素下标比该结点所对应元素下标大。
3.树结构存在堆序性质，即任意树结点所对应数值大／小于其左、右子树内任意结点对应数值
根据堆序性质，笛卡尔树根结点为数列中的最大／小值，树本身也可以通过这一性质递归地定义：根结点为序列的最大／小值，左、右子树则对应于左右两个子序列，其结点同样为两个子序列的最大/小值。
因此，上述三条性质唯一地定义了笛卡尔树。笛卡尔树并不是平衡树
若数列中存在重复值，则可用其它排序原则为数列中相同元素排定序列，便能为含重复值的数列构造笛卡尔树。
可以通过单调栈在O(N)的时间中构造出笛卡尔树：
从左到右依次将数组的元素添加到笛卡尔树中，设树从根结点向右子树方向一直前进到叶结点的路径为右链
由于笛卡尔树的二叉搜索树性质，新加入的结点一定加在右链上
由于笛卡尔树的堆序性质，右链上的结点是单调的，最大堆则单调减，最小堆则单调增
因此，每次向笛卡尔树中添加结点P时，仿照单调栈的做法，从右链末端（叶结点端）依次查找能够维持单调性的结点
即查找结点A及其右子结点B使得A.val>P.val>B.val，结点P作为结点A的右子结点，结点B作为结点P的左子结点
特别地，如果结点P比根结点都大，那么将根结点作为结点P的左子结点即可
由于每个结点最多进出右链一次，因此总时间复杂度为O(N)

vector<int> l,r;
int CartesianTree(vector<int> &a)
{
    int N=a.size();
    l.assign(N,-1);
    r.assign(N,-1);
    vector<int> rstk(1,0);//添加第0个元素到右链
    for(int i=1;i<N;++i)
    {
        int lastpop=-1;
        while(!rstk.empty() && a[rstk.back()]<a[i])
        {
            lastpop=rstk.back();
            rstk.pop_back();
        }
        if(!rstk.empty())
        {
            r[rstk.back()]=i;
        }
        l[i]=lastpop;
        rstk.push_back(i);
    }
    return rstk[0];
}//rstk[0]即为笛卡尔树的根结点

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode *> rstk={new TreeNode(nums[0])};
        for(int i=1;i<nums.size();++i)
        {
            TreeNode *curr=new TreeNode(nums[i]);
            if(rstk[0]->val<nums[i])
            {
                curr->left=rstk[0];
                rstk={curr};
                continue;
            }
            while(rstk.back()->val<nums[i])
            {
                rstk.pop_back();
            }
            curr->left=rstk.back()->right;
            rstk.back()->right=curr;
            rstk.push_back(curr);
        }
        return rstk[0];
    }
};
