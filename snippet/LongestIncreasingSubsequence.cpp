//最长上升子序列，在数组中求单调递增的子序列的最大长度
//如果想要子序列尽可能的长，就需要子序列中的数上升得尽量慢。
//所以对于特定长度的子序列，最后一个值越小越好。
//可以用数组d[]记录下来对于每一种长度的子序列，最后一个值(最小)为多少。
//即d[i]表示长度为i的最长上升子序列的末尾元素的最小值。
//可以用反证法证明d[i]是关于i单调递增的：
//如果d[j]>=d[i] 且 j<i，则从长度为i的最长上升子序列的末尾删除i-j个元素，
//这个序列长度变为j，且第j个元素必定小于d[i]，也就小于d[j]。
//那么就找到了一个长度为j的最长上升子序列，并且末尾元素比d[j]小，
//与d[j]为长度为j的最长上升子序列的末尾元素的最小值相矛盾。因此数组d的单调性得证。

//可以令d[0]为INT_MIN，这样可以直接对原数组每个元素进行处理。当然，答案需要减掉这个1的长度
//对于每个元素curr，二分查找得到最小的i使得d[i]>=curr,这时长度为i的最长上升子序列的末尾元素即可以更新为curr
int lengthOfLIS(vector<int>& nums)
{
    vector<int> dp(1,INT_MIN);
    for(int i:nums)
    {
        if(dp.back()<i)
        {
            dp.push_back(i);
        }
        else
        {
            *lower_bound(dp.begin(),dp.end(),i)=i;
        }
    }
    return dp.size()-1;
}

//注意到这里的LIS最长为序列长度，因此dp也可以初始化为长度为n，值为inf的数组。这样就可以将dp数组的扩展和更新统一为一种操作
//当然求LIS时要去掉最后的值为inf的元素
//而如果要求以每个元素结尾的(包含该元素的前缀的)LIS，就可以使用这种方式。dp数组的意义类似。
//注意原数组的LIS为a数组的最大值
vector<int> CalcLIS(vector<int> &x)
{
    int n=x.size();
    vector<int> dp(n,INT_MAX),a(n);
    for(int i=0;i<n;++i)
    {
        auto it=lower_bound(dp.begin(),dp.end(),x[i]);
        *it=x[i];
        a[i]=it-dp.begin()+1;
    }
    return a;
}
