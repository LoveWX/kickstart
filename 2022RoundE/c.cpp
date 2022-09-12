#include <bits/stdc++.h>
using namespace std;

int N;
string s;

bool Check(int k)
{
    if(N%k!=0) return false;
    for(int i=k;i<N;++i)
    {
        if(s[i%k]!=s[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>s;
        string ans=s;
        for(int i=1;i<N;++i)
        {
            if(Check(i))
            {
                ans=s.substr(0,i);
                break;
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
