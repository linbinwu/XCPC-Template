int siz[MAX], son[MAX];
void dfs(int u, int fa) {
    siz[u] = 1;
    for (auto &v: g[u])
        if (v != fa) {
            dfs(v, u);
            siz[u] += siz[v];
            if (!son[u] || siz[v] > siz[son[u]])
                son[u] = v;
        }
}
int vis[MAX];

void upd(int u, int fa, int k) {

    for (auto &v: g[u])
        if (v != fa && !vis[v]) upd(v, u, k);
}

void dsu(int u, int fa, int keep) {//point
    for (auto &v: g[u])
        if (v != fa && v != son[u]) dsu(v, u, 0);
    if (son[u]) dsu(son[u], u, 1), vis[son[u]] = 1;

    if (son[u]) vis[son[u]] = 0;
    if (!keep) upd(u, fa, -1);
}


int id[MAX], nodeOf[MAX], cnt;
void dsu(int u, int fa, int keep) {//edge
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa && v != son[u]) dsu(v, u, 0);
    if (son[u]) dsu(son[u], u, 1);
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa && v != son[u]) {
            for (int j = 0; j < siz[v]; j++)
                upd(nodeOf[id[v] + j]);
            for (int j = 0; j < siz[v]; j++)
                update(nodeOf[id[v] + j], 1);
        }
    upd(u);
    update(u, 1);
    if (!keep) {
        for (int j = 0; j < siz[u]; j++)
            update(nodeOf[id[u] + j], -1);
    }
}

dfs(1, 0);
dsu(1, 0, 0);

