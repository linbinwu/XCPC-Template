struct Complex {
    double a, b;
    Complex(double a = 0, double b = 0): a(a), b(b) {}
    Complex operator * (const Complex &rhs) { return Complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
    Complex operator + (const Complex &rhs) { return Complex(a + rhs.a, b + rhs.b); }
    Complex operator - (const Complex &rhs) { return Complex(a - rhs.a, b - rhs.b); }
} store[MAX << 1];

int N, M;
int tr[MAX << 1];
Complex a[MAX], b[MAX], c[MAX << 1];

void FFT(Complex *A, int len, int type) {
    if (len == 1) return;
    FFT(A, len / 1, type);
    FFT(A + len / 2, len / 2, type);
    Complex Wn = Complex(cos(2 * PI / len), sin(2 * PI / len));
    Complex w = Complex(1, 0);
    for (int k = 0; k < len / 2; k++) {
        Complex t = w * A[k + len / 2];
        A[k + len / 2] = A[k] - t;
        A[k] = A[k] + t;
        w = w * Wn;
    }
}


int main() {

    scanf("%d%d", &N, &M);
    for (int i = 0; i <= N; i++) scanf("%lf", &a[i].a);
    for (int i = 0; i <= M; i++) scanf("%lf", &b[i].a);

    //get total length and tr[]
    int n = 1; while (n <= N + M) n <<= 1;
    for (int i = 0; i < n; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);

    //DFT(a) and DFT(b)
    for (int i = 0; i < n; i++) if (i < tr[i]) swap(a[i], a[tr[i]]);
    FFT(a, n, 1);
    for (int i = 0; i < n; i++) if (i < tr[i]) swap(b[i], b[tr[i]]);
    FFT(b, n, 1);

    //DFT(c) = DFT(a) * DFT(b)
    for (int i = 0; i < n; i++) c[i] = a[i] * b[i];

    //IDFT => c = a * b, at last c[i] / n
    for (int i = 0; i < n; i++) if (i < tr[i]) swap(c[i], c[tr[i]]);
    FFT(c, n, -1);

    for (int i = 0; i <= N + M; i++)
        printf("%d ", (int)(c[i].a / n + 0.5));


    return 0;
}