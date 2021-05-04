#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

const int SIZE = 100000;
int N, S;
int A[SIZE];
int score[SIZE];

struct SegmentTreeMax
{
    int n;
    vector<int> maxv, tags;
    int inf;
    SegmentTreeMax(int size)
    {
        n = size;
        maxv.assign(n << 2, 0);
        tags.assign(n << 2, 0);
    }
    SegmentTreeMax(vector<int> &v)
    {
        n = v.size();
        maxv.assign(n << 2, 0);
        tags.assign(n << 2, 0);
        for (int i = 0; i < n; ++i)
        {
            Modify(i, i, v[i]);
        }
    }
    void Modify(int c, int l, int r, int L, int R, int diff)
    {
        if (L <= l && r <= R)
        {
            maxv[c] += diff;
            tags[c] += diff;
            return;
        }
        int mid = (l + r) >> 1;
        if (L <= mid)
        {
            Modify((c << 1) + 1, l, mid, L, R, diff);
        }
        if (R > mid)
        {
            Modify((c << 1) + 2, mid + 1, r, L, R, diff);
        }
        maxv[c] = max(maxv[(c << 1) + 1], maxv[(c << 1) + 2]) + tags[c];
    }
    int Query(int c, int l, int r, int L, int R)
    {
        if (L <= l && r <= R)
        {
            return maxv[c];
        }
        int mid = (l + r) >> 1;
        int ans = INT_MIN;
        if (L <= mid)
        {
            ans = max(ans, Query((c << 1) + 1, l, mid, L, R));
        }
        if (R > mid)
        {
            ans = max(ans, Query((c << 1) + 2, mid + 1, r, L, R));
        }
        return ans + tags[c];
    }
    void Modify(int L, int R, int diff)
    {
        Modify(0, 0, n - 1, L, R, diff);
    }
    int Query(int L, int R)
    {
        return Query(0, 0, n - 1, L, R);
    }
};

int main()
{
	int ncase;
	cin >> ncase;
	for (int icase = 1; icase <= ncase; ++icase)
	{
        cin >> N >> S;
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < N; ++i)
        {
            cin >> A[i];
            vector<int> &vi = m[A[i]];
            if (vi.size() < S) score[i] = +1;
            else if (vi.size() == S) score[i] = -S;
            else score[i] = 0;
            vi.push_back(i);
        }
        for (auto it = m.begin(); it != m.end(); ++it)
        {
            reverse(it->second.begin(), it->second.end());
        }
        SegmentTreeMax seg(N);
        int sum = 0;
        for (int i = 0; i < N; ++i)
        {
            sum += score[i];
            seg.Modify(i, i, sum);
        }
        int ans = 0;
        for (int i = 0; i < N; ++i)
        {
            ans = max(ans, seg.Query(i, N - 1));
            vector<int> &vi = m[A[i]];
            seg.Modify(i, N - 1, -1);
            if (vi.size() >= 1 + S) seg.Modify(vi[vi.size() - 1 - S], N - 1, S + 1);
            if (vi.size() >= 2 + S) seg.Modify(vi[vi.size() - 2 - S], N - 1, -S);
            vi.pop_back();
        }
        cout << "Case #" << icase << ": " << ans << endl;
	}
	return 0;
}
