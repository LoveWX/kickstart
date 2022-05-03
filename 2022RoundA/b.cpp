#include <iostream>
#include <vector>
#include <algorithm>
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
        int sum=0;
        for(char c:s)
        {
            sum+=c-'0';
        }
        char c='0'+(9-sum%9)%9;
        cout<<"Case #"<<icase<<": ";
        int i=0;
        if(c=='0')
        {
            cout<<s[0];
            i=1;
        }
        for(;i<s.size();++i)
        {
            if(c<s[i]) break;
            cout<<s[i];
        }
        cout<<c;
        for(;i<s.size();++i)
        {
            cout<<s[i];
        }
        cout<<endl;
    }
    return 0;
}
