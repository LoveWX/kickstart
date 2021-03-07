#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

const int SIZE=100;
array<string,SIZE> grid;
vector<string> dict;
int R,C,W;
int m[SIZE][SIZE];
int rowVal[SIZE][SIZE][SIZE];
int colVal[SIZE][SIZE][SIZE];
long long aa,bb;
int cc;

long long gcd(long long a,long long b)
{
    while(b!=0)
    {
        long long t=a%b;
        a=b;
        b=t;
    }
    return a;
}

void CalcMaxValue(long long ta,long long tb)
{
    if(aa*tb==ta*bb)
    {
        cc+=1;
    }
    else if(aa*tb<ta*bb)
    {
        aa=ta;
        bb=tb;
        cc=1;
    }
}

void FindWord(string &src,vector<pair<int,int>> &vans)
{
    int n=src.size();
    for(string &pat:dict)
    {
        for(int i=0;i<n;)
        {
            i=src.find(pat,i);
            if(i==string::npos) break;
            vans.push_back({i+pat.size()-1,i});
            ++i;
        }
    }
}

void CalcMatchedRow(int r)
{
    vector<pair<int,int>> wordPos;
    FindWord(grid[r],wordPos);
    sort(wordPos.begin(),wordPos.end());
    for(int i=0;i<C;++i)
    {
        int total=0;
        for(int j=i;j<C;++j)
        {
            auto it=lower_bound(wordPos.begin(),wordPos.end(),pair<int,int>({j,i}));
            for(;it!=wordPos.end() && it->first==j;++it)
            {
                total+=j-it->second+1;
            }
            rowVal[r][i][j]=total;
        }
    }
}

void CalcMatchedCol(int c)
{
    string s(R,'a');
    for(int i=0;i<R;++i)
    {
        s[i]=grid[i][c];
    }
    vector<pair<int,int>> wordPos;
    FindWord(s,wordPos);
    sort(wordPos.begin(),wordPos.end());
    for(int i=0;i<R;++i)
    {
        int total=0;
        for(int j=i;j<R;++j)
        {
            auto it=lower_bound(wordPos.begin(),wordPos.end(),pair<int,int>({j,i}));
            for(;it!=wordPos.end() && it->first==j;++it)
            {
                total+=j-it->second+1;
            }
            colVal[c][i][j]=total;
        }
    }
}

int main()
{
    dict.reserve(2000);
    int ncase;
    cin>>ncase;
    for(int icase=1;icase<=ncase;++icase)
    {
        cin>>R>>C>>W;
        for(int i=0;i<R;++i)
        {
            cin>>grid[i];
        }
        string ts;
        for(int i=0;i<W;++i)
        {
            cin>>ts;
            dict.emplace_back(ts);
            reverse(ts.begin(),ts.end());
            dict.emplace_back(move(ts));
        }

        for(int i=0;i<R;++i)
        {
            CalcMatchedRow(i);
        }
        for(int j=0;j<C;++j)
        {
            CalcMatchedCol(j);
        }

        aa=0LL;
        bb=1LL;
        cc=0;
        for(int x0=0;x0<R;++x0)
        {
            for(int y0=0;y0<C;++y0)
            {
                int total=0;
                for(int y1=y0;y1<C;++y1)
                {
                    total+=colVal[y1][x0][x0];
                    m[x0][y1]=rowVal[x0][y0][y1]+total;
                    CalcMaxValue(m[x0][y1],y1-y0+1+1);
                }
                total=rowVal[x0][y0][y0];
                for(int x1=x0+1;x1<R;++x1)
                {
                    total+=rowVal[x1][y0][y0];
                    m[x1][y0]=total+colVal[y0][x0][x1];
                    CalcMaxValue(m[x1][y0],x1-x0+1+1);
                }
                for(int x1=x0+1;x1<R;++x1)
                {
                    for(int y1=y0+1;y1<C;++y1)
                    {
                        long long ta=(m[x1][y1]=m[x1-1][y1]+
                            m[x1][y1-1]-m[x1-1][y1-1]+
                            rowVal[x1][y0][y1]-rowVal[x1][y0][y1-1]+
                            colVal[y1][x0][x1]-colVal[y1][x0][x1-1]);
                        CalcMaxValue(ta,(x1-x0+1)+(y1-y0+1));
                    }
                }
            }
        }
        long long d=gcd(aa,bb);
        aa/=d;
        bb/=d;
        cout<<"Case #"<<icase<<": "<<aa<<'/'<<bb<<' '<<cc<<endl;
        dict.resize(0);
    }
    return 0;
}
