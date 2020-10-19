#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define sz  sizeof
#define eps 1e-9
#define lowbit(x) x&-x
#define lc  u<<1
#define rc  u<<1|1
#define mid (l+r)/2
typedef long long ll;
const int MAX = 1e5 + 10;

int N;
int X[MAX << 1];
int tot, cnt;

int pos(int x) { return lower_bound(X + 1, X + 1 + cnt, x) - X; }

struct Scanline {
    int l, r, h, f;
    bool operator < (const Scanline &rhs) const {
        return h < rhs.h;
    }
} line[MAX << 1];

struct SegmentTree {
    int l, r, sum, len;
} t[MAX << 2];

void push_up(int u) {
    if (t[u].sum) t[u].len = X[t[u].r + 1] - X[t[u].l];
    else t[u].len = t[lc].len + t[rc].len;
}

void build(int u, int l, int r) {
    t[u] = SegmentTree{ l, r, 0, 0 };
    if (l == r) return;
    build(lc, l, mid); build(rc, mid + 1, r);
}

void update(int u, int ql, int qr, int k) {
    if (ql <= t[u].l && t[u].r <= qr) {
        t[u].sum += k;
        return;
    }

}

int main() {
#ifdef ACM_LOCAL
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    auto start_clock = clock();
#endif
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int x1, x2, y1, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        line[++tot] = Scanline{ x1, x2, y1, 1 };
        line[++tot] = Scanline{ x1, x2, y2, -1 };
        X[++cnt] = x1, X[++cnt] = x2;
    }
    sort(line + 1, line + 1 + tot);
    sort(X + 1, X + 1 + cnt);
    cnt = unique(X + 1, X + 1 + cnt) - (X + 1);



#ifdef ACM_LOCAL
    cerr << (double)(clock() - start_clock) / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}