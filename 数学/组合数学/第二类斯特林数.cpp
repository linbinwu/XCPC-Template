//S(n, m) = ifac[m] * \sum{k = 0}^{m} (-1)^k * C(m, k) * (m - k)^n

ll S(ll n, ll m) {
    ll res = 0;
    for (int k = 0, sign = 1; k <= m; k++, sign *= -1)
        res = (res + sign * C(m, k) * qpow(m - k, n) % mod) % mod;
    res = (res + mod) % mod;
    return res * ifac[m] % mod;
}