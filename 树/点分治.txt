//用于解决树上静态路径统计问题
//只需要考虑经过当前树根的两边组成的路径
//经过的树根若是不同一定能在当前树的子树中解决
//如距离为K/小于K的路径有多少....

int maxp[MAX], siz[MAX], vis[MAX], rt;

void getRt(int u, int fa, int all) {//求树的重心
    siz[u] = 1, maxp[u] = 0;
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa && !vis[v]) {
            getRt(v, u, all);
            siz[u] += siz[v];
            maxp[u] = max(maxp[u], siz[v]);
        }
    maxp[u] = max(maxp[u], all - siz[u]);
    if (maxp[u] < maxp[rt]) rt = u;
}

void calc(int u) {//具体题目具体分析
//可以用store记录一下当前树所加的路径

//最后结束的时候清空即可
}

void dfs(int u) {
    vis[u] = 1;
    calc(u);
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (!vis[v]) {
            maxp[rt = 0] = N; getRt(v, 0, siz[v]);
            dfs(rt);
        }
}

int main() {

    maxp[rt = 0] = N; getRt(1, 0, N);
    dfs(rt);

    return 0;
}