
const int N = 4e5 + 10;

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

const ll mod = 998244353;
const ll G = 3;
const ll invG = qpow(G, mod - 2, mod);
int tr[N];

void NTT(ll *A, int n, int type) {
    int len = 1; while (len < n) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        int mid = i / 2;
        ll Wn = qpow(type == 1 ? G : invG, (mod - 1) / i, mod);
        for (int k = 0; k < len; k += i) {
            ll w = 1;
            for (int l = k; l < k + mid; l++) {
                ll t = w * A[l + mid] % mod;
                A[l + mid] = (A[l] - t + mod) % mod;
                A[l] = (A[l] + t) % mod;
                w = w * Wn % mod;
            }
        }
    }
    if (type == -1) {
        ll invn = qpow(len, mod - 2, mod);
        for (int i = 0; i < len; i++)
            A[i] = A[i] * invn % mod;
    }
}

void getDer(ll *f, ll *g, int len) { for (int i = 1; i < len; i++) g[i - 1] = f[i] * i % mod; g[len - 1] = 0; }

void getInt(ll *f, ll *g, int len) { for (int i = 1; i < len; i++) g[i] = f[i - 1] * qpow(i, mod - 2, mod) % mod; g[0] = 0; }

void getInv(ll *f, ll *g, int n) {
    if (n == 1) { g[0] = qpow(f[0], mod - 2, mod); return; }
    getInv(f, g, n >> 1);
    static ll a[N], b[N];
    for (int i = 0; i < n; i++) a[i] = f[i], b[i] = g[i];
    int len = n << 1;
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++)
        a[i] = (2ll * b[i] % mod - a[i] * b[i] % mod * b[i] % mod + mod) % mod;
    NTT(a, len, -1);
    for (int i = 0; i < len; i++) g[i] = i < n ? a[i] : 0;
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;
}

void getLn(ll *f, ll *g, int n) {
    static ll a[N], b[N];
    getDer(f, a, n);
    getInv(f, b, n);
    int len = n << 1;
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1);
    getInt(a, g, len);
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;
}

void getExp(ll *f, ll *g, int n) {
    if (n == 1) { g[0] = 1; return; }
    getExp(f, g, n >> 1);
    static ll a[N];
    getLn(g, a, n);
    a[0] = (f[0] + 1 - a[0] + mod) % mod;
    for (int i = 1; i < n; i++) a[i] = (f[i] - a[i] + mod) % mod;
    int len = n << 1;
    NTT(a, len, 1), NTT(g, len, 1);
    for (int i = 0; i < len; i++) g[i] = g[i] * a[i] % mod;
    NTT(g, len, -1);
    for (int i = n; i < len; i++) g[i] = 0;
    for (int i = 0; i < len; i++) a[i] = 0;
}

ll f[N], g[N];

int main() {

    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &f[i]);

    int len = 1; while (len <= n) len <<= 1;
    getExp(f, g, len);
    for (int i = 0; i < n; i++)
        printf("%lld ", g[i]);

    return 0;
}