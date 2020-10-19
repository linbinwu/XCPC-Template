//树上建主席树，支持动态修改边
int N, M, Q;
int a[MAX], b[MAX], n;

int pos(int x) { return lower_bound(b + 1, b + 1 + n, x) - b; }

struct edge {
    int nxt, to;
}e[MAX << 2];

int cnt, head[MAX];

void add(int u, int v) {
    e[++cnt].nxt = head[u];
    e[cnt].to = v;
    head[u] = cnt;
}

-----------------------主席树---------------------------------------
int tot, rt[MAX];
int lc[MAX * 400], rc[MAX * 400], num[MAX * 400];

int update(int pre, int l, int r, int p) {
    int now = ++tot;
    num[now] = num[pre] + 1;
    lc[now] = lc[pre], rc[now] = rc[pre];
    if (l < r) {
        if (p <= m)lc[now] = update(lc[pre], l, m, p);
        else rc[now] = update(rc[pre], m + 1, r, p);
    }
    return now;
}

int query(int u, int v, int x, int y, int k) {
    int l = 1, r = n;
    while (l < r) {
        int ls = num[lc[u]] + num[lc[v]] - num[lc[x]] - num[lc[y]];
        if (k <= ls) {
            u = lc[u], v = lc[v], x = lc[x], y = lc[y];
            r = m;
        }
        else {
            u = rc[u], v = rc[v], x = rc[x], y = rc[y];
            k -= ls, l = m + 1;
        }
    }
    return l;
}
------------------------LCA-----------------------------------------------
int dep[MAX], fa[MAX][20], lg[MAX], siz[MAX], pre[MAX], fff, vis[MAX];

void init(int N) {
    for (int i = 1; i <= N; i++)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
}

void dfs(int u, int f) {
    vis[u] = 1;
    //建树，在fa的基础上建树
    rt[u] = update(rt[f], 1, n, pos(a[u]));
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    fa[u][0] = f, pre[u] = fff;
    //此处本来应该是 (1 << i) <= dep[u]
    //但是这里是动态的树，有边的修改，所以祖先节点也需要更新
    for (int i = 1; i <= 18; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].to != f) {
            dfs(e[i].to, u);
            siz[u] += siz[e[i].to];
        }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    while (dep[x] > dep[y])
        x = fa[x][lg[dep[x] - dep[y]] - 1];
    if (x == y)return x;
    for (int k = lg[dep[x]] - 1; k >= 0; k--)
        if (fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}

int main() {
    int T = read();
    N = read(); M = read(); Q = read();
    init(N);

    for (int i = 1; i <= N; i++)a[i] = read(), b[i] = a[i], pre[i] = i;
    sort(b + 1, b + 1 + N);
    n = unique(b + 1, b + 1 + N) - (b + 1);

    for (int i = 1; i <= M; i++) {
        int u, v;
        u = read(); v = read();
        add(u, v); add(v, u);
    }

    for (int i = 1; i <= N; i++)
        if (!vis[i]) {
            fff = i;
            dfs(i, 0);
        }

    char op[10];
    int last_ans = 0;
    while (Q--) {
        scanf("%s", op);
        int x, y, k;
        x = read(); y = read();
        x ^= last_ans; y ^= last_ans;
        if (op[0] == 'Q') {
            k = read(); k ^= last_ans;
            int xy = lca(x, y);
            last_ans = b[query(rt[x], rt[y], rt[xy], rt[fa[xy][0]], k)];
            printf("%d\n", last_ans);
        }
        else {
            add(x, y); add(y, x);
            int fx = pre[x], fy = pre[y];
            if (siz[fx] < siz[fy]) {
                fff = fy;
                dfs(x, y);
            }
            else {
                fff = fx;
                dfs(y, x);
            }
        }
    }
    return 0;
}