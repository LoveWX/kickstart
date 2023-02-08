#include <bits/stdc++.h>
using namespace std;

int N;

vector<int> CalcCircle(vector<int> &vp)
{
    vector<int> ans;
    for(int i=1;i<=N;++i)
    {
        if(vp[i]<0) continue;
        int cnt=0;
        for(int j=i;vp[j]>=0;)
        {
            cnt+=1;
            int t=vp[j];
            vp[j]=-1;
            j=t;
        }
        ans.push_back(cnt);
    }
    return ans;
}

struct BitSet
{
    int np;
    vector<int> vp;
    vector<int> vsum;
    int cnt1;
    int nbit,nd;
    vector<unsigned long long> vd;
    vector<unsigned long long> vm;//mask
    vector<int> mpos;
    BitSet(vector<int> &vp)
    {
        nbit=1;
        nd=1;
        vd.push_back(1);
        vm.assign((N+1+63)/64,ULLONG_MAX);

        np=vp.size();
        vsum.assign(np+1,0);
        for(int i=0;i<np;++i)
        {
            vsum[i+1]=vsum[i]+vp[i];
        }
        cnt1=0;
        for(int i=np-1;i>=0 && vp[i]==1;--i,++cnt1);
        if(cnt1!=0) np=np-cnt1+1,cnt1-=1;
        this->vp=move(vp);
    }
    void MoveStep(int pb)
    {
        vector<unsigned long long> vt(nd+(pb+63)/64,0);
        if(pb%64==0)
        {
            for(int i=0,j=pb/64;i<nd;++i,++j)
            {
                vt[j]=vd[i]&vm[i];
            }
        }
        else
        {
            unsigned long long p0=pb%64,p1=64-p0;
            for(int i=0,j=pb/64;i<nd;++i,++j)
            {
                unsigned long long t=vd[i]&vm[i];
                vt[j]^=t<<p0;
                vt[j+1]^=t>>p1;
            }
            if((nbit+pb+63)/64<nd+(pb+63)/64) vt.pop_back();
        }
        for(int i=0;i<nd;++i)
        {
            vt[i]|=vd[i];
        }
        vd=move(vt);
        nbit+=pb;
        nd=vd.size();
    }
    void Calc(vector<int> &vi)
    {
        vector<int> vdiff(np,0);
        for(int i=1;i<np;++i)
        {
            vdiff[i]=vp[i-1]-vp[i];
        }
        for(int i=0;i<np;++i)
        {
            for(int j=vdiff[i];j!=0;--j)
            {
                for(int &p:mpos)
                {
                    vm[p/64]^=(1ULL<<(p%64));
                    p+=1;
                }
            }
            MoveStep(vp[i]);
            mpos.push_back(vsum[i]+1);
        }

        for(int i=0;i<nbit;++i)
        {
            vi[i]=(int)(vd[i/64]>>(i%64))&1;
        }
        for(int i=N-cnt1+1;i<=N;++i)
        {
            vi[i]=1;
        }
        np=vp.size();
        for(int i=0,lastSum=0;i<np;++i)
        {
            int currSum=lastSum+vp[i];
            for(int j=currSum;j>lastSum;--j)
            {
                vi[j]=i+1-vi[j];
            }
            lastSum=currSum;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N;
        vector<int> vi(N+1);
        for(int i=1;i<=N;++i)
        {
            cin>>vi[i];
        }
        vector<int> vp=CalcCircle(vi);
        sort(vp.begin(),vp.end(),greater<int>());
        BitSet bs(vp);
        bs.Calc(vi);
        cout<<"Case #"<<icase<<":";
        for(int i=1;i<=N;++i)
        {
            cout<<' '<<vi[i];
        }
        cout<<endl;
    }
    return 0;
}
