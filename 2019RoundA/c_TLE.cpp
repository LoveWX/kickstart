#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <climits>
#include <list>
#include <unordered_map>
using namespace std;

const int SIZE = 30000;

struct Node
{
    int left;
    int right;
    list<array<int, 2>>::iterator itl;
    list<array<int, 2>>::iterator itr;
};

int main()
{
    vector<Node> vq(SIZE);
    int ncase;
    cin >> ncase;
    for (int icase = 1; icase <= ncase; ++icase)
    {
        int N, Q;
        cin >> N >> Q;
        vq.resize(Q);
        for (int i = 0; i < Q; ++i)
        {
            cin >> vq[i].left >> vq[i].right;
            vq[i].right += 1;
        }
        sort(vq.begin(), vq.end(), [](Node &a, Node &b) {
            return a.right < b.right;
        });
        list<array<int, 2>> lq1;
        for (Node &q : vq)
        {
            lq1.push_back({ q.right,0 });
        }
        auto it = lq1.begin();
        for (int i = 0; i < Q; ++i, ++it)
        {
            vq[i].itr = it;
        }
        sort(vq.begin(), vq.end(), [](Node &a, Node &b) {
            return a.left < b.left;
        });
        list<array<int, 2>> lq0;
        for (Node &q : vq)
        {
            lq0.push_back({ q.left,0 });
        }
        it = lq0.begin();
        for (int i = 0; i < Q; ++i, ++it)
        {
            vq[i].itl = it;
        }
        for (int i = 0; i < Q; ++i)
        {
            (*vq[i].itl)[1] = i;
            (*vq[i].itr)[1] = i;
        }
        int ans = INT_MAX;
        for (int select = 0; select < Q; ++select)
        {
            int lasti = 0, idSum = 0, count = 0;
            unordered_map<int, int> mcount;
            auto it0 = lq0.begin(), it1 = lq1.begin();
            while (it0 != lq0.end() || it1 != lq1.end())
            {
                int curri;
                if (it0 == lq0.end()) curri = (*it1)[0];
                else if (it1 == lq1.end()) curri = (*it0)[0];
                else curri = min((*it0)[0], (*it1)[0]);
                if (count == 1)
                {
                    mcount[idSum] += curri - lasti;
                }
                for (; it0 != lq0.end() && (*it0)[0] == curri; ++it0)
                {
                    idSum += (*it0)[1];
                    count += 1;
                }
                for (; it1 != lq1.end() && (*it1)[0] == curri; ++it1)
                {
                    idSum -= (*it1)[1];
                    count -= 1;
                }
                lasti = curri;
            }
            if (mcount.empty())
            {
                ans = 0;
                break;
            }
            unordered_map<int, int>::iterator itmax = mcount.begin();
            for (auto it = next(mcount.begin()); it != mcount.end(); ++it)
            {
                if (it->second > itmax->second)
                {
                    itmax = it;
                }
            }
            ans = min(ans, itmax->second);
            lq0.erase(vq[itmax->first].itl);
            lq1.erase(vq[itmax->first].itr);
        }
        cout << "Case #" << icase << ": " << ans << endl;
    }
    return 0;
}
