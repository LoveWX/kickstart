#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <climits>
using namespace std;

int N;

int Calc(vector<array<int,2>> &vp)
{
    priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pql;
    priority_queue<int,vector<int>,greater<int>> pq0;
    int cntl=N,cntr=0;
    for(array<int,2> &a:vp)
    {
        pql.push(a);
    }
    pql.push({INT_MAX,-1});
    pq0.push(INT_MAX);
    int mini;
    long long minSum=LLONG_MAX;
    int last=pql.top()[0];
    long long lastSum=0LL;
    for(array<int,2> &a:vp)
    {
        lastSum+=a[0]-last;
    }
    for(;cntr<N;)
    {
        int curr=min(pql.top()[0],pq0.top());
        long long currSum=lastSum-(long long)(curr-last)*cntl+(long long)(curr-last)*cntr;
        if(currSum<minSum)
        {
            minSum=currSum;
            mini=curr;
        }
        while(curr==pq0.top())
        {
            cntr+=1;
            pq0.pop();
        }
        while(curr==pql.top()[0])
        {
            pq0.push(pql.top()[1]);
            pql.pop();
            cntl-=1;
        }
        last=curr;
        lastSum=currSum;
    }
    return mini;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N;
        vector<array<int,2>> px(N),py(N);
        for(int i=0;i<N;++i)
        {
            cin>>px[i][0]>>py[i][0]>>px[i][1]>>py[i][1];
        }
        cout<<"Case #"<<icase<<": "<<Calc(px)<<' '<<Calc(py)<<endl;
    }
    return 0;
}
