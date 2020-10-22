struct LinerBase {
    static const int MAX_BIT = 60;
    ll num[65], tmp[65];
    bool flag;//能否表示0
    LinerBase() {
        flag = 0;
        memset(num, 0, sizeof(num));
        memset(tmp, 0, sizeof(tmp));
    }
    void insert(ll x) {
        for (int bit = MAX_BIT; ~bit; bit--)
            if (x & (1ll << bit)) {
                if (num[bit]) x ^= num[bit];
                else {
                    num[bit] = x;
                    return;
                }
            }
        flag = 1;
    }
    ll queryMax() {
        ll res = 0;
        for (int bit = MAX_BIT; ~bit; bit--) res = max(res, res ^ num[bit]);
        return res;
    }
    ll queryMin() {
        if (flag) return 0;
        for (int bit = 0; bit <= MAX_BIT; bit++)
            if (num[bit]) return num[bit];
    }
    ll queryKth(ll k) {
        ll res = 0, cnt = 0;
        k -= flag; if (!k) return 0;
        for (int i = 0; i < MAX_BIT; i++) {
            for (int j = i - 1; ~j; j--)
                if (num[i] & (1ll << j)) num[i] ^= num[j];
            if (num[i]) tmp[cnt++] = num[i];
        }
        if (k >= (1ll << cnt)) return -1;
        for (int i = 0; i < cnt; i++)
            if (k & (1ll << i)) res ^= tmp[i];
        return res;
    }
} linerBase;

struct LinerBase {
    //区间查询
    //构造的时候, lb[i] = lb[i - 1], lb[i].insert(x, i)
    //ans = lb[qr].queryMax(ql)
    static const int MAX_BIT = 30;
    int num[32], pos[32];
    LinerBase() {
        memset(num, 0, sizeof(num));
        memset(pos, 0, sizeof(pos));
    }
    void insert(int x, int p) {
        for (int bit = MAX_BIT; ~bit; bit--)
            if (x & (1ll << bit)) {
                if (!num[bit]) {
                    num[bit] = x, pos[bit] = p;
                    return;
                }
                else if (p > pos[bit]) {
                    swap(num[bit], x);
                    swap(pos[bit], p);
                }
                x ^= num[bit];
            }
    }
    int queryMax(int ql) {
        int res = 0;
        for (int bit = MAX_BIT; ~bit; bit--)
            if (pos[bit] >= ql)
                res = max(res, res ^ num[bit]);
        return res;
    }
} lb[N];

LinerBase merge(const LinerBase &a, const LinerBase &b) {
    LinerBase res;
    for (int bit = res.MAX_BIT; ~bit; bit--) res.num[bit] = a.num[bit];
    for (int bit = res.MAX_BIT; ~bit; bit--) if (b.num[bit]) res.insert(b.num[bit]);
    return res;
}