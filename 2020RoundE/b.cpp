#include <iostream>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,A,B,C,D;
        cin>>N>>A>>B>>C;
        D=N-(A-C+C+B-C);
        if(N==1)
        {
            cout<<"Case #"<<icase<<": 1"<<endl;
            continue;
        }
        if(D<0 || (A-C==0 && C==1 && B-C==0))
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
            continue;
        }
        cout<<"Case #"<<icase<<":";
        for(int i=N-(A-C);i<N;++i)
        {
            cout<<' '<<i;
        }
        if(D!=0 && A-C!=0)
        {
            for(;D!=0;--D)
            {
                cout<<" 1";
            }
        }

        if(C>=2 && D!=0)
        {
            cout<<' '<<N;
            for(;D!=0;--D)
            {
                cout<<" 1";
            }
            for(int i=1;i<C;++i)
            {
                cout<<' '<<N;
            }
        }
        else
        {
            for(int i=0;i<C;++i)
            {
                cout<<' '<<N;
            }
        }

        if(D!=0 && B-C!=0)
        {
            for(;D!=0;--D)
            {
                cout<<" 1";
            }
        }
        for(int i=N-1;i>=N-(B-C);--i)
        {
            cout<<' '<<i;
        }
        cout<<endl;
    }
    return 0;
}
