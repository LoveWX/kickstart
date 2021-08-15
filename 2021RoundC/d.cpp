#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

string E;
vector<int> vp;
using Var = vector<int>;
using Term = pair<vector<pair<int, int>>, Var>;
using Exp = vector<Term>;
using HashExp = pair<Exp, Exp>;
map<HashExp, int> mHash;
const Exp Num0 = {make_pair(vector<pair<int, int>>(), Var({0}))};
const Exp Num1 = {make_pair(vector<pair<int, int>>(), Var({1}))};

Var MakeVariable(int left, int right)
{
    Var v;
    v.reserve(right - left + 1);
    for (int i = right; i >= left; --i)
    {
        v.push_back(E[i] - '0');
    }
    return v;
}

Var operator +(Var &a, Var &b)
{
    Var ans;
    ans.reserve(max(a.size(), b.size()) + 1);
    int i = 0, carry = 0;
    for (; i < a.size() && i < b.size(); ++i)
    {
        carry += a[i] + b[i];
        ans.push_back(carry % 10);
        carry /= 10;
    }
    for (; i < a.size(); ++i)
    {
        carry += a[i];
        ans.push_back(carry % 10);
        carry /= 10;
    }
    for (; i < b.size(); ++i)
    {
        carry += b[i];
        ans.push_back(carry % 10);
        carry /= 10;
    }
    if (carry != 0) ans.push_back(carry);
    return ans;
}

Var operator *(Var &a, Var &b)
{
    Var ans(a.size() + b.size(), 0);
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < b.size(); ++j)
        {
            ans[i + j] += a[i] * b[j];
        }
    }
    int carry = 0;
    for (int i = 0; i < ans.size(); ++i)
    {
        carry += ans[i];
        ans[i] = carry % 10;
        carry /= 10;
    }
    if (ans.back() == 0) ans.pop_back();
    return ans;
}

inline bool IsSameTerm(const Term &a, const Term &b)
{
    return a.first == b.first;
}

Term operator +(Term &a, Term &b)
{
    return make_pair(a.first, a.second + b.second);
}

Term operator *(Term &a, Term &b)
{
    vector<pair<int, int>> tvp;
    int i = 0, j = 0;
    while (i < a.first.size() && j < b.first.size())
    {
        if (a.first[i].first < b.first[j].first)
        {
            tvp.push_back(a.first[i++]);
        }
        else if (a.first[i].first > b.first[j].first)
        {
            tvp.push_back(b.first[j++]);
        }
        else
        {
            tvp.push_back(a.first[i++]);
            tvp.back().second += b.first[j++].second;
        }
    }
    for(; i < a.first.size(); ++i)
    {
        tvp.push_back(a.first[i]);
    }
    for(; j < b.first.size(); ++j)
    {
        tvp.push_back(b.first[j]);
    }
    return make_pair(tvp, a.second * b.second);
}

Exp operator +(Exp &a, Exp &b)
{
    Exp ans;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size())
    {
        if (IsSameTerm(a[i], b[j]))
        {
            ans.push_back(a[i++] + b[j++]);
            continue;
        }
        if (a[i] < b[j])
        {
            ans.push_back(move(a[i++]));
        }
        else
        {
            ans.push_back(move(b[j++]));
        }
    }
    for(; i < a.size(); ++i)
    {
        ans.push_back(move(a[i]));
    }
    for(; j < b.size(); ++j)
    {
        ans.push_back(move(b[j]));
    }
    return ans;
}

Exp operator *(Exp &a, Exp &b)
{
    Exp tans;
    tans.reserve(a.size() * b.size());
    for (Term &ta : a)
    {
        for (Term &tb : b)
        {
            tans.push_back(ta * tb);
        }
    }
    sort(tans.begin(), tans.end());
    Exp ans;
    ans.push_back(move(tans[0]));
    for (int i = 1; i < tans.size(); ++i)
    {
        if (IsSameTerm(ans.back(), tans[i]))
        {
            ans.back().second = ans.back().second + tans[i].second;
        }
        else
        {
            ans.push_back(move(tans[i]));
        }
    }
    return ans;
}

Exp Calc(int left, int right)
{
    if (E[left] != '(')
    {
        return {make_pair(vector<pair<int, int>>(), MakeVariable(left, right))};
    }
    int mid;
    if (E[left + 1] == '(') mid = vp[left + 1] + 1;
    else for (mid = left + 1; isdigit(E[mid]); ++mid);
    Exp expL = move(Calc(left + 1, mid - 1));
    Exp expR = move(Calc(mid + 1, right - 1));
    Exp ans;
    if (E[mid] == '+')
    {
        if (expL == Num0)
        {
            ans = move(expR);
        }
        else if (expR == Num0)
        {
            ans = move(expL);
        }
        else
        {
            ans = move(expL + expR);
        }
    }
    else if (E[mid] == '*')
    {
        if (expL == Num0 || expR == Num1)
        {
            ans = move(expL);
        }
        else if (expR == Num0 || expL == Num1)
        {
            ans = move(expR);
        }
        else
        {
            ans = move(expL * expR);
        }
    }
    else // E[mid]=='#'
    {
        HashExp hashExp = make_pair(move(expL), move(expR));
        auto it = mHash.find(hashExp);
        if (it != mHash.end())
        {
            ans = {make_pair(vector<pair<int, int>>({make_pair(it->second, 1)}), Var({1}))};
        }
        else
        {
            int idx = mHash.size();
            mHash[move(hashExp)] = idx;
            ans = {make_pair(vector<pair<int, int>>({make_pair(idx, 1)}), Var({1}))};
        }
    }
    return ans;
}

int main()
{
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        cout << "Case #" << icase << ':';
        int N, ei = 1;
        map<Exp, int> m;
        for (cin >> N; N > 0; --N)
        {
            cin >> E;
            vp.assign(E.size(), -1);
            vector<int> stk;
            for (int i = 0; i < E.size(); ++i)
            {
                if (E[i] == '(')
                {
                    stk.push_back(i);
                }
                else if (E[i] == ')')
                {
                    vp[stk.back()] = i;
                    vp[i] = stk.back();
                    stk.pop_back();
                }
            }

            Exp exp = move(Calc(0, E.size() - 1));
            auto it = m.find(exp);
            if (it != m.end())
            {
                cout << ' ' << it->second;
            }
            else
            {
                cout << ' ' << ei;
                m[move(exp)] = ei++;
            }
        }
        cout << endl;
        mHash.clear();
    }
    return 0;
}
