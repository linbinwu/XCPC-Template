int siz[N], son[N], dep[N], fa[N], top[N];
int id[N], nodeOf[N], cnt;//划分点
void dfs(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    for (auto &v: g[u])
        if (v != par) {
            dfs(v, u);
            siz[u] += siz[v];
            if (!son[u] || siz[v] > siz[son[u]])
                son[u] = v;
        }
}

void dfs2(int u, int topf) {
    nodeOf[id[u] = ++cnt] = u, top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (auto &v: g[u])
        if (v != fa[u] && v != son[u]) dfs2(v, v);
}