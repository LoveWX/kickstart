#include <bits/stdc++.h>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        vector<int> vr(N);
        for(int &i:vr)
        {
            cin>>i;
        }
        multiset<int> si(vr.begin(),vr.end());
        si.insert(-1);
        si.insert(INT_MAX);
        for(int &i:vr)
        {
            int j=i;
            si.erase(si.find(i));
            i=*prev(si.upper_bound(i*2));
            if(i==INT_MAX) i=-1;
            si.insert(j);
        }
        cout<<"Case #"<<icase<<':';
        for(int i:vr)
        {
            cout<<' '<<i;
        }
        cout<<endl;
    }
    return 0;
}
