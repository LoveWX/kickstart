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
        cin>>N>>M;
        vector<int> A(N);
        for(int &i:A)
        {
            cin>>i;
        }
        sort(A.begin(),A.end());
        int k=N-(M-1);
        double sum=accumulate(A.begin()+k,A.end(),0);
        if(k%2==0)
        {
            sum+=(A[k/2]+A[k/2-1])*0.5;
        }
        else
        {
            sum+=A[k/2];
        }
        cout<<"Case #"<<icase<<": "<<setiosflags(ios::fixed)<<setprecision(2)<<sum<<endl;
    }
    return 0;
}
