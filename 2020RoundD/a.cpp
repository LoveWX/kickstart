#include <iostream>
#include <algorithm>
using namespace std;

const int SIZE=200000;
int V[SIZE+1];

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
            cin>>V[i];
        }
        V[N]=-1;
        int ans=0,preMax=-1;
        for(int i=0;i<N;++i)
        {
            if(preMax<V[i] && V[i]>V[i+1])
            {
                ans+=1;
            }
            preMax=max(preMax,V[i]);
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
