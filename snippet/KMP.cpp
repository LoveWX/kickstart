//KMP算法在源字符串中查找第一个匹配的模式串
//主要思想:当模式串在源串中失配时,不需要从模式串第一个字符重新尝试匹配,
//而是利用PMT从模式串中间开始重启匹配过程,继续尝试匹配模式串右侧,模式串左侧由于PMT的性质已经匹配
//部分匹配表(PMT, Partial Match Table),部分匹配值记录了:模式串左起某个前缀子字符串的,最长相等真前后缀的长度
//PMT记录了模式串每种长度前缀的 最长相等真前后缀的长度 ,也可用于求解字符串的最长相等前后缀
//以"ABCDABD"为例:
//"A"的前缀和后缀都为空集，共有元素的长度为0；
//"AB"的前缀为[A]，后缀为[B]，共有元素的长度为0；
//"ABC"的前缀为[A, AB]，后缀为[BC, C]，共有元素的长度0；
//"ABCD"的前缀为[A, AB, ABC]，后缀为[BCD, CD, D]，共有元素的长度为0；
//"ABCDA"的前缀为[A, AB, ABC, ABCD]，后缀为[BCDA, CDA, DA, A]，共有元素为"A"，长度为1；
//"ABCDAB"的前缀为[A, AB, ABC, ABCD, ABCDA]，后缀为[BCDAB, CDAB, DAB, AB, B]，共有元素为"AB"，长度为2；
//"ABCDABD"的前缀为[A, AB, ABC, ABCD, ABCDA, ABCDAB]，后缀为[BCDABD, CDABD, DABD, ABD, BD, D]，共有元素的长度为0
//如果在模式串第i位失配,则[0,i-1]是匹配源串的,通过PMT可以查到第i位前的一小段子串能和模式串匹配的最大长度,接下来就不用从模式串第1位继续尝试匹配了
//     src:......ABC D
// pattern:ABCF..ABC E
//例如:模式串字符D和源串字符E失配,这时D之前的一小段ABC已经匹配了模式串,通过PMT得知ABC也匹配模式串前缀,所以下次继续从模式串字符F匹配源串字符D
//注意实际使用的next数组相当于PMT右移一位,因为是失配时才用到PMT,而模式串失配的前一位才是匹配的。
//1.计算PMT,partial_matched_table,用模式串匹配模式串.next数组第0位填-1. 2.用模式串和PMT匹配源串
//KMP算法的时间复杂度O(m+n)

class Solution {
public:
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
    int strStr(string src, string pat) {
        if(pat.empty()) return 0;
        vector<int> next(pat.size());
        CalcPMT(pat,next);
        return KMP(src,pat,next);
    }
};
