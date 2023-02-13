#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

const int SIZE=200000;
int A[SIZE];

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        for(int i=0;i<N;++i)
        {
            cin>>A[i];
        }
        for(int i=1;i<N;++i)
        {
            A[i-1]=A[i]-A[i-1];
        }
        int ans=0,count=1;
        A[N-1]=INT_MAX;
        for(int i=1;i<N;++i)
        {
            if(A[i-1]==A[i])
            {
                count+=1;
            }
            else
            {
                ans=max(ans,count);
                count=1;
            }
        }
        cout<<"Case #"<<icase<<": "<<ans+1<<endl;
    }
    return 0;
}

