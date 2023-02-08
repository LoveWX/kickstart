#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int L,N,D;
        char C;
        int pos=0;
        char dir;
        long long ans=0;
        for(cin>>L>>N;N!=0;--N)
        {
            cin>>D>>C;
            if(pos==0) dir=C;
            if(C=='C')
            {
                int a=pos+D;
                if(a<L)
                {
                    pos=a;
                }
                else if(pos==0)
                {
                    pos=a%L;
                    ans+=a/L;
                    dir='C';
                }
                else if(dir=='C')
                {
                    pos=a%L;
                    ans+=a/L;
                }
                else//if(dir=='A')
                {
                    pos=a%L;
                    ans+=a/L-1;
                    dir='C';
                }
            }
            else//if(C=='A')
            {
                int a=pos-D;
                if(a>0)
                {
                    pos=a;
                }
                else if(pos==0)
                {
                    pos=L-D%L;
                    ans+=D/L;
                    dir='A';
                }
                else if(dir=='A')
                {
                    pos=(a%L+L)%L;
                    ans+=-a/L+1;
                }
                else//if(dir=='C')
                {
                    pos=(a%L+L)%L;
                    ans+=-a/L;
                    dir='A';
                }
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
