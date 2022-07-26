#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

int N,M,K;
vector<int> target;
map<vector<int>,double> mem;

double dp(vector<int> &curr)
{
    if(auto it=mem.find(curr);it!=mem.end()) return it->second;
    int valid=0;
    double ans=0.0;//x=1+(M-V)/M*x+1/M*(E1+E2+...+EV)
    for(int i=0;i<M;)
    {
        int j=i+1;
        for(;j<M && curr[j]==curr[i];++j);
        j-=1;
        if(curr[j]+1<=target[j])
        {
            curr[j]+=1;
            ans+=dp(curr)*(j-i+1);
            valid+=(j-i+1);
            curr[j]-=1;
        }
        i=j+1;
    }
    ans=(ans+M)/valid;
    mem[curr]=ans;
    return ans;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N>>M>>K;
        target.assign(M,0);
        for(int i=M-K;i<M;++i)
        {
            cin>>target[i];
        }
        mem[target]=0.0;
        vector<int> curr(M,0);
        double ans=dp(curr);
        cout<<"Case #"<<icase<<": "<<setiosflags(ios::fixed)<<setprecision(8)<<ans<<endl;
        mem.clear();
    }
    return 0;
}
