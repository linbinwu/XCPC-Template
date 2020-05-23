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
    return x = (x % b + b) % b;
}

ll f(ll n, ll p, ll pk) {
    if (n == 0) return 1;
    ll s = 1;
    for (ll i = 1; i <= pk; i++)
        if (i % p) s = s * i % pk;
    s = qpow(s, n / pk, pk);
    for (ll i = pk * (n / pk); i <= n; i++)
        if (i % p) s = i % pk * s % pk;
    return f(n / p, p, pk) * s % pk;
}

ll g(ll n, ll p) {
    if (n < p) return 0;
    return g(n / p, p) + (n / p);
}

ll c(ll n, ll m, ll p, ll pk) {
    ll frac1 = f(n, p, pk), frac2 = inv(f(m, p, pk) * f(n - m, p, pk) % pk, pk);
    ll s = qpow(p, g(n, p) - g(m, p) - g(n - m, p), pk);
    return frac1 * frac2 % pk * s % pk;
}

ll calc(ll r, ll m, ll M) {
    //CRT, M = p质因数分解后再全部相乘仍然是p
    ll Mi = M / m, invMi = inv(Mi, m);
    return r * Mi % M * invMi % M;
}

ll exLucas(ll n, ll m, ll p) {//O(plogp), 不要求p是质数
    ll t = p, res = 0;
    for (ll i = 2; i * i <= p; i++)
        if (t % i == 0) {//i为当前的质数
            ll pk = 1;//p^k
            while (t % i == 0) {
                t /= i, pk *= i;
            }
            res = (res + calc(c(n, m, i, pk), pk, p)) % p;
        }
    if (t > 1)
        res = (res + calc(c(n, m, t, t), t, p)) % p;
    return res;
}