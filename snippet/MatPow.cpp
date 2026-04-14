const long long mod=1e9+7;
vector<vector<long long>> MatMul(vector<vector<long long>> &a,vector<vector<long long>> &b)
{
    size_t n=a.size();
    vector<vector<long long>> c(n,vector<long long>(n,0));
    for(size_t i=0U;i<n;++i){
        for(size_t j=0U;j<n;++j){
            long long &s=c[i][j];
            for(size_t k=0U;k<n;++k){
                s=(s+a[i][k]*b[k][j])%mod;
            }
        }
    }
    return c;
}

vector<long long> VecMulMat(vector<long long> &a,vector<vector<long long>> &b)
{
    size_t n=a.size();
    vector<long long> c(n,0);
    for(size_t i=0U;i<n;++i){
        long long &s=c[i];
        for(size_t k=0U;k<n;++k){
            s=(s+a[k]*b[k][i])%mod;
        }
    }
    return c;
}

vector<vector<long long>> MatPow(vector<vector<long long>> a,long long b)
{
    size_t n=a.size();
    vector<vector<long long>> c(n,vector<long long>(n,0));
    for(size_t i=0U;i<n;++i){
        c[i][i]=1;
    }
    for(;b;b>>=1){
        if(b&1LL) c=MatMul(c,a);
        a=MatMul(a,a);
    }
    return c;
}
