#include <iostream>
#include <vector>
using namespace std;

const int SIZE=5000;
int B[SIZE];

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,K;
        cin>>N>>K;
        for(int i=0;i<N;++i)
        {
            cin>>B[i];
        }
        int ans=N+1;
        vector<int> sumLen(K+1,N+1);
        sumLen[0]=0;
        for(int i=N-1;i>=0;--i)
        {
            int suml=0;
            for(int j=i;j>=0;--j)
            {
                suml+=B[j];
                if(suml>K) break;
                ans=min(ans,i-j+1+sumLen[K-suml]);
            }
            int sumr=0;
            for(int j=i;j<N;++j)
            {
                sumr+=B[j];
                if(sumr>K) break;
                sumLen[sumr]=min(sumLen[sumr],j-i+1);
            }
        }
        if(ans==N+1) ans=-1;
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
