int last[N];//上一种i出现位置
int rt[N], tot;
int lc[MAX_N], rc[MAX_N], sum[MAX_N];

void update(int &now, int pre, int l, int r, int p, int v) {
    now = ++tot;
    sum[now] = sum[pre] + v, lc[now] = lc[pre], rc[now] = rc[pre];
    if (l < r) {
        if (p <= mid) update(lc[now], lc[pre], l, mid, p, v);
        else update(rc[now], rc[pre], mid + 1, r, p, v);
    }
}

int query(int now, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum[now];
    int res = 0;
    if (ql <= mid) res += query(lc[now], l, mid, ql, qr);
    if (qr > mid) res += query(rc[now], mid + 1, r, ql, qr);
    return res;
}

int main() {
    for (int i = 1; i <= n; i++) {
        int x; scanf("%d", &x);
        update(rt[i], rt[i - 1], 1, n, i, 1);
        if (last[x]) update(rt[i], rt[i], 1, n, last[x], -1);//上一种出现就删除掉
        last[x] = i;
    }
    while (m--) {
        int ql, qr; scanf("%d%d", &ql, &qr);
        //rt[qr]包含[1, qr]的信息, 这里只查询[ql, qr]部分
        printf("%d\n", query(rt[qr], 1, n, ql, n));
    }
    return 0;
}
