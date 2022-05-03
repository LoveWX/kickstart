#include <bits/stdc++.h>
using namespace std;

const double pi=3.1415926535898;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int R,A,B;
        cin>>R>>A>> B;
        double ans=0.0;
        while(R!=0)
        {
            ans+=pi*R*R;
            R*=A;
            ans+=pi*R*R;
            R/=B;
        }
        cout<<"Case #"<<icase<<": "<<setiosflags(ios::fixed)<<setprecision(8)<<ans<<endl;
    }
    return 0;
}
