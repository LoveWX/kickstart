#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int SIZE=10000000;
const double euler=0.5772156649;
double e[SIZE];
long long N;

void Init()
{
    e[0]=0.0;
    e[1]=1.0;
    for(int i=2;i<SIZE;++i)
    {
        e[i]=e[i-1]+1.0/i;
    }
}

int main()
{
    Init();
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>N;
        double ans=(N>=SIZE ? log(N)+euler+0.5/N : e[N]);
        cout<<"Case #"<<icase<<": "<<setiosflags(ios::fixed)<<setprecision(8)<<ans<<endl;
    }
    return 0;
}
