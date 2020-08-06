//key is
//a - b >= c    <->  b - a <= -c
//a - b <= c    <->  a - b <= c
//a - b == c    <->  a - b <= c && b - a <= -c
//注意初始化    有时候需要超级源点0

bool spfa(int u) {//dfs跑差分约束最短路
    vis[u] = 1;
    for (int i = head[u], v; i; i = e[i].nxt)
        if (dis[u] + e[i].w < dis[v = e[i].to]) {
            if (vis[v]) return false;
            else {
                dis[v] = dis[u] + e[i].w;
                if (!spfa(v)) return false;
            }
        }
    vis[u] = 0;
    return true;
}