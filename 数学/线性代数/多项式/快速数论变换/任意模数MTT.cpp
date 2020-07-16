//将多项式拆成(a1 * mod + a2) * (b1 * mod + b2)的形式
//=>a1 * b1 * mod ^ 2 + (a2 * b1 + a1 * b2) * mod + a2 * b2
//在利用DFT合并、IDFT合并，最终只需要4次DFT即可
//精度10^14


const double PI = acos(-1);

struct Complex {
    double x, y;
    Complex(double a = 0, double b = 0): x(a), y(b) {}
    Complex operator + (const Complex &rhs) { return Complex(x + rhs.x, y + rhs.y); }
    Complex operator - (const Complex &rhs) { return Complex(x - rhs.x, y - rhs.y); }
    Complex operator * (const Complex &rhs) { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
    Complex conj() { return Complex(x, -y); }
} w[MAX];

int N, M;
ll mod;
int n, tr[MAX];
int a[MAX], b[MAX], ans[MAX];

void FFT(Complex *A) {
    for (int i = 0; i < n; i++) if(i < tr[i]) swap(A[i], A[tr[i]]);
    for (int len = 2, lyc = n >> 1; len <= n; len <<= 1, lyc >>= 1)
        for (int j = 0; j < n; j += len) {
            Complex *l = A + j, *r = A + j + (len >> 1), *p = w;
            for (int k = 0; k < len >> 1; k++) {
                Complex tmp = *r * *p;
                *r = *l - tmp, *l = *l + tmp;
                ++l, ++r, p += lyc;
            }
        }
}

void FFT_prepare() {
    n = 1; while (n <= N + M) n <<= 1;
    for (int i = 0; i < n; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
    for (int i = 0; i < n; i++) w[i] = w[i] = Complex(cos(2 * PI * i / n), sin(2 * PI * i / n));
}

inline void conv(int *x, int *y, int *z) {
    for (int i = 0; i < n; i++) (x[i] += mod) %= mod, (y[i] += mod) %= mod;
    static Complex a[MAX], b[MAX];
    static Complex dfta[MAX], dftb[MAX], dftc[MAX], dftd[MAX];

    for (int i = 0; i < n; i++) a[i] = Complex(x[i] & 32767, x[i] >> 15);
    for (int i = 0; i < n; i++) b[i] = Complex(y[i] & 32767, y[i] >> 15);
    FFT(a), FFT(b);
    for (int i = 0; i < n; i++) {
        int j = (n - i) & (n - 1);
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
    for (int i = 0; i < n; i++) a[i] = dfta[i] + dftb[i] * Complex(0, 1);
    for (int i = 0; i < n; i++) b[i] = dftc[i] + dftd[i] * Complex(0, 1);
    FFT(a), FFT(b);
    for (int i = 0; i < n; i++) {
        int da = (ll)(a[i].x / n + 0.5) % mod;
        int db = (ll)(a[i].y / n + 0.5) % mod;
        int dc = (ll)(b[i].x / n + 0.5) % mod;
        int dd = (ll)(b[i].y / n + 0.5) % mod;
        z[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
    }
}



int main() {
    scanf("%d%d%lld", &N, &M, &mod);
    for (int i = 0; i <= N; i++) scanf("%d", &a[i]);
    for (int i = 0; i <= M; i++) scanf("%d", &b[i]);
    FFT_prepare();
    conv(a, b, ans);
    for (int i = 0; i <= N + M; i++)
        printf("%s%d", i == 0 ? "" : " ", (ans[i] + mod) % mod);

    return 0;
}