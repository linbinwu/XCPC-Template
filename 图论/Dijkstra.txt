//O((N+M)logM)
struct node {
    int now, d;
    bool operator < (const node &rhs) const {
        return d > rhs.d;
    }
};

priority_queue<node> q;

void dijkstra(int s) {
    for (int i = 1; i <= N; i++) dis[i] = INF, vis[i] = 0;
    dis[s] = 0;
    q.push(node{s, dis[s]});
    while (!q.empty()) {
        node p = q.top(); q.pop();
        int u = p.now, d = p.d;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
            if (dis[u] + e[i].w < dis[v]) {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v]) q.push(node{v, dis[v]});
            }
    }
}