const double PI = acos(-1);

ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

struct Complex {
    double x, y;
    Complex(double a = 0, double b = 0): x(a), y(b) {}
    Complex operator + (const Complex &rhs) { return Complex(x + rhs.x, y + rhs.y); }
    Complex operator - (const Complex &rhs) { return Complex(x - rhs.x, y - rhs.y); }
    Complex operator * (const Complex &rhs) { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    Complex conj() { return Complex(x, -y); }
} w[N];

ll mod;
int tr[N];

int getLen(int n) {
    int len = 1; while (len < (n << 1)) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (int i = 0; i < len; i++) w[i] = w[i] = Complex(cos(2 * PI * i / len), sin(2 * PI * i / len));
    return len;
}

void FFT(Complex *A, int len) {
    for (int i = 0; i < len; i++) if(i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2, lyc = len >> 1; i <= len; i <<= 1, lyc >>= 1)
        for (int j = 0; j < len; j += i) {
            Complex *l = A + j, *r = A + j + (i >> 1), *p = w;
            for (int k = 0; k < i >> 1; k++) {
                Complex tmp = *r * *p;
                *r = *l - tmp, *l = *l + tmp;
                ++l, ++r, p += lyc;
            }
        }
}

inline void MTT(ll *x, ll *y, ll *z, int len) {

    for (int i = 0; i < len; i++) (x[i] += mod) %= mod, (y[i] += mod) %= mod;
    static Complex a[N], b[N];
    static Complex dfta[N], dftb[N], dftc[N], dftd[N];

    for (int i = 0; i < len; i++) a[i] = Complex(x[i] & 32767, x[i] >> 15);
    for (int i = 0; i < len; i++) b[i] = Complex(y[i] & 32767, y[i] >> 15);
    FFT(a, len), FFT(b, len);
    for (int i = 0; i < len; i++) {
        int j = (len - i) & (len - 1);
        static Complex da, db, dc, dd;
        da = (a[i] + a[j].conj()) * Complex(0.5, 0);
        db = (a[i] - a[j].conj()) * Complex(0, -0.5);
        dc = (b[i] + b[j].conj()) * Complex(0.5, 0);
        dd = (b[i] - b[j].conj()) * Complex(0, -0.5);
        dfta[j] = da * dc;
        dftb[j] = da * dd;
        dftc[j] = db * dc;
        dftd[j] = db * dd;
    }
    for (int i = 0; i < len; i++) a[i] = dfta[i] + dftb[i] * Complex(0, 1);
    for (int i = 0; i < len; i++) b[i] = dftc[i] + dftd[i] * Complex(0, 1);
    FFT(a, len), FFT(b, len);
    for (int i = 0; i < len; i++) {
        ll da = (ll)(a[i].x / len + 0.5) % mod;
        ll db = (ll)(a[i].y / len + 0.5) % mod;
        ll dc = (ll)(b[i].x / len + 0.5) % mod;
        ll dd = (ll)(b[i].y / len + 0.5) % mod;
        z[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
    }
}

void getInv(ll *f, ll *g, int n) {
    if (n == 1) { g[0] = qpow(f[0], mod - 2, mod); return; }
    getInv(f, g, (n + 1) >> 1);
    int len = getLen(n);
    static ll c[N];
    for (int i = 0; i < len; ++i) c[i] = i < n ? f[i] : 0;
    MTT(c, g, c, len), MTT(c, g, c, len);
    for (int i = 0; i < n; i++) g[i] = (2ll * g[i] - c[i] + mod) % mod;
    for (int i = n; i < len; ++i) g[i] = 0;
    for (int i = 0; i < len; i++) c[i] = 0;
}

void getDer(ll *f, ll *g, int len) { for (int i = 1; i < len; i++) g[i - 1] = f[i] * i % mod; g[len - 1] = 0; }

void getInt(ll *f, ll *g, int len) { for (int i = 1; i < len; i++) g[i] = f[i - 1] * qpow(i, mod - 2, mod) % mod; g[0] = 0; }

void getLn(ll *f, ll *g, int n) {
    static ll a[N], b[N];
    getDer(f, a, n);
    getInv(f, b, n);
    int len = getLen(n);
    MTT(a, b, a, len);
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
    MTT(a, g, g, len);
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

void fenzhiFFT(ll *f, ll *g, int n) {
    //¼ÆËãg[i] = \sum_{j = 1}^{i} g[i - j] * f[j]
    static ll a[N];
    for (int i = 1; i < n; i++) a[i] = (mod - f[i]) % mod;
    a[0] = 1;
    ll g0 = g[0];
    getInv(a, g, n);
    for (int i = 0; i < n; i++) g[i] = g[i] * g0 % mod, a[i] = 0;
}