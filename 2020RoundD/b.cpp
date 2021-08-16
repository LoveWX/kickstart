#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int SIZE=10000;
int A[SIZE];

int Cmp(int a,int b)
{
    if(a>b) return 1;
    else if(a<b) return -1;
    return 0;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        for(int i=0;i<N;++i)
        {
            cin>>A[i];
        }
        vector<int> last(4,0);
        for(int i=1;i<N;++i)
        {
            vector<int> curr(4,N+1);
            int d0=Cmp(A[i-1],A[i]);
            for(int a=0;a<4;++a)
            {
                for(int b=0;b<4;++b)
                {
                    curr[b]=min(curr[b],last[a]+(d0==Cmp(a,b) ? 0 : 1));
                }
            }
            last=move(curr);
        }
        cout<<"Case #"<<icase<<": "<<min(min(last[0],last[1]),min(last[2],last[3]))<<endl;
    }
    return 0;
}
