struct LinerBase {
    static const int MAX_BIT = 60;
    ll num[65];
    bool flag;//能否表示0
    LinerBase() { flag = 0; memset(num, 0, sizeof(num)); }
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
} linerBase;