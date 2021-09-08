class Solution {
public:
    vector<int> sa;
    vector<int> SuffixArray(vector<int> &vi)
    {
        int n=vi.size();
        vector<int> last=vi;
        for(int stp=1,len=1;len/2<n;++stp,len<<=1)
        {
            vector<array<int,3>> curr(n);
            for(int i=0;i<n;++i)
            {
                curr[i][0]=last[i];
                curr[i][1]=(i+len<n ? last[i+len] : -3);
                curr[i][2]=i;
            }
            sort(curr.begin(),curr.end());
            for(int i=0;i<n;++i)
            {
                last[curr[i][2]]=
                    (i>0 && curr[i-1][0]==curr[i][0] && curr[i-1][1]==curr[i][1] ?
                     last[curr[i-1][2]] : i);
            }
        }
        return last;
    }
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        vector<int> vp,vi;
        for(int i=0;i<paths.size();++i)
        {
            for(int j=0;j<paths[i].size();++j)
            {
                vp.push_back(paths[i][j]);
                vi.push_back(i);
            }
            vp.push_back(-1);
            vi.push_back(-1);
        }
        sa=SuffixArray(vi);
        
    }
};
