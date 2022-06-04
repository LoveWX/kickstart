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
        int n,x,y;
        cin>>n>>x>>y;
        long long s=(n+1)*n/2;
        if(s*x%(x+y)!=0)
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
            continue;
        }
        vector<int> va;
        int a=s*x/(x+y);
        for(int i=n;i>0 && a>0;--i)
        {
            if(a-i>=0)
            {
                va.push_back(i);
                a-=i;
            }
        }
        cout<<"Case #"<<icase<<": POSSIBLE"<<endl;
        cout<<va.size()<<endl;
        for(int i:va)
        {
            cout<<i<<' ';
        }
        cout<<endl;
    }
    return 0;
}
