ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll res = exgcd(b, a % b, x, y);
    ll t = y;
    y = x - a / b * y;
    x = t;
    return res;
}

ll inv(ll a, ll b) {
    ll x = 0, y = 0;
    exgcd(a, b, x, y);
    x = (x % b + b) % b;
}

struct HashTable {
    static const int MOD = 1e5 + 10;
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

ll BSGS(ll a, ll b, ll p) {//a ^ x = b (mod p)
    if (a % p == 0 && b) return -1;
    if (b == 1) return 0;
    ll m = sqrt(p) + 1, base = qpow(a, m, p);
    hs.clear();
    for (ll i = 0, t = b; i < m; i++, t = t * a % p) hs.insert(t, i);
    for (ll i = 1, t = base; i <= m + 1; i++, t = t * base % p) {
        ll j = hs.find(t);
        if (j != -1) return i * m - j;
    }
    return -1;
}

ll exBSGS(ll a, ll b, ll p) {
    if (b == 1 || p == 1) return 0;//b = 1 || (b = 0 && p = 1)的特殊情况
    //b % gcd(a, p) != 0 && b != 1时方程无解
    //   a ^ x = b (mod p)
    //=> a ^ (x - 1) * (a / G) = (b / G) (mod (p / G))
    //=> a ^ (x - 1) = (b / G * invg) (mod (p / G))
    //=> a ^ x' = b' (mod p')
    ll G = __gcd(a, p), k = 0, g = 1;
    while (G != 1) {
        if (b % G) return -1;
        k++, b /= G, p /= G, g = g * (a / G) % p;
        if (g == b) return k;//即a ^ x' = 1 (mod p')时, 返回k即可
        G = __gcd(a, p);
    }
    ll res = BSGS(a, b * inv(g, p) % p, p);
    return res == -1 ? -1 : res + k;
}