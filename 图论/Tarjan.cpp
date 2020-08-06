int n, m;
vector<int> g[N];
int dfn[N], low[N], vis[N], cnt;//cnt记录dfs点时间
int color[N], siz[N], col;//co某点属于哪个强连通分量, siz某强连通分量大小, col强连通分量个数
int st[N], top;

void tarjan(int u) {//强连通
    dfn[u] = low[u] = ++cnt;
    st[++top] = u;
    vis[u] = 1;
    for (auto &v: g[u]) {
        if (!dfn[v]) {
            tarjan(v);
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
        /*非缩点
        ++col;
        vis[u] = 0;
        while (st[top] != u) vis[st[top--]] = 0;
        --top;*/
    }
}

void init() {
    cnt = top = col = 0;
}


int dfn[N], low[N], cnt, tot;
bool cut[N];

void tarjan(int u, int topf) {//无向图割点
    dfn[u] = low[u] = ++cnt;
    int child = 0;
    for (auto &v: g[u]) {
        if (!dfn[v]) {
            tarjan(v, topf);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != topf) cut[u] = 1;
            if (u == topf) child++;
        }
        low[u] = min(low[u], dfn[v]);
    }
    if (child >= 2 && u == topf) cut[u] = 1;
}
