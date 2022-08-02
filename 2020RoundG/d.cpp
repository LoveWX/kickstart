#include <iostream>
#include <iomanip>
using namespace std;

const int SIZE=5000;
double m[SIZE][SIZE];

void Init()
{
    m[0][0]=0.0;
    for(int i=1;i<SIZE;++i)
    {
        m[i][0]=1.0/i+m[i-1][0];
        m[i][i]=1.0/i+m[i-1][i-1];
        for(int j=1;j<i;++j)
        {
            m[i][j]=2.0/i+(double)j/i*m[i-1][j-1]+(double)(i-j)/i*m[i-1][j];
        }
    }
}

int main()
{
    Init();
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        cin>>N;
        double *p=m[N-1];
        double ans=0.0;
        for(int j=0;j<N;++j)
        {
            int a;
            cin>>a;
            ans+=a*p[j];
        }
        cout<<"Case #"<<icase<<": "<<setiosflags(ios::fixed)<<setprecision(8)<<ans<<endl;
    }
    return 0;
}
