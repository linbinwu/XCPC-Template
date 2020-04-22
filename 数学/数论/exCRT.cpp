ll mul(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % mod;
        a = (a << 1) % mod;
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

ll excrt(ll r[], ll m[], int N) {
    //模数m[i]不互质时用excrt
    ll M = m[1], res = r[1];
    for (int i = 2; i <= N; i++) {
        ll a = M, b = m[i], c = (r[i] - res % m[i] + m[i]) % m[i], x = 0, y = 0;
        ll g = exgcd(a, b, x, y);
        if (c % g != 0) return -1;//c不能整除g那就无正整数解
        x = mul(x, c / g, b / g);
        res += x * M;
        M *= b / g;
        res = (res % M + M) % M;
    }
    return (res % M + M) % M;
}