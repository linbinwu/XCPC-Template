int siz[N], son[N], dep[N], fa[N], top[N];
int nodeOf[N], id[N], cnt;
void dfs(int u, int par) {
    dep[u] = dep[fa[u] = par] + (siz[u] = 1);
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != par) {
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
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa[u] && v != son[u]) dfs2(v, v);
}

int ask(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        res += query(1, id[top[x]], id[x]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return res += query(1, id[x], id[y]);
}

int main() {

    int rt = 1; dfs(rt, 0); dfs2(rt, rt);
    build(1, 1, cnt);

    //x对应线段树上的点id[x]
    //线段树上的点x对应树上点nodeOf[x]

    return;
}