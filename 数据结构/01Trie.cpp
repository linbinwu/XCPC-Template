struct Trie {
    static const int MAX_N = N * 35, rt = 0;
    static const int MAX_BIT = 31;
    int ch[MAX_N][2], sum[MAX_N], tot;
    void init() { tot = 0; ch[tot][0] = ch[tot][1] = sum[tot] = 0; }
    void insert(ll val) {
        int u = rt;
        for (int bit = MAX_BIT; bit >= 0; bit--) {
            int s = (val >> bit) & 1; sum[u]++;
            if (!ch[u][s]) {
                ch[u][s] = ++tot;
                ch[tot][0] = ch[tot][1] = sum[tot] = 0;
            }
            u = ch[u][s];
        }
        sum[u]++;
    }
    ll queryKth(ll val, int k = 1) {//第k大
        int u = rt; ll res = 0;
        for (int bit = MAX_BIT; bit >= 0; bit--) {
            int s = (val >> bit) & 1;
            if (!ch[u][s] && !ch[u][s ^ 1]) return res;
            if (!ch[u][s ^ 1]) u = ch[u][s];
            else if (sum[ch[u][s ^ 1]] >= k) u = ch[u][s ^ 1], res += (1ll << bit);
            else k -= sum[ch[u][s ^ 1]], u = ch[u][s];
        }
        return res;
    }
} trie;