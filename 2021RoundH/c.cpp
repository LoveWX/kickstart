#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

const int SIZE=500000;
map<int,int> ms;//<index,value>
vector<set<pair<int,int>>> vs;//vector<set<pair<index1,index2>>>

void Remove()
{
    for(set<pair<int,int>> &sp:vs)
    {
        for(const pair<int,int> &p:sp)
        {
            int &d1=ms[p.first],d2=(d1+1)%10,d3=(d2+1)%10,d0=(d1-1+10)%10;
            auto it0=prev(ms.find(p.first));
            auto it3=ms.upper_bound(p.second);
            int i1=p.first,i2=p.second,i3=it3->first,i0=it0->first;
            if(d0==it0->second)
            {
                vs[d0].erase({i0,i1});
            }
            if(d3==it3->second)
            {
                vs[d2].erase({i2,i3});
            }
            d1=d3;
            ms.erase(i2);
            if((d1+1)%10==it3->second)
            {
                vs[d1].insert({i1,i3});
            }
            d0=(d1-1+10)%10;
            if(d0==it0->second)
            {
                vs[d0].insert({i0,i1});
            }
        }
        sp.clear();
    }
}

int main()
{
    string S;
    S.reserve(SIZE);
    vs.assign(10,set<pair<int,int>>());
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N>>S;
        for(int i=0;i<N;++i)
        {
            ms[i]=S[i]-'0';
        }
        ms[-1]=-99;
        ms[N]=-99;
        for(int i=1;i<N;++i)
        {
            if((S[i-1]-'0'+1)%10==S[i]-'0')
            {
                vs[S[i-1]-'0'].insert({i-1,i});
            }
        }
        while(true)
        {
            bool end=true;
            for(set<pair<int,int>> &sp:vs)
            {
                if(!sp.empty())
                {
                    end=false;
                    break;
                }
            }
            if(end) break;
            Remove();
        }
        S.clear();
        ms.erase(-1);
        ms.erase(N);
        for(auto it=ms.begin();it!=ms.end();++it)
        {
            S.push_back('0'+it->second);
        }
        cout<<"Case #"<<icase<<": "<<S<<endl;
        ms.clear();
    }
    return 0;
}
