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

//r[]为余数, m为模数, 其中模数互质
//M = pi(mi), Mi = M / mi, invMi = Mi % mi
//ni满足是除了mi之外的倍数, 且模mi为ri
//利用逆元性质, 即ri * Mi * invMi = ri (mod mi)
//res = (sigma(ri * Mi * invMi)) % M

ll china(ll r[], ll m[], int n) {
    ll M = 1, res = 0;
    for (int i = 1; i <= n; i++) M *= m[i];
    for (int i = 1; i <= n; i++) {
        ll Mi = M / m[i], invMi = inv(Mi, m[i]);
        res = (res + r[i] * Mi % M * invMi % M) % M;
        //res = (res + mul(mul(r[i], Mi, M), invMi, M)) % M;按位乘
    }
    return (res % M + M) % M;
}