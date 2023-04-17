#include <bits/stdc++.h>
using namespace std;

vector<long long> vnum;

void Init()
{
    const long long MAXV=1e12;
    vnum.reserve(277351);
    long long curr=1;
    vnum.push_back(0);
    for(int i=1;curr<=MAXV;++i)
    {
        vnum.push_back(curr);
        curr+=i*26LL;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Init();
    // cout<<vnum.size()<<endl;
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        long long n;
        cin>>n;
        int i=upper_bound(vnum.begin(),vnum.end(),n)-vnum.begin()-1;
        char c=(n-vnum[i])/i+'A';
        cout<<"Case #"<<icase<<": "<<c<<endl;
    }
    return 0;
}
