const int N = 1e5 + 10;
const int M = 3e5 + 10;
const int INF = 0x3fffffff;
const ll INF64 = 0x3fffffffffffffffLL;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &rhs) const { return w < rhs.w; }
};

Edge e[M];
bool used[M];

int n, m;

class Tr {
private:
    struct Edge {
        int to, nxt, val;
    } e[M << 1];
    int tot, head[N];

    int par[N][22], dep[N];
    // 到祖先的路径上边权最大的边
    int maxx[N][22];
    // 到祖先的路径上边权次大的边，若不存在则为 -INF
    int minn[N][22];

public:
    void add(int u, int v, int val) {
        e[++tot] = (Edge){v, head[u], val};
        head[u] = tot;
    }

    void insedge(int u, int v, int val) {
        add(u, v, val);
        add(v, u, val);
    }

    void dfs(int u, int fa) {
        dep[u] = dep[fa] + 1;
        par[u][0] = fa;
        minn[u][0] = -INF;
        for (int i = 1; (1 << i) <= dep[u]; i++) {
            par[u][i] = par[par[u][i - 1]][i - 1];
            int kk[4] = {maxx[u][i - 1], maxx[par[u][i - 1]][i - 1],
                         minn[u][i - 1], minn[par[u][i - 1]][i - 1]};
            // 从四个值中取得最大值
            sort(kk, kk + 4);
            maxx[u][i] = kk[3];
            // 取得严格次大值
            int ptr = 2;
            while (ptr >= 0 && kk[ptr] == kk[3]) ptr--;
            minn[u][i] = (ptr == -1 ? -INF : kk[ptr]);
        }

        for (int i = head[u]; i; i = e[i].nxt)
            if (e[i].to != fa) {
                maxx[e[i].to][0] = e[i].val;
                dfs(e[i].to, u);
            }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 21; i >= 0; i--)
            if (dep[par[u][i]] >= dep[v]) u = par[u][i];
        if (u == v) return u;
        for (int i = 21; i >= 0; i--)
            if (par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        return par[u][0];
    }

    int query(int u, int v, int val) {
        int res = -INF;
        for (int i = 21; i >= 0; i--)
            if (dep[par[u][i]] >= dep[v]) {
                if (val != maxx[u][i]) res = max(res, maxx[u][i]);
                else res = max(res, minn[u][i]);
                u = par[u][i];
            }
        return res;
    }
} tr;

int pre[N];
int find(int x) { return pre[x] == x ? x : pre[x] = find(pre[x]); }

ll Kruskal() {
    int tot = 0; ll sum = 0;
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; i++) pre[i] = i;

    for (int i = 1; i <= m; i++) {
        int a = find(e[i].u);
        int b = find(e[i].v);
        if (a != b) {
            pre[a] = b;
            tot++;
            tr.insedge(e[i].u, e[i].v, e[i].w);
            sum += e[i].w;
            used[i] = 1;
        }
        if (tot == n - 1) break;
    }
    return sum;
}

int main() {


    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        e[i] = {u, v, w};
    }

    ll sum = Kruskal();
    ll ans = INF64;
    tr.dfs(1, 0);

    for (int i = 1; i <= m; i++) {
        if (!used[i]) {
            int _lca = tr.lca(e[i].u, e[i].v);
            // 找到路径上不等于 e[i].val 的最大边权
            ll tmpa = tr.query(e[i].u, _lca, e[i].w);
            ll tmpb = tr.query(e[i].v, _lca, e[i].w);
            // 这样的边可能不存在，只在这样的边存在时更新答案
            if (max(tmpa, tmpb) > -INF)
                ans = min(ans, sum - max(tmpa, tmpb) + e[i].w);
        }
    }
    // 次小生成树不存在时输出 -1
    printf("%lld\n", ans == INF64 ? -1 : ans);
    return 0;
}