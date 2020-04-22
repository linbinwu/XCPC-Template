ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll getPhi(ll x) {
    ll res = 1;
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0) {
            x = x / i;
            res *= i - 1;
            while (x % i == 0) x = x / i, res *= i;
        }
    if (x > 1) res *= x - 1;
    return res;
}

ll exEuler(char *sa, char *sb, ll p) {//欧拉降幂求a ^ b % p
    //gcd(a, p) = 1        => a ^ b = a ^ (b % phi(p))
    //gcd(a, p) ≠ 1, b < p => a ^ b = a ^ b
    //gcd(a, p) ≠ 1, b ≥ p => a ^ b = a ^ (b % phi(p) + phi(p))
    int N = strlen(sa), M = strlen(sb), flag = 0;
    ll phi = getPhi(p), a = 0, b = 0;
    for (int i = 0; i < N; i++) a = (a * 10 + sa[i] - '0') % p;
    for (int i = 0; i < M; i++) {
        b = b * 10 + sb[i] - '0';
        if (b >= phi) flag = 1;
        b %= phi;
    }
    if (flag) b += phi;
    return qpow(a, b, p);
}