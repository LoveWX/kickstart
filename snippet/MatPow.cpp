const long long mod=1e9+7;
vector<long long> VecMulMat(vector<long long> &b,vector<vector<long long>> &c)
{
    unsigned int n=b.size();
    vector<long long> a(n,0);
    for(unsigned int j=0U;j<n;++j){
        long long sum=0;
        for(unsigned int i=0U;i<n;++i){
            sum+=b[i]*c[i][j]%mod;
        }
        a[j]=sum%mod;
    }
    return a;
}
vector<long long> MatMulVec(vector<vector<long long>> &b,vector<long long> &c)
{
    unsigned int n=b.size();
    vector<long long> a(n,0);
    for(unsigned int i=0U;i<n;++i){
        long long sum=0;
        for(unsigned int j=0U;j<n;++j){
            sum+=b[i][j]*c[j]%mod;
        }
        a[i]=sum%mod;
    }
    return a;
}
vector<vector<long long>> MatMul(vector<vector<long long>> &b,vector<vector<long long>> &c)
{
    unsigned int n=b.size();
    vector<vector<long long>> a(n,vector<long long>(n,0));
    for(unsigned int i=0U;i<n;++i){
        for(unsigned int j=0U;j<n;++j){
            long long sum=0;
            for(unsigned int k=0U;k<n;++k){
                sum+=b[i][k]*c[k][j]%mod;
            }
            a[i][j]=sum%mod;
        }
    }
    return a;
}
vector<vector<long long>> MatPow(vector<vector<long long>> m,int p)
{
    unsigned int n=m.size();
    vector<vector<long long>> a(n,vector<long long>(n,0));
    for(unsigned int i=0U;i<n;++i){
        a[i][i]=1;
    }
    for(;p>0;p>>=1){
        if(p&1) a=MatMul(a,m);
        m=MatMul(m,m);
    }
    return a;
}
