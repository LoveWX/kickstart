#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        string S;
        cin>>N>>S;
        vector<int> vi(N,1);
        for(int i=1;i<N;++i)
        {
            if(S[i-1]<S[i])
            {
                vi[i]=vi[i-1]+1;
            }
        }
        cout<<"Case #"<<icase<<':';
        for(int i=0;i<N;++i)
        {
            cout<<' '<<vi[i];
        }
        cout<<endl;
    }
    return 0;
}
