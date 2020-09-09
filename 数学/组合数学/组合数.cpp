ll C(ll n, ll m) {
    if (m == 0 || n == m) return 1;
    if (m > n) return 0;
    if (m == 1) return n;
    if (c[n][m]) return c[n][m];
    else return c[n][m] = C(n - 1, m) + C(n - 1, m - 1);
}


ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll fac[N], ifac[N];
void init(int siz) {
    fac[0] = 1;
    for (int i = 1; i <= siz; i++)
        fac[i] = i * fac[i - 1] % mod;
    ifac[siz] = qpow(fac[siz], mod - 2);
    for (int i = siz; i >= 1; i--) ifac[i - 1] = ifac[i] * i % mod;
}

ll C(ll n, ll m) {
    if (m == 0 || n == m) return 1;
    if (m > n) return 0;
    if (m == 1) return n;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
