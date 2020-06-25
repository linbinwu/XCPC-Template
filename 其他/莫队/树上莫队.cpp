#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1e5 + 10;

struct Hash {
    int b[MAX], tot;
    void init() { tot = 0; }
    void insert(int x) { b[++tot] = x; }
    void build() {
        sort(b + 1, b + 1 + tot);
        tot = unique(b + 1, b + 1 + tot) - (b + 1);
    }
    int pos(int x) { return lower_bound(b + 1, b + 1 + tot, x) - b; }
} ha;

int N, M;
int c[MAX], cnt[MAX];
vector<int> g[MAX];
int st[MAX], ed[MAX], dfnt, nodeOf[MAX << 1], tag[MAX];
int belong[MAX], sizz;
int ans[MAX], res;

struct Query {
    int l, r, id, k;
    bool operator < (const Query &rhs) const {
        return belong[l] ^ belong[rhs.l] ? belong[l] < belong[rhs.l] : r < rhs.r;
    }
} q[MAX];

int son[MAX], siz[MAX], top[MAX], fa[MAX], dep[MAX];
void dfs(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    int max_son = -1; nodeOf[st[u] = ++dfnt] = u;
    for (auto &v: g[u])
        if (v != par) {
            dfs(v, u);
            siz[u] += siz[v];
            if (max_son < siz[v])
                son[u] = v, max_son = siz[v];
        }
    nodeOf[ed[u] = ++dfnt] = u;
}
void dfs2(int u, int topf) {
    top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (auto &v: g[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

void upd(int x) {
    x = nodeOf[x];
    if (tag[x]) {
        cnt[c[x]]--;
        if (!cnt[c[x]]) res--;
    }
    else {
        if (!cnt[c[x]]) res++;
        cnt[c[x]]++;
    }
    tag[x] ^= 1;
}

int main() {
#ifdef ACM_LOCAL
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) scanf("%d", &c[i]), ha.insert(c[i]);
    ha.build();
    for (int i = 1; i <= N; i++) c[i] = ha.pos(c[i]);

    for (int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v); g[v].push_back(u);
    }
    int rt = 1; dfs(rt, 0); dfs2(rt, rt);

    sizz = sqrt(dfnt); int num = ceil((long double)dfnt / sizz);
    for (int i = 1, j = 1; i <= num; i++)
        while (j <= i * sizz && j <= dfnt)
            belong[j++] = i;
    for (int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        int tlca = lca(u, v);
        if (st[u] > st[v]) swap(u, v);
        if (u == tlca) q[i] = Query{st[u], st[v], i, 0};
        else q[i] = Query{ed[u], st[v], i, tlca};

    }
    sort(q + 1, q + 1 + M);

    int l = 1, r = 0;
    for (int i = 1; i <= M; i++) {
        int ql = q[i].l, qr = q[i].r;
        while (l < ql) upd(l++);
        while (l > ql) upd(--l);
        while (r < qr) upd(++r);
        while (r > qr) upd(r--);
        ans[q[i].id] = res + (q[i].k ? (cnt[c[q[i].k]] == 0) : 0);
    }

    for (int i = 1; i <= M; i++) printf("%d\n", ans[i]);

    return 0;
}