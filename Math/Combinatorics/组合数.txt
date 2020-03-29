ll C(ll n, ll m) {
    if (m == 0 || n == m) return 1;
    if (m > n) return 0;
    if (m == 1) return n;
    if (c[n][m]) return c[n][m];
    else return c[n][m] = C(n - 1, m) + C(n - 1, m - 1);
}


//预处理后O(N)得到
ll fac[MAX], inv[MAX];
void init() {
    fac[0] = 1;
    for (int i = 1; i <= (int)1e6; i++) {
        fac[i] = i * fac[i - 1] % mod;
        inv[i] = qpow(fac[i], mod - 2);
    }
}

ll C(ll n, ll m) {
    if (m == 0 || n == m) return 1;
    if (m > n) return 0;
    if (m == 1) return n;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
