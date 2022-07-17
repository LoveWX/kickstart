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
        int N,M;
        cin>>N;
        vector<int> S;
        S.reserve(N);
        for(int i=0,tlast=-1;i<N;++i)
        {
            int t;
            cin>>t;
            if(tlast!=t)
            {
                S.push_back(t);
                tlast=t;
            }
        }
        N=S.size();
        cin>>M;
        vector<int> K(M);
        map<int,vector<int>> mkey;
        for(int i=0;i<M;++i)
        {
            cin>>K[i];
            mkey[K[i]].push_back(i);
        }

        vector<int> lastCnt(mkey[S[0]].size(),0);
        for(int a=1;a<N;++a)
        {
            vector<int> &lastIdx=mkey[S[a-1]];
            vector<int> &currIdx=mkey[S[a]];
            vector<int> currCnt(currIdx.size(),INT_MAX);
            pair<int,int> minp={INT_MAX,-1};
            for(int i=0,j=0;i<currIdx.size();++i)
            {
                while(j<lastIdx.size() && lastIdx[j]<currIdx[i])
                {
                    minp=min(minp,{lastCnt[j]-lastIdx[j],j});
                    j+=1;
                }
                int k=minp.second;
                if(k<0) continue;
                currCnt[i]=min(currCnt[i],lastCnt[k]+(currIdx[i]-lastIdx[k]));
            }
            minp={INT_MAX,-1};
            for(int i=currIdx.size()-1,j=lastIdx.size()-1;i>=0;--i)
            {
                while(j>=0 && currIdx[i]<lastIdx[j])
                {
                    minp=min(minp,{lastCnt[j]+lastIdx[j],j});
                    j-=1;
                }
                int k=minp.second;
                if(k<0) continue;
                currCnt[i]=min(currCnt[i],lastCnt[k]+(lastIdx[k]-currIdx[i]));
            }
            lastCnt=move(currCnt);
        }
        int ans=*min_element(lastCnt.begin(),lastCnt.end());
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
