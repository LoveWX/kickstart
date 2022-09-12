#include <bits/stdc++.h>
using namespace std;

void CalcPMT(string &pat,vector<int> &next)
{
    int n=pat.size();
    next[0]=-1;
    int i=0,j=-1;
    while(i<n-1)
    {
        if(j==-1 || pat[i]==pat[j])
        {
            i+=1;
            j+=1;
            next[i]=j;
        }
        else
        {
            j=next[j];
        }
    }
}

int KMP(string &src,string &pat,vector<int> &next)
{
    int ns=src.size(),np=pat.size();
    int i=0,j=0;
    while(i<ns && j<np)
    {
        if(j==-1 || src[i]==pat[j])
        {
            i+=1;
            j+=1;
        }
        else
        {
            j=next[j];
        }
    }
    if(j==np) return i-j;
    return -1;
}

int main()
{
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        int N;
        string s;
        cin>>N>>s;
        string ss=s.substr(1)+s;
        vector<int> next(N);
        CalcPMT(s,next);
        int idx=KMP(ss,s,next)+1;
        cout<<"Case #"<<icase<<": "<<s.substr(0,idx)<<endl;
    }
    return 0;
}
