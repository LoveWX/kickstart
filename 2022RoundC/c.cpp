#include <bits/stdc++.h>
using namespace std;

struct Ant
{
    int P;
    int D;
    int idx;
    long long dis;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,L;
        cin>>N>>L;
        vector<Ant> va(N);
        for(int i=0;i<N;++i)
        {
            cin>>va[i].P>>va[i].D;
            va[i].idx=i+1;
        }
        sort(va.begin(),va.end(),[](Ant &a,Ant &b){
            return a.P<b.P;
        });

        vector<int> vle,vri;//向左和向右的集合
        for(int i=0;i<N;++i)
        {
            if(va[i].D==0) vle.push_back(i);
            else vri.push_back(i);
        }
        
        for(int i=0;i<N;++i)
        {
            int lcnt=lower_bound(vri.begin(),vri.end(),i)-vri.begin();//左边的个数
            int rcnt=vle.end()-upper_bound(vle.begin(),vle.end(),i);//右边的个数
            int cnt=min(lcnt,rcnt);
            long long ldis=0,rdis=0;
            if(va[i].D==0)
            {
                if(lcnt<=rcnt)
                {
                    if(lcnt!=0)
                    {
                        int il=vri[lcnt-cnt];
                        ldis=va[i].P-va[il].P;
                        int ir=vle[vle.size()-rcnt+cnt-1];
                        rdis=va[ir].P-va[i].P;
                    }
                    va[i].dis=ldis+rdis+(rdis-ldis)+2*va[i].P;
                }
                else//lcnt>rcnt
                {
                    if(rcnt==0)
                    {
                        int il=vri[lcnt-1];
                        ldis=va[i].P-va[il].P;
                    }
                    else//rcnt!=0
                    {
                        int il=vri[lcnt-cnt-1];
                        ldis=va[i].P-va[il].P;
                        int ir=vle[vle.size()-rcnt+cnt-1];
                        rdis=va[ir].P-va[i].P;
                    }
                    va[i].dis=ldis+rdis+2*L-(rdis-ldis+2*va[i].P);
                }
            }
            else//va[i].D==1
            {
                if(lcnt>=rcnt)
                {
                    if(rcnt!=0)
                    {
                        int il=vri[lcnt-cnt];
                        ldis=va[i].P-va[il].P;
                        int ir=vle[vle.size()-rcnt+cnt-1];
                        rdis=va[ir].P-va[i].P;
                    }
                    va[i].dis=ldis+rdis+2*L-(rdis-ldis+2*va[i].P);
                }
                else//lcnt<rcnt
                {
                    if(lcnt==0)
                    {
                        int ir=vle[vle.size()-rcnt];
                        rdis=va[ir].P-va[i].P;
                    }
                    else//lcnt!=0
                    {
                        int il=vri[lcnt-cnt];
                        ldis=va[i].P-va[il].P;
                        int ir=vle[vle.size()-rcnt+cnt];
                        rdis=va[ir].P-va[i].P;
                    }
                    va[i].dis=ldis+rdis+(rdis-ldis)+2*va[i].P;
                }
            }
        }
        sort(va.begin(),va.end(),[](Ant &a,Ant &b){
            return a.dis==b.dis ? a.idx<b.idx : a.dis<b.dis;
        });
        cout<<"Case #"<<icase<<':';
        for(Ant &a:va)
        {
            cout<<' '<<a.idx;
        }
        cout<<endl;
    }
    return 0;
}
