#include <iostream>
#include <string>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N,D,C,M;
        string line;
        cin>>N>>D>>C>>M>>line;
        while(!line.empty() && line.back()=='C')
        {
            line.pop_back();
        }
        bool feed=true;
        for(char c:line)
        {
            if(c=='C')
            {
                if(C==0)
                {
                    feed=false;
                    break;
                }
                C-=1;
            }
            else
            {
                if(D==0)
                {
                    feed=false;
                    break;
                }
                D-=1;
                C+=M;
            }
        }
        cout<<"Case #"<<icase<<": "<<(feed ? "YES" : "NO")<<endl;
    }
    return 0;
}
