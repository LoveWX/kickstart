#include <iostream>
#include <array>
#include <algorithm>
#include <cstring>
using namespace std;

const int SIZE=500000;
array<array<int,2>,SIZE> P; 
int N;

int n; // length of bit
int bitLeft[1000001];
int bitRight[1000001];

int prefixSum(int *bit,int idx)
{
    int sum=0;
    while(idx!=0)
    {
        sum+=bit[idx];
        idx-=(idx & -idx);
    }
    return sum;
}

void update(int *bit,int idx,int diff)
{
    while(idx<=n)
    {
        bit[idx]+=diff;
        idx+=(idx & -idx);
    }
}

int rangeSum(int *bit,int idx1,int idx2)
{
    return prefixSum(bit,idx2)-prefixSum(bit,idx1-1);
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        long long A,B,C,D,E,F,M;
        cin>>N;
        cin>>P[0][0]>>P[0][1]>>A>>B>>C>>D>>E>>F>>M;
        for(int i=1;i<N;++i)
        {
            // Vi = (A × Vi-1 + B × Hi-1 + C) modulo M
            // Hi = (D × Vi-1 + E × Hi-1 + F) modulo M
            P[i][0]=(A*P[i-1][0]+B*P[i-1][1]+C)%M;
            P[i][1]=(D*P[i-1][0]+E*P[i-1][1]+F)%M;
        }

        n=M;
        memset(bitLeft,0,(n+1)*sizeof(int));
        memset(bitRight,0,(n+1)*sizeof(int));
        for(int i=0;i<N;++i)
        {
            P[i][0]+=1;
            P[i][1]+=1;
            update(bitRight,P[i][1],1);
        }
        sort(P.begin(),P.begin()+N);

        long long ans=(long long)N*(N-1)/2*(N-2)/3;
        for(int i=0;i<N;)
        {
            int j=i;
            for(;j<N && P[j][0]==P[i][0];++j)
            {
                update(bitRight,P[j][1],-1);
            }
            for(int k=i;k<j;++k)
            {
                long long leftup=rangeSum(bitLeft,P[k][1]+1,n);
                long long leftdown=prefixSum(bitLeft,P[k][1]-1);
                long long rightup=rangeSum(bitRight,P[k][1]+1,n);
                long long rightdown=prefixSum(bitRight,P[k][1]-1);
                ans-=leftup*rightdown+leftdown*rightup;
            }
            for(;i<j;++i)
            {
                update(bitLeft,P[i][1],1);
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
