//性质
//以重心为根，所有的子树的大小都不超过整个树大小的一半
//树的重心最多有两个
//树的重心到其他节点的距离是最小的
//把两个树通过一条边相连得到一个新的树，那么新的树的重心在连接原来两个树的重心的路径上
//把一个树添加或删除一个叶子，那么它的重心最多只移动一条边的距离

int maxp[MAX], siz[MAX], rt;

void getRt(int u, int fa, int all) {//树的重心
    siz[u] = 1, maxp[u] = 0;
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa) {
            getRt(v, u, all);
            siz[u] += siz[v];
            maxp[u] = max(maxp[u], siz[v]);
        }
    maxp[u] = max(maxp[u], all - siz[u]);//fa子树为all - siz[u]
    if (maxp[u] < maxp[rt]) rt = u;
}

maxp[rt = 0] = N; getRt(1, 0, N);
