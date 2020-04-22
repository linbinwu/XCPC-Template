//高斯消元白书模板
//n ： 未知数个数，   a[][]为增广矩阵
//把解放在    a[][n]中
bool gauss(double a[][MAX], int n) {
    int i, j, k, r;
    for (i = 0; i < n; i++) {
        r = i;
        for (j = i + 1; j < n; j++)
            if (fabs(a[j][i]) > fabs(a[r][i]))
                r = j;

        if (fabs(a[r][i]) < eps)
            return 0;

        if (r != i)
            for (j = 0; j <= n; j++)
                swap(a[r][j], a[i][j]);


        //根据精度需要选择以下其一：
        //低精度
//        for (k = i + 1; k < n; k++) {
//            r = a[k][i] / a[i][j];
//            for (j = i; j <= n; j++)
//                a[k][j] -= r * a[i][j];
//        }
        //

        //高精度
        for (j = n; j >= i; j--)
            for (k = i + 1; k < n; k++)
                a[k][j] -= a[k][i] / a[i][i] * a[i][j];
        //
    }

    //回代过程
    for (i = n - 1; i >= 0; i--) {
        for (j = i + 1; j < n; j++)
            a[i][n] -= a[j][n] * a[i][j];
        a[i][n] /= a[i][i];
    }
    return 1;
}