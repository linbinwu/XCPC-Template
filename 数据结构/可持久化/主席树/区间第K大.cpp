struct Hash {
    int b[MAX], tot;
    void init() { tot = 0; }
    void insert(int x) { b[++tot] = x; }
    void build() {
        sort(b + 1, b + 1 + tot);
        tot = unique(b + 1, b + 1 + tot) - (b + 1);
    }
    int pos(int x) { return lower_bound(b + 1, b + 1 + tot, x) - b; }
};

const int MAX_N = MAX * 25;
int rt[MAX], tot;
int lc[MAX_N], rc[MAX_N], num[MAX_N];

void update(int &now, int pre, int l, int r, int p) {
    now = ++tot;
    num[now] = num[pre] + 1, lc[now] = lc[pre], rc[now] = rc[pre];
    if (l == r) return;
    if (p <= mid) update(lc[now], lc[pre], l, mid, p);
    else update(rc[now], rc[pre], mid + 1, r, p);
}

int query(int now, int pre, int k) {
    int l = 1, r = ha.tot;
    while (l < r) {
        int sum = num[lc[now]] - num[lc[pre]];
        if (k <= sum) {
            now = lc[now], pre = lc[pre];
            r = mid;
        }
        else {
            now = rc[now], pre = rc[pre];
            l = mid + 1;
            k -= sum;
        }
    }
    return ha.b[l];
}