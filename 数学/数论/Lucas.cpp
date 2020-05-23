//求解C(n, m) (mod p), 其中p为素数且较小
//O(p+logp)∼O(logn)

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll C(ll n, ll m, ll mod) {
    if (n < m) return 0;
    m = min(m, n - m);
    ll a = 1, b = 1;
    for (int i = 0; i < m; i++)
        a = a * (n - i) % mod, b = b * (i + 1) % mod;
    return a * qpow(b, mod - 2) % mod;
}

ll Lucas(ll n, ll m, ll mod) {
    if (m == 0) return 1;
    return Lucas(n / mod, m / mod, mod) * C(n % mod, m % mod, mod) % mod;
}
