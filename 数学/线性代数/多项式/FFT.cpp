//F(x)=FL(x^2)+x*FR(x^2)
//F(W^k)=FL(w^k)+W^k*FR(w^k)
//F(W^{k+n/2})=FL(w^k)-W^k*FR(w^k)


const int N = 4e5 + 10;//4倍空间
const double PI = acos(-1);

struct Complex {
    double a, b;
    Complex(double a = 0, double b = 0): a(a), b(b) {}
    Complex operator * (const Complex &rhs) { return Complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
    Complex operator + (const Complex &rhs) { return Complex(a + rhs.a, b + rhs.b); }
    Complex operator - (const Complex &rhs) { return Complex(a - rhs.a, b - rhs.b); }
};

int tr[N];

void FFT(Complex *A, int len, int type) {
    for (int i = 0; i < len; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int i = 2; i <= len; i <<= 1) {//区间长度
        int mid = i / 2;
        Complex Wn(cos(2 * PI / i), type * sin(2 * PI / i));//单位根
        for (int k = 0; k < len; k += i) {//每个子问题的起始点
            Complex w(1, 0);//omega
            for (int l = k; l < k + mid; l++) {
                Complex t = w * A[l + mid];
                A[l + mid] = A[l] - t;
                A[l] = A[l] + t;
                w = w * Wn;
            }
        }
    }
}

void mul(Complex *a, Complex *b, int n) {
    int len = 1; while (len <= n) len <<= 1;
    for (int i = 0; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    FFT(a, len, 1), FFT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i];
    FFT(a, len, -1);
    for (int i = 0; i < len; i++) a[i].a /= len;
}

Complex a[N], b[N];

int main() {

    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lf", &a[i].a);
    for (int i = 0; i <= m; i++) scanf("%lf", &b[i].a);

    mul(a, b, n + m);
    for (int i = 0; i <= n + m; i++)
        printf("%d ", (int)(a[i].a + 0.5));


    return 0;
}