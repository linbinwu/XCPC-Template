
struct HashTable {
    static const int MOD = 1e7 + 10;//此处sqrt(p)即可
    struct edge {
        int nxt;
        ll num, val;
    } e[MOD];
    int head[MOD], tot;
    void clear() { tot = 0; memset(head, 0, sizeof(head)); }
    void insert(ll u, ll w) { e[++tot] = edge{head[u % MOD], u, w }, head[u % MOD] = tot; }
    int find(ll u) {
        for (int i = head[u % MOD]; i; i = e[i].nxt)
            if (e[i].num == u) return e[i].val;
        return -1;
    }
} hs;

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll BSGS(ll a, ll b, ll p) {//a ^ x = b (mod p)
    //令x = i * m - j
    //a ^ {i * m} = b * a ^ j (mod p)  ,  j ∈ [0, m - 1]
    b %= p;
    if (a % p == 0 && b) return -1;
    if (b == 1) return 0;
    ll m = sqrt(p) + 1, base = qpow(a, m, p);
    hs.clear();
    //insert t = b * a ^ j to HashTable
    for (ll i = 0, t = b; i < m; i++, t = t * a % p) hs.insert(t, i);
    //t = a ^ {i * m}
    for (ll i = 1, t = base; i <= m + 1; i++, t = t * base % p) {
        ll j = hs.find(t);
        if (j != -1) return i * m - j;
    }
    return -1;
}