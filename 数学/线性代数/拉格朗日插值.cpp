//拉格朗日插值, 求点值转化为的多项式f(x)
//得到f(k) = \sum_{i = 1} ^ {n} y[i] \pi_{i != j} \frac{k - x[j]}{x[i] - x[j]}

int lagrange(int n, int *x, int *y, int k) {
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll s1 = 1, s2 = 1;
        for (int j = 0; j < n; j++)
            if (i != j) {
                s1 = s1 * (k - x[j] + mod) % mod;
                s2 = s2 * (x[i] - x[j] + mod) % mod;
            }
        res = (res + 1ll * y[i] * s1 % mod * inv(s2) % mod) % mod;
    }
    return (res + mod) % mod;
}