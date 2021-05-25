
typedef long long ll;
const int N = 1e6 + 10;

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
const ll inv2 = qpow(2ll, mod - 2, mod);
int tr[N];

int getLen(int n) {
    int len = 1;
    while (len < (n << 1)) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    return len;
}

void NTT(ll *A, int len, int type) {
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

void getDer(ll *f, ll *g, int len) {
    for (int i = 1; i < len; i++) g[i - 1] = f[i] * i % mod;
    g[len - 1] = 0;
}

void getInt(ll *f, ll *g, int len) {
    for (int i = 1; i < len; i++) g[i] = f[i - 1] * qpow(i, mod - 2, mod) % mod;
    g[0] = 0;
}

void getInv(ll *f, ll *g, int n) {
    if (n == 1) return (void) (g[0] = qpow(f[0], mod - 2, mod));
    getInv(f, g, (n + 1) >> 1);
    int len = getLen(n);
    static ll a[N];
    for (int i = 0; i < len; ++i) a[i] = i < n ? f[i] : 0;
    NTT(a, len, 1), NTT(g, len, 1);
    for (int i = 0; i < len; i++)
        g[i] = 1LL * (2 - 1LL * a[i] * g[i] % mod + mod) % mod * g[i] % mod;
    NTT(g, len, -1);
    for (int i = n; i < len; i++) g[i] = 0;
}

void getLn(ll *f, ll *g, int n) {
    static ll a[N], b[N];
    getDer(f, a, n);
    getInv(f, b, n);
    int len = getLen(n);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1);
    getInt(a, g, len);
    for (int i = n; i < len; i++) g[i] = 0;
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;
}

void getExp(ll *f, ll *g, int n) {
    if (n == 1) return (void) (g[0] = 1);
    getExp(f, g, (n + 1) >> 1);
    static ll a[N];
    getLn(g, a, n);
    a[0] = (f[0] + 1 - a[0] + mod) % mod;
    for (int i = 1; i < n; i++) a[i] = (f[i] - a[i] + mod) % mod;
    int len = getLen(n);
    NTT(a, len, 1), NTT(g, len, 1);
    for (int i = 0; i < len; i++) g[i] = g[i] * a[i] % mod;
    NTT(g, len, -1);
    for (int i = n; i < len; i++) g[i] = 0;
    for (int i = 0; i < len; i++) a[i] = 0;
}

void getPow(ll *f, ll *g, int n, ll k) {
    static ll a[N];
    getLn(f, a, n);
    for (int i = 0; i < n; i++) a[i] = a[i] * k % mod;
    getExp(a, g, n);
    for (int i = 0, len = getLen(n); i < len; i++) a[i] = 0;
}

void getPower(ll *f, ll *g, int n, ll k1, ll k2) {//k1为原始模数, k2为模phi(mod - 1)
    int pos = 0;
    while (pos < n && !f[pos]) pos++;
    if (k1 * pos >= n) {
        for (int i = 0; i < n; i++) g[i] = 0;
        return;
    }
    static ll a[N], b[N];
    int m = n - pos, inv = qpow(f[pos], mod - 2, mod), t = qpow(f[pos], k2, mod);
    for (int i = 0; i < m; i++) a[i] = f[i + pos] * inv % mod;
    getLn(a, b, m);
    for (int i = 0; i < m; i++) b[i] = b[i] * k1 % mod;
    getExp(b, g, m);
    for (int i = 0; i < m; i++) g[i] = g[i] * t % mod;
    pos = min(1ll * pos * k1, 1ll * n);
    for (int i = n - 1; i >= pos; i--) g[i] = g[i - pos];
    for (int i = pos - 1; i >= 0; i--) g[i] = 0;
    for (int i = 0, len = getLen(m); i < len; i++) a[i] = b[i] = 0;
}

void fenzhiFFT(ll *f, ll *g, int n) {
    //计算g[i] = \sum_{j = 1}^{i} g[i - j] * f[j]
    static ll a[N];
    for (int i = 1; i < n; i++) a[i] = (mod - f[i]) % mod;
    a[0] = 1;
    ll g0 = g[0];
    getInv(a, g, n);
    for (int i = 0; i < n; i++) g[i] = g[i] * g0 % mod, a[i] = 0;
}

struct Complex {
    ll x, y;
};
ll w;

Complex mul(Complex a, Complex b, ll mod) {
    Complex ans = {0, 0};
    ans.x = ((a.x * b.x % mod + a.y * b.y % mod * w % mod) % mod + mod) % mod;
    ans.y = ((a.x * b.y % mod + a.y * b.x % mod) % mod + mod) % mod;
    return ans;
}

ll binpow_imag(Complex a, ll b, ll mod) {
    Complex ans = {1, 0};
    while (b) {
        if (b & 1) ans = mul(ans, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return ans.x % mod;
}

ll cipolla(ll n, ll mod) {
    srand(time(0));
    n %= mod;
    if (mod == 2) return n;
    if (qpow(n, (mod - 1) / 2, mod) == mod - 1) return -1;
    ll a;
    while (1) {
        a = rand() % mod;
        w = ((a * a % mod - n) % mod + mod) % mod;
        if (qpow(w, (mod - 1) / 2, mod) == mod - 1) break;
    }
    Complex x = {a, 1};
    return binpow_imag(x, (mod + 1) / 2, mod);
}

void getSqrt(ll *f, ll *g, int n) {
    if (n == 1) {
        if (f[0] == 0) g[0] = f[0];
        else {
            ll t = cipolla(f[0], mod);
            g[0] = min(t, mod - t);
        }
        return;
    }
    getSqrt(f, g, (n + 1) >> 1);
    int len = getLen(n);
    static ll a[N], b[N];
    for (int i = 0; i < len; ++i) a[i] = i < n ? f[i] : 0;
    getInv(g, b, n);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = 1ll * a[i] * b[i] % mod;
    NTT(a, len, -1);
    for (int i = 0; i < n; i++) g[i] = (g[i] + a[i]) % mod * inv2 % mod;
    for (int i = n; i < len; i++) g[i] = 0;
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;
}

//分治乘法
void solve(ll *f1, ll *f2, ll *g, int l, int r) {
    if (l == r) return (void) (g[(l - 1) * 2] = f1[l], g[(l - 1) * 2 + 1] = f2[l]);
    int mid = (l + r) / 2;
    solve(f1, f2, g, l, mid);
    solve(f1, f2, g, mid + 1, r);
    static ll a[N], b[N];
    int len1 = mid - l + 2, len2 = r - mid + 1;
    for (int i = 0; i < len1; i++) a[i] = g[(l - 1) * 2 + i];
    for (int i = 0; i < len2; i++) b[i] = g[mid * 2 + i];
    int n = r - l + 2, len = getLen(n);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1);
    for (int i = 0; i < n; i++) g[(l - 1) * 2 + i] = a[i];
    for (int i = n; i < len; i++) g[(l - 1) * 2 + i] = 0;
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;

}