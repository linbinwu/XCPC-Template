//计算生成树个数
//即求\sum_{Tree} \prod_{e ∈ Tree} num(e)

ll gauss(int n, ll K[][N]) {//求矩阵K的n-1阶顺序主子式
    ll res = 1;
    for (int i = 1; i <= n - 1; i++) {//枚举主对角线上第i个元素
        for (int j = i + 1; j <= n - 1; j++) {//枚举剩下的行
            while (K[j][i]) {//辗转相除
                int t = K[i][i] / K[j][i];
                for (int k = i; k <= n - 1; k++)//转为倒三角
                    K[i][k] = (K[i][k] - t * K[j][k] + mod) % mod;
                swap(K[i], K[j]);//交换i、j两行
                res = -res;//取负
            }
        }
        res = (res * K[i][i]) % mod;
    }
    return (res + mod) % mod;
}

int n, m;
int K[N][N];

int main() {

    for (int i = 1; i <= m; i++) {
        int u, v; ll w; scanf("%d%d%lld", &u, &v, &w);
        K[u][u]++, K[v][v]++, K[u][v]--, K[v][u]--;
    }

    ll ans = gauss(n, K);

    return 0;
}