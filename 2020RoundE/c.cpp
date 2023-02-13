#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
using namespace std;

const int SIZE=100000;

int main()
{
    vector<array<int,3>> vtoy(SIZE);//{Ei+Ri, idx, Ei}
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        vtoy.resize(N);
        long long sumE=0LL;
        for(int i=0;i<N;++i)
        {
            cin>>vtoy[i][2]>>vtoy[i][0];
            vtoy[i][1]=i;
            vtoy[i][0]+=vtoy[i][2];
            sumE+=vtoy[i][2];
        }
        sort(vtoy.begin(),vtoy.end());
        int count=N;
        for(int i=N-1;i>=0 && sumE<vtoy[i][0];--i)
        {
            count-=1;
            sumE-=vtoy[i][2];
        }
        if(count>0)
        {
            cout<<"Case #"<<icase<<": "<<N-count<<" INDEFINITELY"<<endl;
            continue;
        }
        sort(vtoy.begin(),vtoy.end(),[](array<int,3> &a,array<int,3> &b){
            return a[1]<b[1];
        });
        sumE=0LL;
        for(array<int,3> &a:vtoy)
        {
            sumE+=a[2];
        }
        count=0;
        long long sum2=0LL;
        pair<long long,int> ans={sumE,0};
        priority_queue<array<int,3>> pq;
        for(int i=0;i<N;++i)
        {
            if(sumE>=vtoy[i][0])
            {
                sum2+=vtoy[i][2];
                pq.push(vtoy[i]);
            }
            else
            {
                sumE-=vtoy[i][2];
                count+=1;
                while(!pq.empty() && sumE<pq.top()[0])
                {
                    sumE-=pq.top()[2];
                    sum2-=pq.top()[2];
                    count+=1;
                    pq.pop();
                }
            }
            ans=max(ans,{sumE+sum2,-count});
        }
        cout<<"Case #"<<icase<<": "<<-ans.second<<' '<<ans.first<<endl;
    }
    return 0;
}
