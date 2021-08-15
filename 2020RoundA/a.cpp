#include <iostream>
#include <string>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,K;
        string S;
        cin>>N>>K>>S;
        int count=0;
        for(int i=0,j=N-1;i<j;++i,--j)
        {
            if(S[i]!=S[j])
            {
                count+=1;
            }
        }
        cout<<"Case #"<<icase<<": "<<abs(K-count)<<endl;
    }
    return 0;
}
