//要求选取的三个模数mod1 * mod2 * mod3 >= p^2*n
//优点是精度高，可达10^26
//缺点是常数大(9次NTT)，并且还使用了龟速乘

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

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

int N, M;
ll a[3][MAX], b[3][MAX], ans[MAX], p;

int tr[MAX], n;
const ll mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, mod4 = mod1 * mod2;
const ll G = 3;

void NTT(ll *A, int type, ll mod) {
    for (int i = 0; i < n; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int len = 2; len <= n; len <<= 1) {
        int mid = len / 2;
        ll Wn = qpow(type == 1 ? G : qpow(G, mod - 2, mod), (mod - 1) / len, mod);
        for (int k = 0; k < n; k += len) {
            ll w = 1;
            for (int l = k; l < k + mid; l++) {
                ll t = w * A[l + mid] % mod;
                A[l + mid] = (A[l] - t + mod) % mod;
                A[l] = (A[l] + t) % mod;
                w = w * Wn % mod;
            }
        }
    }
    if (type != 1) {
        ll invn = qpow(n, mod - 2, mod);
        for (int i = 0; i < n; i++) A[i] = A[i] * invn % mod;
    }
}

void doNTT(int i, ll mod) {
    NTT(a[i], 1, mod), NTT(b[i], 1, mod);
    for (int j = 0; j < n; j++) a[i][j] = a[i][j] * b[i][j] % mod;
    NTT(a[i], -1, mod);
}

void CRT() {
    ll inv1 = qpow(mod2, mod1 - 2, mod1);
    ll inv2 = qpow(mod1, mod2 - 2, mod2);
    ll inv3 = qpow(mod4 % mod3, mod3 - 2, mod3);
    for (int i = 0; i < n; i++) {
        ll t = 0;
        t = (t + mul(a[0][i] * mod2 % mod4, inv1, mod4)) % mod4;
        t = (t + mul(a[1][i] * mod1 % mod4, inv2, mod4)) % mod4;
        a[1][i] = t;
        t = (a[2][i] - a[1][i] % mod3 + mod3) % mod3 * inv3 % mod3;
        ans[i] = (mod4 % p * t % p + a[1][i] % p) % p;
    }
}

int main() {

    scanf("%d%d%lld", &N, &M, &p);
    for (int i = 0; i <= N; i++) {
        ll x; scanf("%lld", &x);
        a[0][i] = a[1][i] = a[2][i] = x % p;
    }
    for (int i = 0; i <= M; i++) {
        ll x; scanf("%lld", &x);
        b[0][i] = b[1][i] = b[2][i] = x % p;
    }
    n = 1; while (n <= N + M) n <<= 1;
    for (int i = 0; i < n; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);

    doNTT(0, mod1), doNTT(1, mod2), doNTT(2, mod3);
    CRT();
    for (int i = 0; i <= N + M; i++) printf("%lld ", ans[i]);

    return 0;
}