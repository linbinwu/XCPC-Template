vector<int> g[N];
vector<pii> edge;
int dfn[N], low[N], vis[N], dfnt;
int color[N], siz[N], col;
int st[N], top;

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++dfnt;
    st[++top] = u;
    vis[u] = 1;
    for (auto &v: g[u]) {
        if (v == fa) continue;//ÓÐÏòÍ¼È¥µô
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        color[u] = ++col;
        vis[u] = 0;
        ++siz[col];
        while (st[top] != u) {
            ++siz[col];
            color[st[top]] = col;
            vis[st[top--]] = 0;
        }
        --top;
    }
}

void init() {
    dfnt = top = col = 0;
    for (int i = 1; i <= n; i++) g[i].clear();
}

int main() {


    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, 0);
    for (int i = 1; i <= n; i++) g[i].clear();
    for (auto &i: edge) {
        int u = color[i.first], v = color[i.second];
        if (u != v) {
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }

}