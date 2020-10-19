struct Trie {
    static const int MAX_N = N * 35;
    static const int MAX_BIT = 28;
    int rt[N];
    int ch[MAX_N][2], sum[MAX_N], tot;
    void insert(int now, int pre, ll val) {
        rt[now] = ++tot;
        now = rt[now], pre = rt[pre];
        for (int bit = MAX_BIT; bit >= 0; bit--) {
            int s = (val >> bit) & 1;
            sum[now] = sum[pre] + 1;
            if (!ch[now][s]) ch[now][s] = ++tot;
            ch[now][s ^ 1] = ch[pre][s ^ 1];
            now = ch[now][s];
            pre = ch[pre][s];
        }
        sum[now] = sum[pre] + 1;
    }
    ll queryKth(int now, int pre, ll val, int k = 1) {
        now = rt[now], pre = rt[pre];
        ll res = 0;
        for (int bit = MAX_BIT; bit >= 0; bit--) {
            int s = (val >> bit) & 1;
            int lsum = sum[ch[now][s ^ 1]] - sum[ch[pre][s ^ 1]];
            if (lsum >= k) res += (1 << bit), now = ch[now][s ^ 1], pre = ch[pre][s ^ 1];
            else k -= lsum, now = ch[now][s], pre = ch[pre][s];
        }
        return res;
    }
} trie;