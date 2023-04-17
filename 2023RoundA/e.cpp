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
        string s;
        cin>>s;
        int ans=0;
        int i=0;
        for(;!s.empty() && s[0]==s.back();)
        {
            ans+=1;
            s.pop_back();
        }
        int n=s.size();
        if(n==0)
        {
            ans=(ans+1)/2;
            cout<<"Case #"<<icase<<": "<<ans<<endl;
            continue;
        }
        for(;i<n && s[0]==s[i];++i);
        ans=(ans+i)/2;
        for(;i<n;)
        {
            int j;
            for(j=i+1;j<n && s[i]==s[j];++j);
            ans+=(j-i)/2;
            i=j;
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
