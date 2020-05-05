const int MAX_BIT = 20;

int dp[MAX][MAX_BIT];//dp[i][j]表示区间[i, i + 2 ^ j - 1]内的最小值

void build(int N) {
    for (int i = 1; i <= N; i++) cin >> dp[i][0];
    for (int j = 1; j < MAX_BIT; j++)
        for (int i = 1; i + (1 << j) - 1 <= N; i++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}

int query(int ql, int qr) {
    int k = (int)log2(qr - ql + 1);
    return min(dp[ql][k], dp[qr - (1 << k) + 1][k]);
}
