#include <iostream>
#include <map>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int m[3][3];
        cin>>m[0][0]>>m[0][1]>>m[0][2];
        cin>>m[1][0]         >>m[1][2];
        cin>>m[2][0]>>m[2][1]>>m[2][2];
        map<int,int> mc;
        if((m[1][2]-m[1][0])%2==0) mc[m[1][0]+(m[1][2]-m[1][0])/2]+=1;
        if((m[2][1]-m[0][1])%2==0) mc[m[0][1]+(m[2][1]-m[0][1])/2]+=1;
        if((m[2][2]-m[0][0])%2==0) mc[m[0][0]+(m[2][2]-m[0][0])/2]+=1;
        if((m[2][0]-m[0][2])%2==0) mc[m[0][2]+(m[2][0]-m[0][2])/2]+=1;
        int ans=0;
        for(const auto &p:mc)
        {
            ans=max(ans,p.second);
        }
        if(m[2][0]-m[1][0]==m[1][0]-m[0][0]) ans+=1;
        if(m[2][2]-m[1][2]==m[1][2]-m[0][2]) ans+=1;
        if(m[0][2]-m[0][1]==m[0][1]-m[0][0]) ans+=1;
        if(m[2][2]-m[2][1]==m[2][1]-m[2][0]) ans+=1;
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
