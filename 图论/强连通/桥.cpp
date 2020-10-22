vector<int> g[N];
int low[N], dfn[N], fa[N], dfnt, cnt_bridge;
bool isbridge[N];//(x, fa[x])为桥

void tarjan(int u, int par) {
    fa[u] = par;
    low[u] = dfn[u] = ++dfnt;
    for (auto &v: g[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                isbridge[v] = true;
                cnt_bridge++;
            }
        }
        else if (dfn[v] < dfn[u] && v != par) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
