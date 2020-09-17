struct Matrix {
    static const int N = 510;
    int a[N][N], n;
    Matrix(int siz) {
        n = siz;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = 0;
    }
    Matrix operator * (const Matrix& A) const {//重载矩阵乘法
        Matrix res = Matrix(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    res.a[i][j] = (res.a[i][j] + 1ll * A.a[i][k] * a[k][j] % mod) % mod;
        return res;
    }
};

Matrix power(Matrix A, ll k) {//普通的快速幂
    Matrix res = Matrix(A.n);
    for (int i = 0; i < res.n; i++) res.a[i][i] = 1;
    while (k) {
        if (k & 1)res = res * A;
        A = A * A;
        k >>= 1;
    }
    return res;
}

Matrix power(Matrix A, string s) {//优化的快速幂
    Matrix res = Matrix(A.n);
    for (int i = 0; i < res.n; i++) res.a[i][i] = 1;
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] != '0') res = res * power(A, s[i] - '0');
        A = power(A, 10);
    }
    return res;
}