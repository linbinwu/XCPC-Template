
//树上启发式合并和点分治都能解决树上边、点信息问题, 一般来说
//如果已经确定树根, 就不能用点分治, 因为点分治需要找树的重心
//而树上启发式合并更侧重于处理——子树信息

int siz[N], son[N];
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
int vis[N];

void upd(int u, int fa, int k) {

    for (auto &v: g[u])
        if (v != fa && !vis[v]) upd(v, u, k);
}

void dsu(int u, int fa, int keep) {//点信息
    for (auto &v: g[u])
        if (v != fa && v != son[u]) dsu(v, u, 0);
    if (son[u]) dsu(son[u], u, 1), vis[son[u]] = 1;
    //更新自己+子树信息的同时统计答案

    if (son[u]) vis[son[u]] = 0;
    if (!keep) upd(u, fa, -1);
}


int id[N], nodeOf[N], cnt;
void dsu(int u, int fa, int keep) {//边信息
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

int main() {

    int rt = 1; dfs(rt, 0);
    dsu(rt, 0, 0);

    return 0;
}

