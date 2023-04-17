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
        vector<char> vdict(26);
        for(char &c:vdict)
        {
            cin>>c;
        }
        unordered_set<string> ms;
        int N;
        cin>>N;
        for(int k=0;k<N;++k)
        {
            string s;
            cin>>s;
            for(char &c:s)
            {
                c=vdict[c-'A'];
            }
            ms.insert(s);
        }
        string ans=(ms.size()==N ? "NO" : "YES");
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
