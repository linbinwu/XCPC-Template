
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
