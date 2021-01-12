#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <utility>
#include <map>
using namespace std;

const int SIZE=300;
int n;
// for each substring, list all the beginning and end index pair of each existence
vector<vector<pair<int,int>>> mStr;
// store position of each substring in mStr
// for substring s[x,y], mStr[mpStr[x][y]][mpStr[y][x]]==(x,y)
int mpStr[SIZE][SIZE];
// partial ans of prefix substring
int mem1[SIZE];
// partial ans of prefix substring whose last operation is paste specific length of substring
int mem2[SIZE][SIZE];

int dp2(int left,int idx);

int dp1(int idx)
{
    if(mem1[idx]!=-1) return mem1[idx];
    int &ans=mem1[idx];
    ans=dp1(idx-1)+1;
    for(int i=idx-1;i>0;--i)
    {
        ans=min(ans,dp2(i,idx));
    }
    return ans;
}

int dp2(int left,int idx)
{
    if(mem2[left][idx]!=-1) return mem2[left][idx];
    int &ans=mem2[left][idx];
    ans=0x1FFFFFFF;
    if(mpStr[left][idx]==-1) return ans;
    vector<pair<int,int>> &vp=mStr[mpStr[left][idx]];
    for(int i=mpStr[idx][left]-1;i>=0;--i)
    {
        if(vp[i].second>=left) continue;
        if(vp[0].second<vp[i].first)
        {
            ans=min(ans,dp2(vp[i].first,vp[i].second)+(left-vp[i].second-1)+1);
        }
        else
        {
            ans=min(ans,dp1(left-1)+2);
        }
    }
    return ans;
}

int main()
{
    mStr.reserve(SIZE/2*(SIZE/2-1)/2);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        string s;
        cin>>s;
        memset(mpStr,-1,sizeof(mpStr));
        n=s.size();
        for(int k=n/2;k>1;--k)
        {
            map<string,vector<pair<int,int>>> m;
            for(int i=0,j=k-1;j<n;++i,++j)
            {
                m[s.substr(i,k)].emplace_back(pair<int,int>(i,j));
            }
            for(auto it=m.begin();it!=m.end();++it)
            {
                if(it->second.size()<=1) continue;
                vector<pair<int,int>> &vp=it->second;
                for(int i=0;i<vp.size();++i)
                {
                    mpStr[vp[i].first][vp[i].second]=mStr.size();
                    mpStr[vp[i].second][vp[i].first]=i;
                }
                mStr.emplace_back(move(vp));
            }
        }
        memset(mem1,-1,sizeof(mem1));
        mem1[0]=1;
        memset(mem2,-1,sizeof(mem2));
        cout<<"Case #"<<icase<<": "<<dp1(n-1)<<endl;
        mStr.resize(0);
    }
    return 0;
}
