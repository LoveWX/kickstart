#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE=1000;
int mat[SIZE][SIZE];

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        vector<long long> vsum(N*2-1,0LL);
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                int t;
                cin>>t;
                vsum[i-j+N-1]+=t;
            }
        }
        cout<<"Case #"<<icase<<": "<<*max_element(vsum.begin(),vsum.end())<<endl;
    }
    return 0;
}
