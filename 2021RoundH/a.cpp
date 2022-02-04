#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        string S,F;
        cin>>S>>F;
        vector<int> dis(26,-1);
        for(char c:F)
        {
            dis[c-'a']=0;
        }
        for(int i=0;i<26;++i)
        {
            if(dis[i]==0) continue;
            int d1=1,d2=1;
            for(int j=(i+1)%26;dis[j]!=0;j=(j+1)%26)
            {
                d1+=1;
            }
            for(int j=(i-1+26)%26;dis[j]!=0;j=(j-1+26)%26)
            {
                d2+=1;
            }
            dis[i]=min(d1,d2);
        }
        int ans=0;
        for(char c:S)
        {
            ans+=dis[c-'a'];
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
