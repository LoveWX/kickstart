#include <iostream>
#include <algorithm>
using namespace std;

const int SIZE=100000;
int A[SIZE*3];

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int W,N;
        cin>>W>>N;
        for(int i=0;i<W;++i)
        {
            cin>>A[i];
            A[i]-=1;
        }
        sort(A,A+W);
        for(int i=0;i<W;++i)
        {
            A[i+W]=A[i]+N;
            A[i+W*2]=A[i]+N*2;
        }
        int countL=W/2,countR=W-1-countL;
        long long sumL=0LL,sumR=0LL;
        for(int i=W-countL;i<W;++i)
        {
            sumL+=A[W]-A[i];
        }
        for(int i=W+1;i<=W+countR;++i)
        {
            sumR+=A[i]-A[W];
        }
        long long ans=sumL+sumR;
        for(int i=W+1;i<W*2;++i)
        {
            long long diff=A[i]-A[i-1];
            sumL=sumL-(A[i-1]-A[i-1-countL])+countL*diff;
            sumR=sumR-countR*diff+(A[i+countR]-A[i]);
            ans=min(ans,sumL+sumR);
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
