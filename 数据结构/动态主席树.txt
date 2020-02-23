//树状数组套主席树，动态维护区间第k小
//当前点p作用于[p, N]的主席树（普通主席树是在rt[p - 1]的基础上得到)
//查询[1, p]，即可得到rt[p]时的状态
int N, M;
int a[MAX], b[MAX << 1], n;

struct node {
    int x, y, z;
} q[MAX];
--------------动态主席树--------------------------------------
int rt[MAX], ru[MAX], rv[MAX], tot;
int lc[MAX_N], rc[MAX_N], sum[MAX_N];

void update(int &now, int l, int r, int p, int v) {
    if (!now) now = ++tot;
    sum[now] += v;
    if (l < r) {
        if (p <= m) update(lc[now], l, m, p, v);
        else update(rc[now], m + 1, r, p, v);
    }
}

void change(int p, int v) {
    int pos = lower_bound(b + 1, b + 1 + n, a[p]) - b;
    for (int i = p; i <= n; i += lowbit(i))
        update(rt[i], 1, n, pos, v);
}

int query(int ql, int qr, int k) {
    ql--;//前缀和相减，[ql, qr]的状态为pre[qr] - pre[ql - 1]
    int cnt1 = 0, cnt2 = 0;
    for (int i = qr; i; i -= lowbit(i)) ru[++cnt1] = rt[i];
    for (int i = ql; i; i -= lowbit(i)) rv[++cnt2] = rt[i];
    int l = 1, r = n;
    while (l < r) {
        int num = 0;
        for (int i = 1; i <= cnt1; i++) num += sum[lc[ru[i]]];
        for (int i = 1; i <= cnt2; i++) num -= sum[lc[rv[i]]];
        if (k <= num) {
            for (int i = 1; i <= cnt1; i++) ru[i] = lc[ru[i]];
            for (int i = 1; i <= cnt2; i++) rv[i] = lc[rv[i]];
            r = m;
        }
        else {
            for (int i = 1; i <= cnt1; i++) ru[i] = rc[ru[i]];
            for (int i = 1; i <= cnt2; i++) rv[i] = rc[rv[i]];
            l = m + 1;
            k -= num;
        }
    }
    return b[l];
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) scanf("%d", &a[i]), b[++n] = a[i];
    for (int i = 1; i <= M; i++) {
        char ch = getchar();
        while (ch != 'Q' && ch != 'C') ch = getchar();
        scanf("%d%d", &q[i].x, &q[i].y);
        if (ch == 'Q') scanf("%d", &q[i].z);
        else b[++n] = q[i].y;
    }
    sort(b + 1, b + 1 + n);
    n = unique(b + 1, b + 1 + n) - b - 1;

    for (int i = 1; i <= N; i++)
        change(i, 1);

    for (int i = 1; i <= M; i++) {
        if (!q[i].z) {
            change(q[i].x, -1);
            a[q[i].x] = q[i].y;
            change(q[i].x, 1);
        }
        else {
            printf("%d\n", query(q[i].x, q[i].y, q[i].z));
        }
    }

    return 0;
}