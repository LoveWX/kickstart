#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int mask5=(1<<5)-1;
bool v5[1<<5];
bool v6[1<<6];

void Init()
{
    for(int i=(1<<5)-1;i>0;--i)
    {
        v5[i]=!(((i>>4)&1)==((i>>0)&1) && ((i>>3)&1)==((i>>1)&1));
    }
    for(int i=(1<<6)-1;i>0;--i)
    {
        v6[i]=v5[(i>>1)&mask5] && v5[i&mask5] && 
                !(((i>>5)&1)==((i>>0)&1) && ((i>>4)&1)==((i>>1)&1) && ((i>>3)&1)==((i>>2)&1));
    }
}

int main()
{
    Init();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int n;
        string s;
        cin>>n>>s;
        if(n<5)
        {
            cout<<"Case #"<<icase<<": POSSIBLE"<<endl;
            continue;
        }
        int mask=0;
        set<int> slast;
        slast.insert(0);
        for(int j=0;j<5;++j)
        {
            set<int> scurr;
            if(s[j]=='?')
            {
                for(int i:slast)
                {
                    scurr.insert((i<<1));
                    scurr.insert((i<<1)^1);
                }
            }
            else
            {
                for(int i:slast)
                {
                    scurr.insert((i<<1)+(s[j]-'0'));
                }
            }
            slast=move(scurr);
        }
        {
            set<int> scurr;
            for(int i:slast)
            {
                if(v5[i])
                {
                    scurr.insert(i);
                }
            }
            slast=move(scurr);
        }
        for(int j=5;j<n && !slast.empty();++j)
        {
            set<int> scurr;
            if(s[j]=='?')
            {
                for(int i:slast)
                {
                    int curr=(i<<1);
                    if(v6[curr]) scurr.insert(curr&mask5);
                    curr^=1;
                    if(v6[curr]) scurr.insert(curr&mask5);
                }
            }
            else
            {
                for(int i:slast)
                {
                    int curr=(i<<1)+(s[j]-'0');
                    if(v6[curr]) scurr.insert(curr&mask5);
                }
            }
            slast=move(scurr);
        }
        if(slast.empty())
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
        }
        else
        {
            cout<<"Case #"<<icase<<": POSSIBLE"<<endl;
        }
    }
    return 0;
}
