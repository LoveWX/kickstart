#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        string str;
        cin>>N>>str;
        vector<int> vi;
        vi.reserve(str.size());
        for(int i=0;i<str.size();++i)
        {
            if(str[i]=='1')
            {
                vi.push_back(i);
            }
        }
        long long ans=(long long)(1+vi[0])*vi[0]/2+(long long)(1+N-1-vi.back())*(N-vi.back()-1)/2;
        for(int i=1;i<vi.size();++i)
        {
            int len=vi[i]-vi[i-1]-1;
            if(len%2==0)
            {
                ans+=(long long)(1+len/2)*(len/2)/2*2;
            }
            else
            {
                ans+=(long long)(1+len/2)*(len/2)/2*2+(len+1)/2;
            }
        }
        cout<<"Case #"<<icase<<": "<<ans<<endl;
    }
    return 0;
}
