#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N;

int Calc(vector<int> &vi)
{
    int ans=0;
    for(int i=0;i<N;)
    {
        if(vi[i]==0)
        {
            i+=1;
            continue;
        }
        for(i+=1;i<N && vi[i]!=0;++i);
        ans+=1;
    }
    return ans;
}

int main()
{
    int color[26];
    color['U'-'A']=0;// U = Uncolored
    color['R'-'A']=1;// R = Red
    color['Y'-'A']=2;// Y = Yellow
    color['B'-'A']=4;// B = Blue
    color['O'-'A']=3;// O = Orange
    color['P'-'A']=5;// P = Purple
    color['G'-'A']=6;// G = Green
    color['A'-'A']=7;// A = Gray
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        string P;
        cin>>N>>P;
        vector<int> vr(N,0),vy(N,0),vb(N,0);
        for(int i=0;i<N;++i)
        {
            int j=color[P[i]-'A'];
            vr[i]=j&1;
            vy[i]=j&2;
            vb[i]=j&4;
        }
        cout<<"Case #"<<icase<<": "<<Calc(vr)+Calc(vy)+Calc(vb)<<endl;
    }
    return 0;
}
