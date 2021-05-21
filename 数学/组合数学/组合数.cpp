ll C(ll n, ll m) {
    if (m == 0 || n == m) return 1;
    if (m > n) return 0;
    if (m == 1) return n;
    if (c[n][m]) return c[n][m];
    else return c[n][m] = C(n - 1, m) + C(n - 1, m - 1);
}


//预处理版本, 模数为质数
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

// 模数非质数
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int prime[10], g[N][10], num;
ll fac[N], ifac[N];
void init(int siz, int mod) {
    num = 0;
    fac[0] = ifac[0] = 1;
    ll tmp = mod;
    for (int i = 2; i * i <= mod; i++)
        if (tmp % i == 0) {
            prime[++num] = i;
            while (tmp % i == 0) tmp /= i;
        }
    if (tmp > 1) prime[++num] = tmp;
    ll phi = mod;
    for (int i = 1; i <= num; i++) phi = phi / prime[i] * (prime[i] - 1);
    for (int i = 1; i <= siz; i++) {
        ll x = i;
        for (int j = 1; j <= num; j++) {
            g[i][j] = g[i - 1][j]; // 前i个数prime[j]的幂次和
            while (x % prime[j] == 0) x /= prime[j], g[i][j]++;
        }
        fac[i] = fac[i - 1] * x % mod;
        ifac[i] = qpow(fac[i], phi - 1, mod); // gcd(fac[i], mod) = 1
    }
}

ll C(ll n, ll m, ll mod) {
    if (m == 0 || n == m) return 1;
    if (m > n) return 0;
    if (m == 1) return n % mod;
    ll res = fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    for (int i = 1; i <= num; i++)
        res = res * qpow(prime[i], g[n][i] - g[m][i] - g[n - m][i], mod) % mod;
    return res;
}