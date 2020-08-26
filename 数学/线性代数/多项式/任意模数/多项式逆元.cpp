//四倍空间

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


int tr[N];

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

inline void MTT(int *x, int *y, int *z, int len) {

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


int a[N], b[N], c[N];

void inv(int *a, int *b, int deg) {
    if (deg == 1) { b[0] = qpow(a[0], mod - 2, mod); return; }
    inv(a, b, (deg + 1) >> 1);
    int len = 1; while (len < (deg << 1)) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (int i = 0; i < len; i++) w[i] = w[i] = Complex(cos(2 * PI * i / len), sin(2 * PI * i / len));
    for (int i = 0; i < len; ++i) c[i] = i < deg ? a[i] : 0;
    MTT(c, b, c, len), MTT(c, b, c, len);
    for (int i = 0; i < len; i++) b[i] = (2ll * b[i] - c[i] + mod) % mod;
    for (int i = deg; i < len; ++i) b[i] = 0;
}


int main() {

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    inv(a, b, n);
    for (int i = 0; i < n; i++) printf("%d ", (b[i] + mod) % mod);

    return 0;
}