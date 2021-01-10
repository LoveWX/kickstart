数位dp是一种用于计数的dp，一般是要统计区间[left,right]内满足一定条件的数的个数。
这些条件一般是数本身的性质，或者是连续数位组合之和的性质。也就是和“每一位的数”有关系。
一般用于处理十进制，但是其它进制方法类似。
1.对于区间[left,right]，类似于前缀和，一般用F([0,right])-F([0,left-1])来计算。F(0)已经减掉不在差值中，是否计算不重要
2.对于给定上界，计算每一个数位。
3.从高到低遍历每个数位。
3.1.用一个入参limit来表示该位的高位是否已经到达上界，如果到达上界，那该位也需要考虑上界，否则遍历0-9
3.2.limit可以作为dp的一维中间结果记录下来，但是由于情况较少O(logn)且不会重复计算，所以一般不保存。
3.3.通过limit计算出本数位可能的值，结合给定的其它条件，分别遍历本位可能的值，并用dp计算出更低位的结果。累计和即为当前结果。
整个过程更像是带记忆化的dfs。
一般而言，当dfs到某一位时，函数的入参表示的是该位更高位的状态，按给定的条件定制。
一般limit都需要有，因为limit反映了是否到达上界。表示是否有前导0的leading也经常需要。
该位更低位的结果，是通过递归调用函数dp更低位来获得的。
通过遍历该位可能的值，将状态传入更低位，并得到结果，累加后得到该位的总结果，记录下来并返回给更高位。
也就是说：状态从高位到低位传递，结果从低位到高位累计。

int a[20];//存储各个数位上的值
int mem[20][9];//存储每个数位各种状态下的个数

int dp(int pos,int state,int leading,int limit)
{
    //递归边界,最低位是0,pos==-1说明已经枚举完了,需要根据入参返回符合状态的数的个数,一般返回1
    if(pos==-1)
    {
        return 1;
    }
    //只记录不在上界时的中间结果
    if(!limit && !lead && mem[pos][state]!=-1)
    {
        return mem[pos][state];
    }
    //计算本数位的上界
    int top=limit ? a[pos] : 9;
    int ans=0;
    //枚举本数位所有值
    for (int i = 0; i <= top; ++i)
    {
        if () ;//根据给定条件去掉某些值
        //把本数位信息和更高位信息传给更低位,计算结果并累加
        ans+=dp(pos - 1,newstate/*状态转移*/,lead && i==0,limit && i == a[pos]);
    }
    if(!limit && !lead)
    {
        mem[pos][state] = ans;
    }
    return ans;
}

int Calc(int n)
{
    memset(mem, -1, sizeof(mem));
    int pos=0;
    while(n!=0)
    {
        a[pos++]=n%10;
        n/=10;
    }
    //传入初始状态开始dp
    //此时没有更高位,可以传入必定符合条件的状态
    //leading和limit传入true,表示从上界开始dp。dp过程中上界和非上界的结果都会累加
    return dp(pos-1,0,1,1);
}

int a[20];
int mem[20][9];

int dp(int pos,int state,int leading,int limit)
{
    if(pos==-1)
    {
        return 1;
    }
    if(!limit && !lead && mem[pos][state]!=-1)
    {
        return mem[pos][state];
    }
    int top=limit ? a[pos] : 9;
    int ans=0;
    for (int i = 0; i <= top; ++i)
    {
        if () ;
        ans+=dp(pos - 1,newstate,lead && i==0,limit && i == a[pos]);
    }
    if(!limit && !lead)
    {
        mem[pos][state] = ans;
    }
    return ans;
}

int Calc(int n)
{
    memset(mem, -1, sizeof(mem));
    int pos=0;
    while(n!=0)
    {
        a[pos++]=n%10;
        n/=10;
    }
    return dp(pos-1,0,1,1);
}
