struct Complex {
    double a, b;
    Complex(double a = 0, double b = 0): a(a), b(b) {}
    Complex operator * (const Complex &rhs) { return Complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
    Complex operator + (const Complex &rhs) { return Complex(a + rhs.a, b + rhs.b); }
    Complex operator - (const Complex &rhs) { return Complex(a - rhs.a, b - rhs.b); }
} store[MAX << 1];

//递归版
void FFT(Complex *A, int len, int type) {//type(1, -1) = (DFT, IDFT)
    if (len == 1) return;
    Complex *fl = A, *fr = A + len / 2;
    for (int k = 0; k < len; k++) store[k] = A[k];
    for (int k = 0; k < len / 2; k++) fl[k] = store[k << 1], fr[k] = store[k << 1 | 1];
    FFT(fl, len / 2, type), FFT(fr, len / 2, type);
    Complex Wn = Complex(cos(2 * PI / len), type * sin(2 * PI / len));
    Complex w = Complex(1, 0);
    //Wn -> 单位根, w * I -> 下一个单位根
    for (int k = 0; k < len / 2; k++) {
        store[k] = fl[k] + w * fr[k];
        store[k + len / 2] = fl[k] - w * fr[k];
        w = w * Wn;
    }
    for (int k = 0; k < len; k++) A[k] = store[k];
}