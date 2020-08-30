const int N = 5e2 + 10;
const ll mod = 998244353;

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void mul(ll a[], ll b[], int n) {//a = a * b
    static ll res[N];
    for (int i = 0; i < n; i++) res[i] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[(i + j) % n] = (res[(i + j) % n] + 1ll * a[i] * b[j] % mod) % mod;
    memcpy(a, res, sizeof(res));
}

void qpow(ll a[], int n, ll k) {//a = a^k
    static ll res[N];
    for (int i = 0; i < n; i++) res[i] = (i == 0);
    while (k) {
        if (k & 1) mul(res, a, n);
        mul(a, a, n);
        k >>= 1;
    }
    memcpy(a, res, sizeof(res));
}

ll x[N], A[N], ans[N];

int main() {

    //x[i] = a * x[i - 1] + b * x[i] + c * x[i + 1]
    A[n - 1] = a, A[0] = b, A[1] = c;
    qpow(A, n, k);
    //X = A^{k} * X
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans[j] = (ans[j] + 1ll * A[(j - i + n) % n] * x[i] % mod) % mod;
    for (int i = 0; i < n; i++)
        printf("%lld%s", ans[i], i == n - 1 ? "\n" : " ");

    return 0;
}