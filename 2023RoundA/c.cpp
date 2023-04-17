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
        int N;
        cin>>N;
        vector<int> vcolor(N);
        for(int &c:vcolor)
        {
            cin>>c;
        }
        unordered_set<int> si;
        int lastcolor=-1;
        vector<int> vi;
        vi.reserve(N);
        for(int c:vcolor)
        {
            if(c==lastcolor) continue;
            if(si.count(c)!=0)
            {
                vi.clear();
                break;
            }
            si.insert(c);
            vi.push_back(c);
            lastcolor=c;
        }
        if(vi.empty())
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
            continue;
        }
        cout<<"Case #"<<icase<<":";
        for(int c:vi)
        {
            cout<<' '<<c;
        }
        cout<<endl;
    }
    return 0;
}
