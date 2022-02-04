#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        string s;
        cin>>s;
        map<char,int> mchar;
        for(char c:s)
        {
            mchar[c]+=1;
        }
        priority_queue<pair<int,char>> pq;
        for(const auto &p:mchar)
        {
            pq.push({p.second,p.first});
        }
        if(pq.top().first>s.size()-pq.top().first)
        {
            cout<<"Case #"<<icase<<": IMPOSSIBLE"<<endl;
            continue;
        }
        vector<string> ms(26);
        while(!pq.empty())
        {
            auto [counta,a]=pq.top();
            pq.pop();
            auto [countb,b]=pq.top();
            pq.pop();
            if(counta==1 && countb==1 && pq.size()==1 && pq.top().first==1)
            {
                char c=pq.top().second;
                ms[a-'a'].push_back(b);
                ms[b-'a'].push_back(c);
                ms[c-'a'].push_back(a);
                break;
            }
            ms[a-'a'].push_back(b);
            ms[b-'a'].push_back(a);
            counta-=1;
            if(counta!=0) pq.push({counta,a});
            countb-=1;
            if(countb!=0) pq.push({countb,b});
        }
        string ans;
        ans.reserve(s.size());
        for(char c:s)
        {
            string &ts=ms[c-'a'];
            ans.push_back(ts.back());
            ts.pop_back();
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
