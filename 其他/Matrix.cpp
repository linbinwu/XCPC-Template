struct Matrix {
    static const int MAX_N = 10, INF = 0x3f3f3f3f;
    int n, a[MAX_N][MAX_N];
    Matrix(int siz, int type) {
        n = siz;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (type == 0) a[i][j] = 0;
                else if (type == 1) a[i][j] = i == j ? 1 : 0;
                else a[i][j] = INF;
            }
    }
    Matrix operator * (const Matrix &rhs) {
        Matrix res = Matrix(n, 0);
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res.a[i][j] += a[i][k] * rhs.a[k][j];
        return res;
    }
};

Matrix qpow(Matrix a, ll b) {
    Matrix res = Matrix(a.n, 1);
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}