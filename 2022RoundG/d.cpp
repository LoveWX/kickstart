#include <bits/stdc++.h>
using namespace std;

const long long NINF=LLONG_MIN/2;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        long long E;
        cin>>N>>E;
        map<int,vector<array<int,2>>> mp;
        for(;N>0;--N)
        {
            int x,y,c;
            cin>>x>>y>>c;
            mp[-y].push_back({x,c});
        }
        vector<int> lastx(1,0);
        vector<long long> lastle(1,-E);
        vector<long long> lastri(1,0);
        for(auto &[_,currp]:mp)
        {
            sort(currp.begin(),currp.end());
            int nlast=lastx.size();
            int ncurr=currp.size();
            long long sum=accumulate(currp.begin(),currp.end(),0LL,[](long long a,const array<int,2> &b){
                return a+b[1];
            });
            long long lastLeMax=*max_element(lastle.begin(),lastle.end());
            long long lastRiMax=*max_element(lastri.begin(),lastri.end());
            vector<long long> currle(ncurr,max(lastLeMax-2LL*E,lastRiMax-3LL*E));
            vector<long long> currri(ncurr,max(lastRiMax-2LL*E,lastLeMax-3LL*E));

            {
                long long currsum=0;
                long long max0=NINF,max1=NINF;
                for(int i=0,j=0;j<ncurr;)//从左向右计算
                {
                    int x=currp[j][0];
                    if(i<nlast) x=min(x,lastx[i]);
                    if(i<nlast && lastx[i]==x)
                    {
                        max0=max(max0,lastri[i]-currsum);
                        max1=max(max1,lastle[i]);
                        i+=1;
                    }
                    if(currp[j][0]==x)
                    {
                        currsum+=currp[j][1];
                        currri[j]=max(currri[j],max0+currsum);//0次转向,入方向和出方向相同
                        currle[j]=max(currle[j],max0+sum-E);//1次转向,入点在左,出点在右
                        currri[j]=max(currri[j],max1+currsum-E);//1次转向,入点在右,出点在左
                        j+=1;
                    }
                }
            }
            {
                long long currsum=0;
                long long max0=NINF,max1=NINF;
                for(int i=nlast-1,j=ncurr-1;j>=0;)//从右向左计算
                {
                    int x=currp[j][0];
                    if(i>=0) x=max(x,lastx[i]);
                    if(i>=0 && lastx[i]==x)
                    {
                        max0=max(max0,lastle[i]-currsum);
                        max1=max(max1,lastri[i]);
                        i-=1;
                    }
                    if(currp[j][0]==x)
                    {
                        currsum+=currp[j][1];
                        currle[j]=max(currle[j],max0+currsum);//0次转向,入方向和出方向相同
                        currri[j]=max(currri[j],max0+sum-E);//1次转向,入点在右,出点在左
                        currle[j]=max(currle[j],max1+currsum-E);//1次转向,入点在左,出点在右
                        j-=1;
                    }
                }
            }

            vector<int> nextx;
            nextx.reserve(nlast+ncurr);
            vector<long long> nextle,nextri;
            nextle.reserve(nlast+ncurr);
            nextri.reserve(nlast+ncurr);
            int i=0,j=0;
            for(;i<nlast && j<ncurr;)
            {
                if(lastx[i]<currp[j][0])
                {
                    nextx.push_back(lastx[i]);
                    nextle.push_back(lastle[i]);
                    nextri.push_back(lastri[i]);
                    i+=1;
                }
                else if(lastx[i]>currp[j][0])
                {
                    nextx.push_back(currp[j][0]);
                    nextle.push_back(currle[j]);
                    nextri.push_back(currri[j]);
                    j+=1;
                }
                else
                {
                    nextx.push_back(lastx[i]);
                    nextle.push_back(max(lastle[i],currle[j]));
                    nextri.push_back(max(lastri[i],currri[j]));
                    i+=1;
                    j+=1;
                }
            }
            for(;i<nlast;++i)
            {
                nextx.push_back(lastx[i]);
                nextle.push_back(lastle[i]);
                nextri.push_back(lastri[i]);
            }
            for(;j<ncurr;++j)
            {
                nextx.push_back(currp[j][0]);
                nextle.push_back(currle[j]);
                nextri.push_back(currri[j]);
            }
            lastx=move(nextx);
            lastle=move(nextle);
            lastri=move(nextri);
        }
        long long ans=max(*max_element(lastle.begin(),lastle.end()),*max_element(lastri.begin(),lastri.end()));
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
