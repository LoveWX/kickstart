////对顶堆,由一个最小堆和一个最大堆组成,主要用于维护变长数组的前k大的元素的和
//这里用最小堆维护前k大元素，用最大堆维护其它元素。其中最小堆的期望尺寸sz1可以调节，注意调节后需要立即尝试适配

//用堆实现的带懒删除的版本,速度更快
struct DualHeapMax
{
    priority_queue<int,vector<int>,greater<int>> pq1,del1;
    priority_queue<int> pq2,del2;
    size_t sz1;//需要维持的pq1的大小
    long long sum1,sum2;
    DualHeapMax(size_t size1)
    {
        sz1=size1;
        sum1=sum2=0;
    }
    int Top1()
    {
        while(!del1.empty() && pq1.top()==del1.top()){
            pq1.pop();
            del1.pop();
        }
        return pq1.top();
    }
    int Top2()
    {
        while(!del2.empty() && pq2.top()==del2.top()){
            pq2.pop();
            del2.pop();
        }
        return pq2.top();
    }
    size_t Size1()
    {
        return pq1.size()-del1.size();
    }
    size_t Size2()
    {
        return pq2.size()-del2.size();
    }
    void Add(int val)
    {
        pq1.push(val);
        sum1+=val;
        Adjust();
    }
    void Del(int val)
    {
        if(Size1()>0 && val>=Top1()){
            del1.push(val);
            sum1-=val;
        }else{
            del2.push(val);
            sum2-=val;
        }
        Adjust();
    }
    void Adjust()
    {
        while(Size1()>sz1){
            int val=Top1();
            pq1.pop();
            sum1-=val;
            pq2.push(val);
            sum2+=val;
        }
        while(Size1()<sz1 && Size2()>0){
            int val=Top2();
            pq2.pop();
            sum2-=val;
            pq1.push(val);
            sum1+=val;
        }
    }
};

//multiset版本
struct DualHeapMax
{
    multiset<int> s1,s2;
    size_t sz1;//需要维持的s1的大小
    long long sum1,sum2;
    DualHeapMax(size_t size1)
    {
        sz1=size1;
        sum1=0;
        sum2=0;
    }
    int Top1()
    {
        return *s1.begin();
    }
    int Top2()
    {
        return *s2.rbegin();
    }
    void Add(int val)
    {
        s1.insert(val);
        sum1+=val;
        Adjust();
    }
    void Del(int val)
    {
        if(auto it1=s1.find(val);it1!=s1.end()){
            s1.erase(it1);
            sum1-=val;
        }else{
            s2.erase(s2.find(val));
            sum2-=val;
        }
        Adjust();
    }
    void Adjust()
    {
        while(s1.size()>sz1){
            int val=*s1.begin();
            s1.erase(s1.begin());
            sum1-=val;
            s2.insert(val);
            sum2+=val;
        }
        while(s1.size()<sz1 && !s2.empty()){
            int val=*s2.rbegin();
            s2.erase(prev(s2.end()));
            sum2-=val;
            s1.insert(val);
            sum1+=val;
        }
    }
};
