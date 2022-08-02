#include <iostream>
#include <string>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        string s;
        cin>>s;
        int n=s.size();
        int ans=0;
        int countKick=0;
        for(int i=0;i+4<n;)
        {
            if(s[i]=='K' && s[i+1]=='I' && s[i+2]=='C' && s[i+3]=='K')
            {
                countKick+=1;
                i+=3;
            }
            else if(s[i]=='S' && s[i+1]=='T' && s[i+2]=='A' && s[i+3]=='R' && s[i+4]=='T')
            {
                ans+=countKick;
                i+=5;
            }
            else
            {
                i+=1;
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
