ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll fac[N];
void init(int siz) {
    fac[0] = 1;
    for (int i = 1; i <= siz; i++) fac[i] = i * fac[i - 1] % mod;
}

ll C(ll n, ll m) {
    if (n < m) return 0;
    return fac[n] * qpow(fac[m], mod - 2) % mod * qpow(fac[n - m], mod - 2) % mod;
}

ll Lucas(ll n, ll m) {
    if (m == 0) return 1;
    return Lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}