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
        int n;
        string s;
        cin>>n>>s;
        bool digit=false,up=false,low=false,special=false;
        for(char c:s)
        {
            if(isdigit(c))
            {
                digit=true;
            }
            else if(isupper(c))
            {
                up=true;
            }
            else if(islower(c))
            {
                low=true;
            }
            else if(c=='#' || c=='@' || c=='*' || c=='&')
            {
                special=true;
            }
        }
        if(!digit) s+='0';
        if(!up) s+='A';
        if(!low) s+='a';
        if(!special) s+='#';
        if(s.size()<7) s+=string(7-s.size(),'a');
        cout<<"Case #"<<icase<<": "<<s<<endl;
    }
    return 0;
}
