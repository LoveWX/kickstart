#include <iostream>
#include <vector>
#include <array>
using namespace std;

const int SIZE=1000;

int main()
{
    vector<array<int,2>> p(SIZE);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,A;
        cin>>N>>A;
        if(A<N-2)
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
            continue;
        }
        if(N==4)
        {
            cout<<"Case #"<<icase<<": POSSIBLE"<<endl;
            cout<<0<<' '<<0<<endl;
            cout<<0<<' '<<1<<endl;
            cout<<1<<' '<<A<<endl;
            cout<<1<<' '<<1<<endl;
            continue;
        }
        p.resize(0);
        int n=N/2;
        for(int x=0,y=1;x<n;++x,y^=1)
        {
            p.push_back({x,y});
        }
        A-=(n-1)*2;
        if(N%2!=0)
        {
            p.push_back({p.back()[0]+A,1});
            for(int i=p.size()-2;i>=0;--i)
            {
                p.push_back({p[i][0],p[i][1]+1});
            }
        }
        else
        {
            for(int i=p.size()-1;i>=0;--i)
            {
                p.push_back({p[i][0],p[i][1]+1});
            }
            p.back()[1]+=A;
        }
        cout<<"Case #"<<icase<<": POSSIBLE"<<endl;
        for(array<int,2> &a:p)
        {
            cout<<a[0]<<' '<<a[1]<<endl;
        }
    }
    return 0;
}
