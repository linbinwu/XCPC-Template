//树链剖分
//此代码为边权版本，点权版本为注释部分

int N, Q, S, w[MAX];
int cnt, head[MAX];
int tot, siz[MAX], son[MAX], dep[MAX], fa[MAX], top[MAX], id[MAX];
---------------前向星------------------------------------------
struct edge{
    int from, nxt, to, c;
} e[MAX << 1];

void add(int u, int v, int c) {
    e[++cnt].nxt = head[u];
    e[cnt].from = u;//remove
    e[cnt].to = v;
    e[cnt].c = c;//remove
    head[u] = cnt;
}
-----------------线段树----------------------------------------
struct SegTree {
    int l, r, sum;
} t[MAX << 2];

void push_up(int u) {
    t[u].sum = t[lc].sum + t[rc].sum;
}

void build(int u, int l, int r) {
    t[u].l = l, t[u].r = r, t[u].sum = 0;
    if (l == r) return;
    //t[u].sum = w[pos[l]];
    build(lc, l, m); build(rc, m + 1, r);
    push_up(u);
}

void update(int u, int p, int k) {
    if (t[u].l == t[u].r) {
        t[u].sum = k;
        return;
    }
    if (p <= mid) update(lc, p, k);
    else update(rc, p, k);
    push_up(u);
}

int query(int u, int ql, int qr) {
    if (ql <= t[u].l && t[u].r <= qr) return t[u].sum;
    int res = 0;
    if (ql <= mid) res += query(lc, ql, qr);
    if (qr > mid) res += query(rc, ql, qr);
    return res;
}
-----------------树剖------------------------------------------
void dfs1(int u, int f, int d) {
    dep[u] = d, fa[u] = f, siz[u] = 1;
    int max_son = -1;
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != f) {
            dfs1(v, u, d + 1);
            siz[u] += siz[v];
            if (max_son < siz[v])
                max_son = siz[v], son[u] = v;
        }
}

void dfs2(int u, int topf) {
    id[u] = ++tot;
    //pos[tot] = u;
    top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa[u] && v != son[u])
            dfs2(v, v);
}

int ask(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += query(1, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (x != y) {//remove
        if (dep[x] > dep[y]) swap(x, y);
        res += query(1, id[son[x]], id[y]);
        //res += query(1, id[x], id[y]);
    }
    return res;
}

--------------------多组样例初始化-------------------------------
void init() {
    tot = cnt = 0;
    memset(head, 0, sz(head));
    memset(son, 0, sz(son));
}

int main() {
    init();
    scanf("%d%d%d", &N, &Q, &S);
    for (int i = 1; i < N; i++) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        add(u, v, c); add(v, u, c);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    build(1, 1, tot);
    for (int i = 1; i <= cnt; i += 2) {
        int u = e[i].from, v = e[i].to;
        if (dep[u] < dep[v]) swap(u, v);
        update(1, id[u], e[i].c);
    }
    int last = S;
    while (Q--) {
        int op; scanf("%d", &op);
        if (!op) {
            int p; scanf("%d", &p);
            printf("%d\n", ask(last, p));
            last = p;
        }
        else {
            int p, k; scanf("%d%d", &p, &k);
            int u = e[(p << 1) - 1].from, v = e[(p << 1) - 1].to;
            if (dep[u] < dep[v]) swap(u, v);//边权需要找深度更深的
            update(1, id[u], k);
        }
    }
    return 0;
}