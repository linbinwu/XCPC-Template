//F(x)=FL(x^2)+x*FR(x^2)
//F(W^k)=FL(w^k)+W^k*FR(w^k)
//F(W^{k+n/2})=FL(w^k)-W^k*FR(w^k)

const int MAX = 4e6 + 10;//4N
const double PI = acos(-1);

struct Complex {
    double a, b;
    Complex(double a = 0, double b = 0): a(a), b(b) {}
    Complex operator * (const Complex &rhs) { return Complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
    Complex operator + (const Complex &rhs) { return Complex(a + rhs.a, b + rhs.b); }
    Complex operator - (const Complex &rhs) { return Complex(a - rhs.a, b - rhs.b); }
};

int N, M;
int n, tr[MAX];
Complex a[MAX], b[MAX];

void FFT(Complex *A, int type) {
    for (int i = 0; i < n; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int len = 2; len <= n; len <<= 1) {//区间长度
        int mid = len / 2;
        Complex Wn(cos(2 * PI / len), type * sin(2 * PI / len));//单位根
        for (int k = 0; k < n; k += len) {//每个子问题的起始点
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

int main() {

    scanf("%d%d", &N, &M);
    for (int i = 0; i <= N; i++) scanf("%lf", &a[i].a);
    for (int i = 0; i <= M; i++) scanf("%lf", &b[i].a);

    //get total length and tr[]
    n = 1; while (n <= N + M) n <<= 1;
    for (int i = 0; i < n; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);

    //DFT(a) and DFT(b)
    FFT(a, 1), FFT(b, 1);

    //DFT(c) = DFT(a) * DFT(b)
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i];

    //IDFT => c = a * b, at last c[i] / n
    FFT(a, -1);

    for (int i = 0; i <= N + M; i++)
        printf("%d ", (int)(a[i].a / n + 0.5));


    return 0;
}