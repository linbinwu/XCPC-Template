//四维偏序查最大值
int N;
struct node {
    int a, b, c, d;
    inline bool operator < (const node &rhs) const {//四维排序掉一维
        return a < rhs.a || (a == rhs.a && (b < rhs.b || (b == rhs.b && (c < rhs.c || (c == rhs.c && d < rhs.d)))));
    }
} nod[MAX];

struct point {
    int x, y, z, val;
} p[MAX];

inline point max(const point &a, const point &b) {
    return point{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)};
}

inline point min(const point &a, const point &b) {
    return point{min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)};
}

int cmptype;

inline bool operator < (const point &a, const point &b) {
    if (cmptype == 0) return a.x <  b.x;
    else if (cmptype == 1) return a.y < b.y;
    else return a.z < b.z;
}

struct K_D_Tree{
    point pos, lpos, rpos;
    int mx, siz;
    int ls, rs;
} t[MAX];

int root, tot, top, rub[MAX];

inline int newnode() {
    if (top) return rub[top--];
    else return ++tot;
}

inline void push_up(int u) {
    t[u].lpos = t[u].rpos = t[u].pos;
    t[u].mx = t[u].pos.val;
    t[u].siz = 1;
    if (lc) {
        t[u].siz += t[lc].siz;
        t[u].lpos = min(t[u].lpos, t[lc].lpos);
        t[u].rpos = max(t[u].rpos, t[lc].rpos);
        t[u].mx = max(t[u].mx, t[lc].mx);
    }
    if (rc) {
        t[u].siz += t[rc].siz;
        t[u].lpos = min(t[u].lpos, t[rc].lpos);
        t[u].rpos = max(t[u].rpos, t[rc].rpos);
        t[u].mx = max(t[u].mx, t[rc].mx);
    }
}

inline int build(int l, int r, int type) {//建树
    if (l > r) return 0;
    cmptype = type;
    nth_element(p + l, p + m, p + r + 1);
    int u = newnode();
    t[u].pos = p[m];
    t[u].ls = build(l, m - 1, (type + 1) % 3);
    t[u].rs = build(m + 1, r, (type + 1) % 3);
    push_up(u);
    return u;
}

inline void pia(int u, int num) {//拍扁回炉重做
    if (lc) pia(lc, num);
    p[t[lc].siz + num + 1] = t[u].pos, rub[++top] = u;
    if (rc) pia(rc, t[lc].siz + num + 1);
}

inline void check(int &u, int type) {//检查是否平衡，不平衡则需要重建
    if (t[u].siz * alpha < t[lc].siz || t[u].siz * alpha < t[rc].siz) pia(u, 0), u = build(1, t[u].siz, type);
}

inline void insert(int &u, int type, point tp) {
    if (!u) {//新点
        u = newnode();
        lc = rc = 0;
        t[u].pos = tp;
        push_up(u);
        return;
    }
    cmptype = type;
    if (tp < t[u].pos) insert(lc, (type + 1) % 3, tp);
    else insert(rc, (type + 1) % 3, tp);
    push_up(u);
    check(u, type);
}

inline bool out(const point &l, const point &r, const point &L, const point &R) {//完全在外面
    return l.x > R.x || l.y > R.y || l.z > R.z || r.x < L.x || r.y < L.y || r.z < L.z;
}

inline bool in(const point &l, const point &r, const point &L, const point &R) {//完全在里面
    return l.x <= L.x && R.x <= r.x && l.y <= L.y && R.y <= r.y && l.z <= L.z && R.z <= r.z;
}

inline int query(int u, point ql, point qr) {//查询最大值
    if (!u || out(ql, qr, t[u].lpos, t[u].rpos)) return 0;
    if (in(ql, qr, t[u].lpos, t[u].rpos)) return t[u].mx;
    int res = 0;
    if (in(ql, qr, t[u].pos, t[u].pos)) res = max(res, t[u].pos.val);
    res = max(res, query(lc, ql, qr));
    res = max(res, query(rc, ql, qr));
    return res;
}

inline void init() {
    root = tot = top = 0;
}

int main() {
    init();
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d%d%d%d", &nod[i].a, &nod[i].b, &nod[i].c, &nod[i].d);
    sort(nod + 1, nod + 1 + N);
    for (int i = 1; i <= N; i++) p[i] = point{nod[i].b, nod[i].c, nod[i].d, 0};
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        ans = max(ans, p[i].val = query(root, point{ -INF, -INF, -INF}, p[i]) + 1);
        insert(root, 0, p[i]);
    }
    printf("%d\n", ans);
    return 0;
}