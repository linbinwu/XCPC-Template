bool gauss(double a[][MAX], int n) {
    //a[][]为增广矩阵[0, n) x [0, n)
    //最后解在a[][n]中
    int i, j, k, r;
    for (i = 0; i < n; i++) {
        r = i;
        for (j = i + 1; j < n; j++)
            if (abs(a[j][i]) > abs(a[r][i])) r = j;
        if (abs(a[r][i]) < eps) return 0;//无穷多解
        if (r != i) {
            for (j = 0; j <= n; j++)
                swap(a[r][j], a[i][j]);
        }
        for (j = n; j >= i; j--)
            for (k = i + 1; k < n; k++)
                a[k][j] -= a[k][i] / a[i][i] * a[i][j];
    }
    for (i = n - 1; i >= 0; i--) {
        for (j = i + 1; j < n; j++)
            a[i][n] -= a[j][n] * a[i][j];
        a[i][n] /= a[i][i];
    }
    return 1;//唯一解
}