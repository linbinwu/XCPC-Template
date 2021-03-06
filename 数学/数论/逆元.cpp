//存在逆元的充要条件为gcd(a, mod) = 1
//小心那种mod = 2^k, 然后求inv(2^i), 这种只能迭代求(可能为0)
//mod为质数, 费马小定理求解
#define inv(x,y) qpow(x,y-2,y)

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

//mod不是质数, exgcd求解
//exgcd(a, b x, y) -> b=mod, x为逆元
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

ll inv(ll a, ll b = mod) {
    ll x = 0, y = 0;
    exgcd(a, b, x, y);
    return x = (x % b + b) % b;
}
