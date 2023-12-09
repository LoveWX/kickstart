长度为2^N的数组每个下标可以用一个bit位来表示,用某个(N bit的)掩码mask表示下标为mask子掩码的所有元素组成的集合.
而Sum over Subsets(SOS)用于计算某个掩码对应的所有子掩码的问题.
例如:给定长度为2^N的数组A,定义函数F(x)=Sum(A[i]),x&i==i,即i为x的子集,计算所有的F(x)

如果暴力计算,时间复杂度为O(4^N);如果对每个掩码枚举子掩码来计算,时间复杂度为O(3^N)
这两种方法没有用到各个掩码之间的关系,因此有很多重复计算

设S(mask)为mask所有的子掩码的集合,设S(mask,i)为mask所有子掩码的集合,但是这些子掩码与mask相比只在低i bit不同,这里下标从0开始,即最低位为第0 bit
相当于从高位到低位将mask依次划分为更小的子集的并,直到划分完最后一位,得到的每个集合都只有一个元素,这些元素都是mask的子掩码
考虑mask的第i位,如果为0,说明mask的子掩码在第i位只能为0,因此S(mask,i)只能划分为一个集合:S(mask,i-1)
如果为1,那么mask的子掩码在第i位可以为1,对应的集合为S(mask,i-1)
也可以为0,对应的集合为S(mask ^ (1<<i),i-1)
因此有: S(mask,i) = S(mask,i-1) , 第i bit为0
        S(mask,i) = S(mask,i-1) 并 S(mask ^ (1<<i),i-1) , 第i bit为1

可以写出DP的代码:
//iterative version
    for(int mask = 0; mask < (1<<N); ++mask){
        dp[mask][-1] = A[mask];	//handle base case separately (leaf states)
        for(int i = 0;i < N; ++i){
            if(mask & (1<<i))
                dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
            else
                dp[mask][i] = dp[mask][i-1];
        }
        F[mask] = dp[mask][N-1];
    }

注意到实际上每个dp[mask][i]只依赖dp[mask1][i-1],因此可以优化存储空间
    for(int i=0;i<N;++i)
    {
        for(int j=(1<<N)-1;j>=0;--j)
        {
            if((j>>i)&1)
            {
                F[j^(1<<i)]+=F[j];
            }
        }
    }

而另外也注意到,当进入内层的if语句时,说明此时掩码j的第i bit为1,需要额外累加的掩码j^(1<<i)为0
即在本轮(最外层)循环中F[j^(1<<i)]不会改变,因此也可以从小到大遍历
    for(int i=0;i<N;++i)
    {
        for(int j=0;j<(1<<N);++j)
        {
            if((j>>i)&1)
            {
                F[j^(1<<i)]+=F[j];
            }
        }
    }

参考:https://codeforces.com/blog/entry/45223
