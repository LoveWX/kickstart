#include <bits/stdc++.h>
using namespace std;

int Calc(long long a)
{
    string s=to_string(a);
    for(int i=0,j=s.size()-1;i<j;++i,--j)
    {
        if(s[i]!=s[j])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        long long a;
        cin>>a;
        long long b=sqrt(a);
        int ans=0;
        if(b*b==a) ans=Calc(b--);
        for(;b>0;--b)
        {
            if(a%b==0)
            {
                ans+=Calc(b);
                ans+=Calc(a/b);
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
