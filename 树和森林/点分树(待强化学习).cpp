//建立点分树

struct Grap {
    struct edge {
        int nxt, to;
        ll w;
    } e[MAX << 1];
    int head[MAX], tot;
    void add(int u, int v, int w) { e[++tot] = edge{ head[u], v, w }; head[u] = tot; }
    //G1为原树, G2点分树
    //G2中v为当前点到下一个重心w靠近u的点
} G1, G2;


int root, rt;
int maxp[MAX], siz[MAX], vis[MAX], fa[MAX];
void getRt(int u, int par, int all) {//求树的重心，将分治复杂度降为logN
    siz[u] = 1, maxp[u] = 0;
    for (int i = G1.head[u], v = G1.e[i].to; i; i = G1.e[i].nxt, v = G1.e[i].to)
        if (v != par && !vis[v]) {
            getRt(v, u, all);
            siz[u] += siz[v];
            maxp[u] = max(maxp[u], siz[v]);
        }
    maxp[u] = max(maxp[u], all - siz[u]);
    if (maxp[u] < maxp[rt]) rt = u;
}
void rebuild(int u) {//建点分树
    vis[u] = 1;
    for (int i = G1.head[u], v = G1.e[i].to; i; i = G1.e[i].nxt, v = G1.e[i].to)
        if (!vis[v]) {
            maxp[rt = 0] = N; getRt(v, 0, siz[v]);
            G2.add(u, v, rt); fa[rt] = u;
            rebuild(rt);
        }
}


int main() {

    maxp[rt = 0] = N; getRt(1, 0, N); root = rt;
    rebuild(root);


    return 0;
}