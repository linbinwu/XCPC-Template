ll phi(ll x) {
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