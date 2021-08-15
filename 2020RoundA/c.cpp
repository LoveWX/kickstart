#include <iostream>
using namespace std;

const int SIZE=1000;
int mm[SIZE][SIZE];
int le[SIZE][SIZE],ri[SIZE][SIZE],up[SIZE][SIZE],dn[SIZE][SIZE];
int R,C;

inline int Calc(int c0,int c1) //c0:longer edge, c1:shorter edge
{
    return (c1<2 || c0<4) ? 0 : min(c1-1,c0/2-1);
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,K;
        cin>>R>>C;
        for(int i=0;i<R;++i)
        {
            for(int j=0;j<C;++j)
            {
                cin>>mm[i][j];
            }
        }
        for(int i=0;i<R;++i)
        {
            le[i][0]=mm[i][0];
            for(int j=1;j<C;++j)
            {
                le[i][j]=(mm[i][j]==0 ? 0 : le[i][j-1]+1);
            }
            ri[i][C-1]=mm[i][C-1];
            for(int j=C-2;j>=0;--j)
            {
                ri[i][j]=(mm[i][j]==0 ? 0 : ri[i][j+1]+1);
            }
        }
        for(int j=0;j<C;++j)
        {
            up[0][j]=mm[0][j];
            for(int i=1;i<R;++i)
            {
                up[i][j]=(mm[i][j]==0 ? 0 : up[i-1][j]+1);
            }
            dn[R-1][j]=mm[R-1][j];
            for(int i=R-2;i>=0;--i)
            {
                dn[i][j]=(mm[i][j]==0 ? 0 : dn[i+1][j]+1);
            }
        }
        int ans=0;
        for(int i=0;i<R;++i)
        {
            for(int j=0;j<C;++j)
            {
                ans+=Calc(up[i][j],le[i][j])+Calc(up[i][j],ri[i][j]);
                ans+=Calc(dn[i][j],le[i][j])+Calc(dn[i][j],ri[i][j]);
                ans+=Calc(le[i][j],up[i][j])+Calc(le[i][j],dn[i][j]);
                ans+=Calc(ri[i][j],up[i][j])+Calc(ri[i][j],dn[i][j]);
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
